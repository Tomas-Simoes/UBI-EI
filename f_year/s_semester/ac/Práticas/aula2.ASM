org 100h

escrita equ 40h
leitura equ 07h
terminar equ 4ch
ecra equ 1
caracteres equ 1

mov [cout], 5

ciclo:
add [cout], 48

mov ah, escrita
mov bx, ecra
mov cx, caracteres
mov dx, cout
mov dx, cout
int 21h

sub [cout], 48
dec [cout]
jnz ciclo

mov ah, leitura
int 21h

mov ah, terminar
int 21h

msg db "UBI", 10
cout rb 1