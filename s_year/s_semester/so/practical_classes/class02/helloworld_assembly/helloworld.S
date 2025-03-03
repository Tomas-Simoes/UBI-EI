.data #initialized data section

msg:
 .ascii "Ola Mundo\n" #ascii string
 len = . - msg #number of bytes of the string
.text
 .global _start

_start:
 movq $1, %rax #system call number 1 is write
 movq $1, %rdi #file descriptor of standard output is 1
 movq $msg, %rsi #message address
 movq $len, %rdx #number of bytes
 syscall #raise system call interrupt write(...)

 movq $60, %rax #system call number 60 is exit
 movq $1, %rdi #exit status code can be caught in bash with $?
 syscall #exit(1)