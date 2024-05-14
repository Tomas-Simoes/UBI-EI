org 100h

escrita equ 40h
leitura equ 07h
terminar equ 4ch
ecra equ 1
caracteres equ 4

mov cx, 5

ciclo:
call mensagem
loop  ciclo

mov ah, leitura
int 21h

mov ah, terminar
int 21h

mensagem:
        push cx
        mov ah, escrita
        mov bx, ecra
        mov cx, caracteres
        mov dx, msg
        int 21h
        pop cx
        ret


msg db "UBI", 10
cout rw 1