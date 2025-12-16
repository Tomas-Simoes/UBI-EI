'''
IA
UBI
ex1

usando pyagrum
https://pyagrum.readthedocs.io/en/stable/

sudo pip3 install pyagrum

ou

pip3 install pyagrum

ou 

pip install pyagrum

portas: A, B e C
'''
import pyagrum as gum

def mostra(d, q):
    # mostra resultado do query q, dadas as observações d
    global ie
    ie.setEvidence(d)
    ie.makeInference()
    print (ie.posterior(q))

def prob_monty(guest,prize):
   # define probabilidade de o monty escolher abrir cada porta, sabendo quais foram as outras 2 escolhas: devolve uma lista com a prob de abrir cada porta
    p = []
    doors = ['A','B','C']

    for monty in doors:
        if guest == monty or prize == monty:
            p.append(0)
        elif guest == prize:
            p.append(1/2)
        else:
            p.append(1/(len(doors) - 2))

    return p


bn=gum.BayesNet('MontyHall')

# criar nodos
guest=bn.add(gum.LabelizedVariable('guest','guest',['A','B','C']))
prize=bn.add(gum.LabelizedVariable('prize','prize',['A','B','C']))
monty=bn.add(gum.LabelizedVariable('monty','monty',['A','B','C']))

# criar arestas
bn.addArc(guest,monty)
bn.addArc(prize,monty)

# colocar tabelas de probabilidade no nodos
# o convidado escolhe uma porta aleatóriamente
bn.cpt(guest)[{}] = [1./3,1./3,1./3]
# a porta que tem o prémio também pode ser qualquer
bn.cpt(prize)[{}] = [1./3,1./3,1./3]
# a porta escolhida pelo Monty depende das portas do guest e do prize
for i in ['A','B','C']:
    for j in ['A','B','C']:
        bn.cpt(monty)[{'guest': i, 'prize': j}] = prob_monty(i,j)

ie=gum.LazyPropagation(bn)

# passar os valores observados para algumas variáveis e ele estima a probabilidade das restantes

# exemplo: se o guest escolher a porta B e o prémio estiver na porta A, qual a prob de o monty escolher as várias portas?
mostra({ 'guest' : 'B' , 'prize' : 'A'}, 'monty')

# COMPLETAR
