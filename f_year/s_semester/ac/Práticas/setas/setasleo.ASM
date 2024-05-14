org 100h
leitura equ 07h
terminar equ 4ch

mov ah, 4FH
mov al, 02
mov bx, 13h
int 10h

mov [coutcoluna], 319
mov [coutlinha], 199
mov [coutdiagonalcoluna], 0
mov [coutdiagonallinha], 0

ciclo:
mov ah, 0ch
mov al, 3
mov bh, 0
mov cx, [coutcoluna]
mov dx, 10
int 10h
dec [coutcoluna]
jnz ciclo

coluna:
mov ah, 0ch
mov al, 3
mov bh, 0
mov cx, 10
mov dx, [coutlinha]
int 10h
dec [coutlinha]
jnz coluna

diagonal:
mov ah, 0ch
mov al, 3
mov bh, 0
mov cx, [coutdiagonalcoluna]
mov dx, [coutdiagonallinha]
int 10h
inc [coutdiagonalcoluna]
inc [coutdiagonallinha]
jnz diagonal

mov ah, leitura
int 21h
mov ah, terminar
int 21h

coutlinha rw 1
coutcoluna rw 1
coutdiagonalcoluna rw 1
coutdiagonallinha rw 1