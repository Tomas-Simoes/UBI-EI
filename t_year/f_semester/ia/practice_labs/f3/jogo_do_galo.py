"""
Esqueleto para o exercício 1 da ficha 3.
IA -- UBI
"""
import copy, random

# ------------------------------------------------------------------
def mostra_tabuleiro(T):
    row_count = 0
    
    for x in T: 
        if x == -1: 
            print("X", end=" ")
        elif x == 1:
            print("O", end=" ")
        elif x == 0:
            print(".", end=" ")
        
        row_count += 1
        if(row_count == 3):
            print()
            row_count = 0


# ------------------------------------------------------------------
# devolve a lista de ações que se podem executar partido de um estado
def acoes(T):
    acoes = []

    for i, x in enumerate(T): 
        if x == 0:
            acoes.append((i // 3, i % 3))
        
    return acoes

# ------------------------------------------------------------------
# devolve o estado que resulta de partir de um estado e executar uma ação
def resultado(T, a, jogador):
    # aux fica com cópia do tabuleiro
    aux = copy.copy(T)

    x,y = a 
    aux[x * 3 + y] = 1 if jogador == "MAX" else -1 

    return aux

# ------------------------------------------------------------------
# existem 8 possíveis alinhamentos vencedores, para cada jogador
def utilidade(T):
    # testa as linhas
    for i in range(3):
        max_win = 0
        min_win = 0

        for j in range(3):
            if T[i * 3 + j] == 1:
                max_win += 1
            elif T[i * 3 + j] == -1:
                min_win += 1
                
            if max_win == 3: return 1       # vitoria max
            elif min_win == 3: return -1    # vitoria min

    # testa as colunas
    for j in range(3):
        max_win = 0
        min_win = 0

        for i in range(3):
            if T[i * 3 + j] == 1:
                max_win += 1
            elif T[i * 3 + j] == -1:
                min_win += 1
                
            if max_win == 3: return 1       # vitoria max
            elif min_win == 3: return -1    # vitoria min

    # testa as diagonais
    max_win = 0
    min_win = 0
    for i in range(3):                      # main diagonal
        if T[i * 3 + i] == 1:
            max_win += 1
        elif T[i * 3 + i] == -1:
            min_win += 1
        
        if max_win == 3: return 1       # vitoria max
        elif min_win == 3: return -1    # vitoria min

    max_win = 0
    min_win = 0
    for i,j in zip(range(3), reversed(range(3))): # inverted diagonal
        if T[i * 3 + j] == 1:
            max_win += 1
        elif T[i * 3 + j] == -1:
            min_win += 1
        
        if max_win == 3: return 1       # vitoria max
        elif min_win == 3: return -1    # vitoria min
    

    # não é nodo folha ou dá empate
    return 0

# ------------------------------------------------------------------
# devolve True se T é terminal, senão devolve False
def estado_terminal(T):
    util_T = utilidade(T)
    if util_T == 1 or util_T == -1 or all(x != 0 for x in T):
        return True 

    return False 


# ------------------------------------------------------------------
# algoritmo da wikipedia (fail-soft version adaptada)
# https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
# ignoramos a profundidade e devolvemos o valor, a ação e o estado resultante
def alfabeta(T, alfa, beta, jogador):
    if estado_terminal(T):
        return utilidade(T), -1, -1
    
    if jogador == 'MAX':
        v = -10
        melhor_acao = -1
        for a in acoes(T):
            v1, ac, es = alfabeta(resultado(T, a, 'MAX'), alfa, beta, 'MIN')
            if v1 > v:
                v = v1
                melhor_acao = a
            alfa = max(alfa, v)
            if v >= beta:
                break
        return v, melhor_acao, resultado(T, melhor_acao, 'MAX')
    else:
        v = 10
        melhor_acao = -1
        for a in acoes(T):
            v1, ac, es = alfabeta(resultado(T, a, 'MIN'), alfa, beta, 'MAX')
            if v1 < v:
                v = v1
                melhor_acao = a
            beta = min(beta, v)
            if v <= alfa:
                break
        return v, melhor_acao, resultado(T, melhor_acao, 'MIN')
# ------------------------------------------------------------------
def joga_max(T):
    # passamos o tabuleiro e valores iniciais para alfa e beta
    v, a, e = alfabeta(T, -10, 10, 'MAX')
    print('MAX joga para ',a)
    return e

# ------------------------------------------------------------------
def joga_min(T):
    v, a, e = alfabeta(T, -10, 10, 'MIN')
    print('MIN joga para ',a)  
    return e

# ------------------------------------------------------------------
# jogador aleatório
def joga_rand(T):
    possible_choises = [(i,j) for i in range(3) for j in range(3) if T[i*3+j] == 0]

    if possible_choises: 
        i,j = random.choice(possible_choises)
        T[i * 3 + j] = -1

    print('RAND joga para ', (i,j))  

    return T

# ------------------------------------------------------------------
# jogador aleatório
def joga_humano(T):
    i = int(input("Insira a coordenada x: "))
    j = int(input("Insira a coordenada y: "))

    while T[i*3+j] != 0:
        print("Jogada inválida!")
        i = int(input("Insira a coordenada x: "))
        j = int(input("Insira a coordenada y: "))

    T[i*3 + j] = -1

    print('HUMANO joga para ', (i,j))  

    return T


# ------------------------------------------------------------------
def jogo(p1, p2):
    # cria tabuleiro vazio
    T = [0,0,0,0,0,0,0,0,0]
    # podemos partir de um estado mais "avançado"
    #T = [1,-1,0,0,-1,0,1,0,0]
    mostra_tabuleiro(T)
    while acoes(T) != [] and not estado_terminal(T):
        T = p1(T)
        mostra_tabuleiro(T)
        if acoes(T) != [] and not estado_terminal(T):
            T = p2(T)
            mostra_tabuleiro(T)
    # fim
    if utilidade(T) == 1:
        print('Venceu o MAX')
    elif utilidade(T) == -1:
        print('Venceu o MIN')
    else:
        print('Empate')



# ------------------------------------------------------------------
# main

# deve ganhar (quase) sempre o max:
jogo(joga_max,joga_humano)

# devem empatar sempre:
#jogo(joga_max,joga_min)


