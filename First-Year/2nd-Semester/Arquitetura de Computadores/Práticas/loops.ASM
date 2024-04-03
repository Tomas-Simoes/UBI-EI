org 100h

write equ 40h
read equ 07h
end equ 4ch

mov [count], 20

_loop:
mov ah, write
mov bx, 1
mov cx, 4
mov dx, msg
int 21h

dec [count]
jnz _loop

mov ah, read
int 21h

mov ah, end
int 21h

msg db 'UBI', 10
count rb 1          