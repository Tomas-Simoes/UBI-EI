org 100h

escrita equ 40h
ecra equ 1
leitura equ 07h
terminar equ 4ch
Esc equ 27

pontos rb 1
obliqua rw 1
linha rw 1
coluna rw 1
cor rb 1
msg db 'Tipo de reta?'
sentido rb 1
mensagem_erro db 'Tecla inválida! Pressione "d" para seta à direita, "e" para seta à esquerda ou Esc para sair.', 0

mov ah,4fh
mov al,02
mov bx,13h
int 10h

mov [cor], 2

mov ah, escrita
mov bx, ecra
mov cx, 13
mov dx, msg
int 21h

le_tecla:
mov ah, leitura
int 21h

mov [sentido], al

cmp [sentido], Esc ; Se for a tecla "Esc", sai do programa
je sair

cmp [sentido], 'e' ; Tecla 'e' pressionada
je seta_esquerda

cmp [sentido], 'd' ; Tecla 'd' pressionada
je seta_direita

jmp erro ; Se a tecla não for 'e', 'd' ou Esc, vai para erro
jmp le_tecla ; Volta para ler a próxima tecla

termino:
mov ah, leitura
int 21h

sair:
mov ah, terminar
int 21h

seta_esquerda:
call desenha_seta_esquerda
jmp termino

seta_direita:
call desenha_seta_direita
jmp termino

erro:
mov ah, escrita
mov bx, ecra
mov cx, 18 ; Posição da coluna para centralizar a mensagem de erro
mov dx, mensagem_erro
int 21h
jmp le_tecla ; Espera o usuário pressionar outra tecla

desenha_seta_esquerda:
mov [coluna], 80
mov [pontos], 100
ciclo_esquerda:
mov ah, 0ch
mov al, 2
mov bh, 0
mov cx, [coluna]
mov dx, 50
int 10h
dec [coluna] ; Decrementa a coluna para desenhar para a esquerda
dec [pontos]
jnz ciclo_esquerda
ret

desenha_seta_direita:
mov [coluna], 80
mov [pontos], 100
ciclo_direita:
mov ah, 0ch
mov al, 2
mov bh, 0
mov cx, [coluna]
mov dx, 50
int 10h
inc [coluna] ; Incrementa a coluna para desenhar para a direita
dec [pontos]
jnz ciclo_direita
ret

