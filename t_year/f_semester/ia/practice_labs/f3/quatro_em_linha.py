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
        if(row_count == 4):
            print()
            row_count = 0


# ------------------------------------------------------------------
# devolve a lista de ações que se podem executar partido de um estado
def acoes(T):
    acoes = []

    for i, x in reversed(list(enumerate(T))): 
        if x == 0:
            if i+4 >= len(T) or T[i+4] != 0:
                acoes.append(i)
   
    return acoes

# ------------------------------------------------------------------
# devolve o estado que resulta de partir de um estado e executar uma ação
def resultado(T, a, jogador):
    # aux fica com cópia do tabuleiro
    aux = copy.copy(T)

    aux[a] = 1 if jogador == "MAX" else -1 

    return aux

# ------------------------------------------------------------------
# existem 8 possíveis alinhamentos vencedores, para cada jogador
def utilidade(T):
    # testa as linhas
    for i in range(3):
        max_win = 0
        min_win = 0

        for j in range(4):
            if T[i * 4 + j] == 1:
                max_win += 1
            elif T[i * 4 + j] == -1:
                min_win += 1
                
            if max_win == 4: return 1       # vitoria max
            elif min_win == 4: return -1    # vitoria min

    # testa as colunas
    for j in range(4):
        max_win = 0
        min_win = 0

        for i in range(3):
            if T[i * 4 + j] == 1:
                max_win += 1
            elif T[i * 4 + j] == -1:
                min_win += 1
                
            if max_win == 3: return 1       # vitoria max
            elif min_win == 3: return -1    # vitoria min

    # testa as diagonais
    max_win = 0
    min_win = 0
    for i in range(4):                      # main diagonal
        if i == 3:
            if T[2 * 4 + i] == 1:
                max_win += 1
            elif T[2 * 4 + i] == -1:
                min_win += 1
        else:
            if T[i * 4 + i] == 1:
                max_win += 1
            elif T[i * 4 + i] == -1:
                min_win += 1
            
        if max_win == 4: return 1       # vitoria max
        elif min_win == 4: return -1    # vitoria min

    max_win = 0
    min_win = 0
    for i,j in zip(range(3), reversed(range(4))): # inverted diagonal
        if T[i * 4 + j] == 1:
            max_win += 1
        elif T[i * 4 + j] == -1:
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
        return utilidade(T),-1,-1
    if jogador == 'MAX':
        v = -10
        ba=-1
        for a in acoes(T):
            v1, ac, es = alfabeta(resultado(T, a, 'MAX'), alfa, beta, 'MIN')
            if v1 > v: # guardo a ação que corresponde ao melhor
                v = v1
                ba = a
            alfa = max(alfa, v)
            if v >= beta:
                break
        return v, ba, resultado(T, ba, 'MAX')
    else:
        v = 10
        ba= -1
        for a in acoes(T):
            v1, ac, es = alfabeta(resultado(T, a, 'MIN'), alfa, beta, 'MAX')
            if v1 < v: # guardo a ação que corresponde ao melhor
                v = v1
                ba = a
            beta = min(beta, v)
            if v <= alfa:
                break
        return v, ba, resultado(T, ba, 'MIN')


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
    possible_choices = [i for i in range(len(T)) if T[i] == 0 and (i+4 >= len(T) or T[i+4] != 0)]
    
    if possible_choices: 
        i = random.choice(possible_choices)
        T[i] = 1

    print('RAND joga para ', i)  

    return T

# ------------------------------------------------------------------
# jogador aleatório
def joga_humano(T):
    i = int(input("Insira a coordenada: "))

    while T[i] != 0:
        print("Jogada inválida!")
        i = int(input("Insira a coordenada x: "))

    T[i] = -1

    print('HUMANO joga para ', (i,j))  

    return T


# ------------------------------------------------------------------
def jogo(p1, p2):
    # cria tabuleiro vazio
    T = [0,0,0,0,0,0,0,0,0,0,0,0]
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
        print('Venceu o jogador 1')
        return 1
    elif utilidade(T) == -1:
        print('Venceu o jogador 2')
        return -1
    else:
        print('Empate')
        return 0



# ------------------------------------------------------------------
# main
res_arr = [0,0,0]
# deve ganhar (quase) sempre o max:
for i in range(1000):
    res = jogo(joga_max,joga_min)
    res_arr[res] += 1

print("Jogador MAX ganhou", res_arr[0])
print("Jogador MIN ganhou", res_arr[2])
print("Empates:", res_arr[1])

# devem empatar sempre:
#jogo(joga_max,joga_min)


