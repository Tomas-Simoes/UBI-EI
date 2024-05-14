org 100h

escrita equ 40h
ecra equ 1
terminar equ 4ch
abrirficheiro equ 3dh
lerfile equ 3fh
fecharfile equ 3eh

;abrir ficheiro
mov ah, abrirficheiro
mov al, 0; 0 = abrir pra leitura, 1 = abrir pra escrita, 2 = leitura e escrita
mov dx, nomefile
int 21h

mov [handle], ax

; ler conteudo do ficheiro
mov ah, lerfile
mov bx, [handle]
mov cx, 18
mov dx, msg
int 21h

; fechar ficheiro
mov ah, fecharfile
int 21h

; escrever no ecra o conteudo do ficheiro
mov ah, escrita
mov bx, ecra
mov cx, 18
mov dx, msg
int 21h

;

mov ah, terminar
int 21h

msg rb 18
nomefile db 'teste.txt', 0
handle rw 1