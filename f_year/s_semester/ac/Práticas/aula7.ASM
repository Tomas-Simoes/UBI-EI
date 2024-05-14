org 100h

criarfile equ 3ch
escrita equ 40h
ecra equ 1
fecharfile equ 3eh
terminar equ 4ch


;criar ficheiro
mov ah, criarfile
mov cx, 0 ;0 = ficheiro normal
mov dx, nomefile
int 21h

mov [handle], ax

;escrever dentro ficheiro
mov ah, escrita
mov bx, [handle]
mov cx, 18
mov dx, msg
int 21h

;fixa file

mov ah, fecharfile
mov bx, [handle]
int 21h

;terminar

mov ah, terminar
int 21h

msg db 'alo estas ocupada?'
nomefile db 'teste.txt', 0
handle rw 1