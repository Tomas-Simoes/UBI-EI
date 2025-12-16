'''
IA UBI
ex3

usando pyagrum
http://www-desir.lip6.fr/~phw/aGrUM/docs/last/notebooks/Tutorial.ipynb.html
https://pyagrum.readthedocs.io/en/0.22.2/

sudo pip3 install pyagrum

ou

pip3 install pyagrum

'''
import pyagrum as gum

def mostra(d, q):
    # mostra resultado do query q, dadas as observações d
    global ie
    ie.setEvidence(d)
    ie.makeInference()
    print (ie.posterior(q))

bn=gum.BayesNet('RelvaMolhada')

# criar nodos
chuva=bn.add(gum.LabelizedVariable('chuva','chuva',2))
aspersor=bn.add(gum.LabelizedVariable('aspersor','aspersor ligado',2))
relva=bn.add(gum.LabelizedVariable('relva','relva molhada',2))

# criar arestas
bn.addArc(chuva,aspersor)
# COMPLETAR

# colocar tabelas de probabilidade nos nodos
bn.cpt(chuva)[{}] = [0.8,0.2]

bn.cpt(aspersor)[{'chuva': 0}] = [0.6, 0.4]
bn.cpt(aspersor)[{'chuva': 1}] = [0.99, 0.01]

bn.cpt(relva)[{'chuva': 0, 'aspersor': 0}] = [1, 0]
bn.cpt(relva)[{'chuva': 0, 'aspersor': 1}] = [0.2, 0.8]
bn.cpt(relva)[{'chuva': 1, 'aspersor': 0}] = [0.1, 0.9]
bn.cpt(relva)[{'chuva': 1, 'aspersor': 1}] = [0.01, 0.99]


ie=gum.LazyPropagation(bn)

# 3a: Qual é a probabilidade de a relva não estar molhada?
# COMPLETAR
mostra({}, 'relva')

# 3b: Qual é a probabilidade de estar a chover dado que observamos a relva molhada?
# COMPLETAR
mostra({"relva": 1}, 'chuva')

# 3c: Qual é a probabilidade de o aspersor estar desligado dado que a relva não está molhada e não está a chover?
# COMPLETAR
mostra({"relva": 0, "chuva":0 }, "aspersor")
