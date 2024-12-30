// based on https://github.com/skeeto/ptrace-examples

#define _GNU_SOURCE
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define err(str) do { perror(__FILE__ ":" TOSTRING(__LINE__) ": " str); exit(1); } while (0)

int quiet = 0;

#define iprintf(...) do { if (!quiet) fprintf(stderr, __VA_ARGS__); } while (0)

int perform_operation(long op, unsigned char *buf, size_t len)
{
	switch (op) {
	case 1: // toupper
		for (size_t i = 0; i < len; i++)
			buf[i] = toupper(buf[i]);
		break;
	case 2: // reverse
		for (size_t i = 0; i < len/2; i++) {
			unsigned char tmp = buf[len - 1 - i];
			buf[len - 1 - i] = buf[i];
			buf[i] = tmp;
		}
		break;
	case 3: // += 3
		for (size_t i = 0; i < len; i++) {
			if ('a' <= buf[i] && buf[i] <= 'z') {
				int x = buf[i];
				x = (x-'a'+3)%26+'a';
				buf[i] = x;
			}
			if ('A' <= buf[i] && buf[i] <= 'Z') {
				int x = buf[i];
				x = (x-'A'+3)%26+'A';
				buf[i] = x;
			}
			if ('0' <= buf[i] && buf[i] <= '9') {
				int x = buf[i];
				x = (x-'0'+3)%10+'0';
				buf[i] = x;
			}
		}
		break;
	case 4: // swap adjacent
		for (size_t i = 0; i + 2 <= len; i += 2) {
			unsigned char tmp = buf[i + 1];
			buf[i + 1] = buf[i];
			buf[i] = tmp;
		}
		break;
	case 5: // erase numbers
		for (size_t i = 0; i < len; i++) {
			if ('0' <= buf[i] && buf[i] <= '9')
				buf[i] = 'X';
		}
		break;
	case 6: // bee movie script
		{
			const char *str =
				"According_to_all_known_laws_of_aviation_there_is_no_way_a_bee_should_be_able_to_fly__"
				"Its_wings_are_too_small_to_get_its_fat_little_body_off_the_ground__"
				"The_bee_of_course_flies_anyway_because_bees_dont_care_what_humans_think_is_impossible__"
				"Yellow_black_Yellow_black_Yellow_black_Yellow_black__"
				"Ooh_black_and_yellow__"
				"Lets_shake_it_up_a_little__"
				"Barry_Breakfast_is_ready__"
				"Coming____";
			const size_t sz = strlen(str);
			for (size_t i = 0; i < len; i++)
				buf[i] = str[i % sz];
		}
		break;
	case 7: // fill with first
		for (size_t i = 1; i < len; i++)
			buf[i] = buf[0];
		break;
	case 8: // fill with last
		for (size_t i = 0; i + 1 < len; i++)
			buf[i] = buf[len - 1];
		break;
	case 0xfea1dead00000001: // = 18348191191494819841, fill with a
		for (size_t i = 0; i < len; i++)
			buf[i] = 'a';
		break;
	default:
		return -1;
	}
	return 0;
}

void handle_magic_syscall(pid_t child, struct user_regs_struct *regs)
{
	iprintf("magic syscall!\n");
	long op = (long)regs->rdi;
	void *addr = (void *)regs->rsi;
	ssize_t len = (size_t)regs->rdx;
	unsigned char *buf = 0;
	long ret = 0;

	if (len < 0) {
		ret = -EINVAL;
		goto end;
	}

	if (len == 0) {
		ret = 0;
		goto end;
	}

	if ((buf = malloc(len)) == 0) {
		ret = -errno;
		goto end;
	}

	// We could use ptrace(PTRACE_PEEKDATA, ...) instead of
	// process_vm_readv but it isn't a good idea to make O(len) syscalls
	{
		struct iovec local = { .iov_base = buf, .iov_len = len };
		struct iovec remote = { .iov_base = addr, .iov_len = len };
		ssize_t ret2  = process_vm_readv(child, &local, 1, &remote, 1, 0);
		//iprintf("readv: len = %ld, ret2 = %ld\n", len, ret2);
		if (ret2 == -1) {
			ret = -errno;
			goto end;
		}
		if (ret2 != len) {
			ret = -EFAULT;
			goto end;
		}
	}

	if (perform_operation(op, buf, len) == -1) {
		ret = -EINVAL;
		goto end;
	}

	// Same as process_vm_readv
	{
		struct iovec local = { .iov_base = buf, .iov_len = len };
		struct iovec remote = { .iov_base = addr, .iov_len = len };
		ssize_t ret2  = process_vm_writev(child, &local, 1, &remote, 1, 0);
		//iprintf("writev: len = %ld, ret2 = %ld\n", len, ret2);
		if (ret2 == -1) {
			ret = -errno;
			goto end;
		}
		if (ret2 != len) {
			ret = -EFAULT;
			goto end;
		}
	}

	ret = 0;

end:
	if (buf)
		free(buf);
	if (ptrace(PTRACE_POKEUSER, child, RAX * 8, (void *)ret) == -1)
		err("ptrace pokeuser");

	iprintf("magic syscall done with ret = %ld\n", ret);
}

void usage(const char *prog_name)
{
	fprintf(stderr, "Usage: %s [-q] <program>\n", prog_name);
	exit(2);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		usage(argv[0]);

	// argument handling is a complete hack at the moment
	char **ptr = argv + 1;
	while (*ptr) {
		if ((*ptr)[0] != '-')
			break;
		if (!strcmp(*ptr, "-q"))
			quiet = 1;
		ptr++;
	}
	if (!*ptr)
		usage(argv[0]);

	pid_t child = fork();

	if (child == -1) {
		perror("fork failed");
		return 1;
	}

	if (child == 0) {
		// child process
		if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
			err("ptrace traceme");
		execv(*ptr, ptr);
		err("execv");
	}

	int status;
	if (waitpid(child, &status, 0) == -1) // exec causes sigtrap, sync with it
		err("waitpid (probably bad argument)");
	if (!WIFSTOPPED(status) || WSTOPSIG(status) != SIGTRAP) {
		fprintf(stderr, "expected sigtrap but didn't catch. bad arguments?\n");
		exit(1);
	}

	// EXITKILL causes the child to die if we get killed
	// TRACESYSGOOD causes the stop signal to be (SIGTRAP|0x80) when it is from a syscall
	if (ptrace(PTRACE_SETOPTIONS, child, 0, (void *)(PTRACE_O_EXITKILL | PTRACE_O_TRACESYSGOOD)) == -1)
		err("ptrace setoptions");

	long signo = 0;

	for (;;) {
		// wait for syscall
		if (ptrace(PTRACE_SYSCALL, child, 0, (void *)signo) == -1)
			err("ptrace");
		if (waitpid(child, &status, 0) == -1)
			err("waitpid");

		signo = 0;

		if (WIFEXITED(status)) {
			iprintf("child exited with %d\n", WEXITSTATUS(status));
			exit(WEXITSTATUS(status));
		}

		if (WIFSIGNALED(status)) {
			iprintf("child terminated with signal %d\n", WTERMSIG(status));
			// https://stackoverflow.com/questions/1101957/are-there-any-standard-exit-status-codes-in-linux
			exit(128 + WTERMSIG(status));
		}

		assert(WIFSTOPPED(status));

		if (WSTOPSIG(status) != (SIGTRAP|0x80)) { // it isn't a syscall trap
			iprintf("child stopped with signal %d\n", WSTOPSIG(status));
			signo = WSTOPSIG(status);
			continue;
		}

		/* Gather system call arguments */
		struct user_regs_struct regs0;
		if (ptrace(PTRACE_GETREGS, child, 0, &regs0) == -1)
			err("ptrace reg");
		long syscall = regs0.orig_rax;

		/* Run system call and stop on exit */
		if (ptrace(PTRACE_SYSCALL, child, 0, 0) == -1)
			err("ptrace 2");
		if (waitpid(child, 0, 0) == -1)
			err("waitpid 2");

		/* Get system call result */
		struct user_regs_struct regs1;
		if (ptrace(PTRACE_GETREGS, child, 0, &regs1) == -1) {
			if (errno == ESRCH) {
				iprintf("normal exit with code %llu\n", regs0.rdi & 0xff);
				exit(regs0.rdi); // system call was _exit(2) or similar
			}
			err("ptrace reg 2");
		}

		/* Special handling for our syscall */
		if (syscall == 0xFACADE)
			handle_magic_syscall(child, &regs0);
	}
}
