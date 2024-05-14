org 100h

criarfile equ 3ch
escrita equ 40h
ecra equ 1
fecharfile equ 3eh
terminar equ 4ch
abrirfile equ 3dh
lerfile equ 3fh

; abrir ficheiro
mov ah, abrirfile
mov al, 0
mov dx, nomefile
int 21h

jc sair

mov [handle], ax

;ler ficheiro letrinha por letrinha
leroutravez:
mov ah, lerfile
mov bx, [handle]
mov cx, 1
mov dx, msg
int 21h

cmp ax, 0

je fim

;mostrar letrinhas lidas
mov ah, escrita
mov bx, ecra
mov cx, 1
mov dx, msg
int 21h
jmp leroutravez

fim:
mov ah, fecharfile
mov bx, [handle]
int 21h

jmp cefini

sair:
mov ah, escrita
mov bx, ecra
mov cx, 34
mov dx, msgerro
int 21h

cefini:
mov ah, terminar
int 21h

msg rb 1
nomefile rb 1
msgerro db 'Estas a fim de ver nascer a manha?'
handle rw 1