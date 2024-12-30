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
#define err(str) do { perror("emulation error: " __FILE__ ":" TOSTRING(__LINE__) ": " str); exit(1); } while (0)

/*
 * Change this function to add your own operation!
 * note that this function must return 0 if magic_number is valid
 * otherwise it must return -1
 */
int perform_operation(long magic_number, unsigned char *buf, size_t len)
{
	switch (magic_number) {
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
	default:
		return -1;
	}
	return 0;
}

void handle_magic_syscall(pid_t child, struct user_regs_struct *regs)
{
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

	{
		struct iovec local = { .iov_base = buf, .iov_len = len };
		struct iovec remote = { .iov_base = addr, .iov_len = len };
		ssize_t ret2  = process_vm_readv(child, &local, 1, &remote, 1, 0);
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

	{
		struct iovec local = { .iov_base = buf, .iov_len = len };
		struct iovec remote = { .iov_base = addr, .iov_len = len };
		ssize_t ret2  = process_vm_writev(child, &local, 1, &remote, 1, 0);
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
}

void usage(const char *prog_name)
{
	fprintf(stderr, "Usage: %s <program>\n", prog_name);
	exit(2);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		usage(argv[0]);

	char **ptr = argv + 1;
	if (!*ptr)
		usage(argv[0]);

	pid_t child = fork();

	if (child == -1) {
		perror("fork failed");
		return 1;
	}

	if (child == 0) {
		if (ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
			err("ptrace traceme");
		execv(*ptr, ptr);
		err("execv");
	}

	int status;
	if (waitpid(child, &status, 0) == -1)
		err("waitpid (probably bad argument)");
	if (!WIFSTOPPED(status) || WSTOPSIG(status) != SIGTRAP) {
		exit(1);
	}

	if (ptrace(PTRACE_SETOPTIONS, child, 0, (void *)(PTRACE_O_EXITKILL | PTRACE_O_TRACESYSGOOD)) == -1)
		err("ptrace setoptions");

	long signo = 0;

	for (;;) {
		if (ptrace(PTRACE_SYSCALL, child, 0, (void *)signo) == -1)
			err("ptrace");
		if (waitpid(child, &status, 0) == -1)
			err("waitpid");

		signo = 0;

		if (WIFEXITED(status)) {
			exit(WEXITSTATUS(status));
		}

		if (WIFSIGNALED(status)) {
			fprintf(stderr, "%s\n", strsignal(WTERMSIG(status)));
			exit(128 + WTERMSIG(status));
		}

		assert(WIFSTOPPED(status));

		if (WSTOPSIG(status) != (SIGTRAP|0x80)) {
			signo = WSTOPSIG(status);
			continue;
		}

		struct user_regs_struct regs0;
		if (ptrace(PTRACE_GETREGS, child, 0, &regs0) == -1)
			err("ptrace reg");
		long syscall = regs0.orig_rax;

		if (ptrace(PTRACE_SYSCALL, child, 0, 0) == -1)
			err("ptrace 2");
		if (waitpid(child, 0, 0) == -1)
			err("waitpid 2");

		struct user_regs_struct regs1;
		if (ptrace(PTRACE_GETREGS, child, 0, &regs1) == -1) {
			if (errno == ESRCH)
				exit(regs0.rdi);
			err("ptrace reg 2");
		}

		if (syscall == 0xFACADE)
			handle_magic_syscall(child, &regs0);
	}
}
