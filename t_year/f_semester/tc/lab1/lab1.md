# Laboratórios

Na aba Extensions do VS Code instalar a extensão

```
Dev Containers
Id: ms-vscode-remote.remote-containers
Description: Open any folder or repository inside a Docker container and take advantage of Visual Studio Code's full feature set.
Version: 0.384.0
Publisher: Microsoft
VS Marketplace Link: https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers
```

Na aba Remote Explorer carregar no link "installing Docker". Prosseguir com a instalação externa ao VS Code.

Depois de instalar o Docker na mesma aba devem conseguir agora construir o ambiente (baseado em  Debian) para o laboratório. No botão '+' adicionar o `.devcontainer` file da diretoria local.

Nota: Estas instruções tanto funcionam em Windows como em Linux (qualquer versão).


## Lab 1: Autómatos não deterministas com transições epsilon

Abrir um terminal no VS Code.


Executar o comando para compilar a aplicação:

```shell
$ ocamlc str.cma nfa.ml -o nfa
```

Agora vamos executar o binário que compilamos, mas dando-lhe como entrada o ficheiro `exemplo.nfa`. 

```shell
$ cat exemplo.nfa | ./nfa
```

Para isso utilizamos o comando `cat` que lê ficheiro e imprime no ecrã o seu conteúdo e procedemos com um pipe `|` para enviar o conteúdo como argumento para o binário `nfa` que foi compilado.

Exemplo de entrada:

```
a a b a
0
1 2
0 a 0
0 b 1
0 a 3
1 a 2
2 a 3
3 a 1
3 a 2
```

Esta aplicação executa autómatos não deterministas com transições epsilon e diz-nos se uma dada palavra é ou não aceite pelo autómato, i.e., aceitação de palavra dum nfa.

Com base no código fornecido, construa as seguintes funções:

- a. Uma função para enumerar todas as palavras com comprimento `n` de um autómato em entrada.

- b. Uma função para converter um nfa num dfa.

- c. Uma função que diz se um dado autómato em entrada é determinista.

- d. Uma função para minimizar o autómato em entrada caso seja um dfa.
