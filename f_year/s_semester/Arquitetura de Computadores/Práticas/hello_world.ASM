org 100h

mov ah, 40h
mov bx, 1
mov cx, 3
mov dx, msg
int 21h

mov ah, 07h
int 21h

mov ah, 4ch
int 21h

msg db 'UBI'