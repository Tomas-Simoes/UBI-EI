org 100h

escrita equ 40h
leitura equ 07h
terminar equ 4ch
ecra equ 1
caracteres equ 4

mov cx, 10

ciclo:
call mensagem
call separar
loop  ciclo

mov cx, 20

ciclo1:
call mensagem
call separar
loop  ciclo1

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

separar:
        push cx
        mov ah, escrita
        mov bx, ecra
        mov cx, 11
        mov dx, separador
        int 21h
        pop cx
        ret


msg db "UBI", 10
separador db "__________", 10
cout rw 1