org 100h

escrita equ 40h
leitura equ 07h
terminar equ 4ch
ecra equ 1
caracteres equ 1

mov [cout], 20

ciclo:

mov ax, [cout]
mov bl, 10
div bl
mov [quociente], al
mov [resto], ah

add [quociente], 48
mov ah, escrita
mov bx, ecra
mov cx, caracteres
mov dx, quociente
int 21h

add [resto], 48
mov ah, escrita
mov bx, ecra
mov cx, caracteres
mov dx, resto
int 21h

dec [cout]
jnz ciclo

mov ah, leitura
int 21h

mov ah, terminar
int 21h

msg db "UBI", 10
cout rw 1
quociente rb 1
resto rb 1