org 100h

escrita equ 40h
ecra equ 1
leitura equ 07h
terminar equ 4ch
Esc equ 27

obliqua rw 1
linha rw 1
coluna rw 1

cor rb 1
msg db 'Tipo de reta?'
sentido rb 1
mensagem_erro db 'Tecla invalida, pressione "d" para seta � direita, "e" para seta � esquerda ou Esc para sair.', 0

; Modo Grafico
mov ah,4fh
mov al,02
mov bx,13h
int 10h

mov [cor], 2

; Write msg
mov ah, escrita
mov bx, ecra
mov cx, 13
mov dx, msg
int 21h

; Read key
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

jmp erro ; Se a tecla n�o for 'e', 'd' ou Esc, vai para erro
jmp le_tecla ; Volta para ler a pr�xima tecla

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
mov cx, 18 ; Posi��o da coluna para centralizar a mensagem de erro
mov dx, mensagem_erro
int 21h
jmp le_tecla ; Espera o usu�rio pressionar outra tecla

desenha_seta_esquerda:
mov [coluna], 80
ciclo:
mov ah, 0ch
mov al, 2
mov bh, 0
mov cx, [coluna]
mov dx, 50
int 10h
dec [coluna] ; Decrementa a coluna para desenhar para a esquerda
jnz ciclo
ret

desenha_seta_direita:
mov [coluna], 80
ciclo1:
mov ah, 0ch
mov al, 2
mov bh, 0
mov cx, [coluna]
mov dx, 50
int 10h
inc [coluna] ; Incrementa a coluna para desenhar para a direita
jnz ciclo1
call desenha_diagonal
ret

desenha_diagonal:
mov [coluna], 80
mov [linha], 80
ciclo2:
mov ah, 0ch
mov al, 2
mov bh, 0
mov cx, [coluna]
mov dx, [linha]
int 10h
dec [coluna]
dec [linha]
jnz ciclo2
