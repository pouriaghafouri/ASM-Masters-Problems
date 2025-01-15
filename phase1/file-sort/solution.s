# "This solution was written by AH MZ"

#==============================================
    # ASM Masters - Code of Question "Sort"
    # IBM S390x Architecture Assembly Language
    # Description: This Program reads a string from "input.txt",
    # sorts the string and writes the sorted string to "output.txt"
#==============================================

############## Macro: call <label> ##############
# <label> : The label of the function to be called.
# This macro call a function using calling convention of S390x architecture.
.macro call func
    lay   %r15, -160(%r15)                  # Allocate stack frame for calling function
    brasl %r14, \func                       # Call the function
    lay   %r15, 160(%r15)                   # Disallocate stack frame of called function
.endm

################# Macro: ret ####################
# This macro returns to the caller function.
.macro ret
    br %r14                                 # Return to the caller
.endm

######## Macro: enter [size=0] [first=6] ########
# [size=0] : The number of 64-bit local variables to be allocated in stack.
# [first=6] : The first register number to be saved in stack.
# This macro allocates space in stack for local variables,
# and saves the registers from r[x] to r[15] in stack frame allocated by caller
.macro enter size=0 first=6
    stmg %r\first, %r15, \first*8(%r15)
    lay %r15, -\size*8(%r15)
.endm

####### Macro: leave [size=0] [first=6] ########
# [size=0] : The number of 64-bit local variables to be deallocated in stack.
# [first=6] : The first register number to be restored from stack.
# This macro deallocates space in stack for local variables,
# and restores the registers from r[x] to r[15] from stack frame
.macro leave size=0 first=6
    lay %r15, \size*8(%r15)                 # Disallocate local variables in stack
    lmg %r\first, %r15, \first*8(%r15)      # Restore r6 - r15
.endm

############# Macro: push <srcreg> #############
# <srcreg> : The register to be pushed in stack.
# This macro pushes the value of register <srcreg> in stack.
.macro push srcreg
    lay %r15, -8(%r15)
    stg \srcreg, 0(%r15)
.endm

############ Macro: pop <dstreg> ###############
# <dstreg> : The register to be popped from stack.
# This macro pops the value from stack and stores in register <dstreg>.
.macro pop dstreg
    lg \dstreg, 0(%r15)
    lay %r15, 8(%r15)
.endm

########### Linux System Call Macros ###########
.macro sys_exit   ; svc 1  ; .endm   # void _exit(int status);
.macro sys_read   ; svc 3  ; .endm   # ssize_t read(int fd, void buf[.count], size_t count);
.macro sys_write  ; svc 4  ; .endm   # ssize_t write(int fd, const void buf[.count], size_t count);
.macro sys_open   ; svc 5  ; .endm   # int open(const char *filename, int flags, mode_t mode);
.macro sys_close  ; svc 6  ; .endm   # int close(int fd);
.macro sys_creat  ; svc 8  ; .endm   # int creat(const char *filename, mode_t mode);
.macro sys_chdir  ; svc 12 ; .endm   # int chdir(const char *path);
.macro sys_rename ; svc 38 ; .endm   # int rename(const char *oldpath, const char *newpath);
.macro sys_mkdir  ; svc 39 ; .endm   # int mkdir(const char *pathname, mode_t mode);

.eqv STDIN,  0
.eqv STDOUT, 1
.eqv STDERR, 2

###### Macro fprint: <fd> in %r2, <buf> in %r3 ######
.macro fprint
    lgfi %r4, -1
1:  lb %r5, 1(%r4, %r3)
    agfi %r4, 1
    clijne %r5, 0, 1b
    sys_write
.endm

###### Macro fread: <fd> in %r2, <buf> in %r3, <max_size> in %r4 ######
.macro fread
    lgr   %r5, %r2
1:  sys_read
    cije  %r2, 0, 2f
    agr   %r4, %r2
    agr   %r3, %r2
    lgr   %r2, %r5
    cijne %r4, 0, 1b
    lgfi  %r2, 0
2:  stc   %r2, 0(%r3)
.endm

################################################################

# Begin of data section
.data
    .align 8
    input_path: .asciz "input.txt"
    .align 8
    output_path: .asciz "output.txt"
    .align 8
    buffer: .zero 100000                            # Buffer to store the content
    .align 8

# Begin of text section
.text
.global main
main:
    call _main
    sys_exit

################################################################
_main:
    enter 1

    # Open the input file
    larl %r2, input_path          # input.txt
    lgfi %r3, 0                   # O_RDONLY
    sys_open
    stg  %r2, 0(%sp)              # Store fd in local variable

    # Read the content of the input file
    larl %r3, buffer
    lgfi %r4, 1024
    fread

    # Close the input file
    lg   %r2, 0(%sp)
    sys_close
    
    # Sort the buffer
    larl %r2, buffer
    call sort

    # Open the output file
    larl %r2, output_path         # output.txt
    lgfi %r3, 0101                # O_CREAT | O_WRONLY
    lgfi %r4, 0777                # Mode 0777 (rwxrwxrwx)
    sys_open
    stg  %r2, 0(%sp)              # Store fd in local variable

    # Write the output
    larl %r3, buffer
    fprint

    # Close the output file
    lg   %r2, 0(%sp)
    sys_close

    leave 1
    xgr %r2, %r2
    ret

################################################################
sort:
    enter
    lgfi  %r3, 0                  # Init master counter
    llc %r0, 0(%r2)               # Load the first character
    .loop:
        # %r0 containing current character. searching this and insert
        lgfi %r1, -1              # Init search counter to zero
        lgr %r5, %r3              # Init insert counter to curr index
        .search:
            agfi %r1, 1
            clije %r0, '\n, .insert_end  # Skip inserting \n at beginning of file
            crjhe %r1, %r3, .insert_end  # Insert the character here if we reach master index
            llc %r4, 0(%r1, %r2)
            crjhe %r0, %r4, .search 
        # We should insert %r0 into index %r1
        .insert:
            agfi %r5, -1
            llc %r4, 0(%r5, %r2)
            stc %r4, 1(%r5, %r2)
            crjne %r5, %r1, .insert
        stc %r0, 0(%r1, %r2)
        .insert_end:
        agfi %r3, 1
        llc %r0, 0(%r3, %r2)
        clijne %r0, 0, .loop
    leave
    ret

