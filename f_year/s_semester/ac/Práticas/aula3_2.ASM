org 100h
escrita equ 40h
ecra equ 1
leitura equ 3fh
termina equ 4ch
teclado equ 0
ler equ 07h

mov ah, escrita
mov bx, ecra
mov cx, 7
mov dx, msg
int 21h

mov ah, leitura
mov bx, teclado
mov cx, 2
mov dx, valor, 10
int 21h

sub [valor], 48
mov al, [valor]
mul al
mov [resultado], ax

add [resultado], 48
mov ah, escrita
mov bx, ecra
mov cx, 1
mov dx, resultado
int 21h

mov ah, ler
int 21h
mov ah, termina
int 21h

msg db "Valor?", 10
valor rb 1
resultado rw 1