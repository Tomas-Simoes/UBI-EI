(*
  Execução de autómatos não deterministas com transições epsilon

  Para compilar:
    $ ocamlc str.cma nfa.ml -o nfa

  Para executar com o input do ficheiro:
    $ cat input.nfa | ./nfa

  Exemplo de entrada:
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

*)

open List
open Str
open Scanf
open Printf

type simbolo = char option
(**

  O tipo simbolo representa o tipo das letras (o alfabeto). Por isso devemos considerar o
  alfabeto standard (aqui utilizamos o tipo char) mas também considerar a
  palavra/letra vazia: o epsilon.

  Neste caso concreto optamos pelo tipo char option. Assim o valor
  Some x representa o caractere x, e o valor None representa o
  epsilon.

*)

type fita = simbolo list
(** 
  a fita de entrada é simplesmente uma lista de simbolos
*)

type estado = int
(**

  Escolhemos representar os estados por inteiros. Em particular
  tentaremos respeitar o invariante sobre a representação dos
  estados. Invariante: Se houver n estados então estes são 0 1 2 3 .. n-1.

*)

type transicao = (estado * simbolo) * estado
(**

  As transições q1 --a--> q2 são representadas como ((q1,a),q2) ao
  detrimento da representação mais natural (q1,a,q2).

  Esta pequena nuance permite uma pesquisa melhorada de uma transição
  no conjunto das possíveis transições (de tipo hash table, em que a chave é
  (q1,a) e o conteudo é estado destino q2)

*)

type maquina = transicao list * estado list * estado list
(**

  Neste cenário, um autómato (ou máquina) é dado pela relação de
  transição (a listas de adjacência, ou seja a lista das transições),
  o conjuntos dos estados iniciais e o conjunto dos estados
  finais. Sendo que o alfabeto é do tipo char e conjunto dos estados
  deduz-se automaticamente dos dados anteriores.

*)

type memoria = estado list * fita
(**

  As configurações da máquina (não determinista), aqui designada de
  memória, é simplesmente o par dos estados actualmente activos (onde se
  encontra no momento a execução) e o buffer ainda por processar

*)

exception FIM of memoria
(**
  uma excepção para assinalar o fim de uma execução
*)

(**

  Duas funções simples mas naturais que codificam as noções de
  subconjuntos e igualdade de conjunto (sendo estes codificados como
  listas)

*)
let subset c1 c2 = for_all (function x -> mem x c2) c1

let equal c1 c2 = subset c1 c2 && subset c2 c1

(**

  As operações sobre transições, estados ou configurações podem
  levar a que se gere muitos duplicados nas listas que os representam.
  A função normalize de forma natural permite remover estes elementos
  duplicados.

*)
let normalize c =
  fold_left (fun res x -> if mem x res then res else x :: res) [] c

(**
  união de dois conjuntos 
*)
let union c1 c2 = normalize (c1 @ c2)

(**

  Dado uma máquina maq e um estado state, a função
  epsilon_trans_aux calcula que estados se consegue atingir a partir
  de state e de *uma* transição epsilon.

*)
let epsilon_trans_aux state maq =
  let transicoes, b, c = maq in
  map
    (function a, b -> b)
    (filter (function x, y -> x = (state, None)) transicoes)

(**

  Generaliza a função anterior.  A função epsilon_trans calcula
  todos os estados atingíveis, por uma ou mais transições epsilon, a
  partir dos estados em lstate (lista de estado). O calculo é feito
  por "ponto fixo". enquanto aparecer estados novos calcula-se, mal
  deixe de aparecer novidades... para-se.

*)
let rec epsilon_trans lstate maq =
  (** res = todos os estados atingíveis por uma transição epsilon a
      partir dos estados de lstate *)
  let res =
    normalize (flatten (map (fun x -> epsilon_trans_aux x maq) lstate))
  in

  (** junta-se estes estados ao lstate*)
  let resultado = union res lstate in

  (** se esta união não traz nada de novo... ponto fixo. Devolve se
    então resultado *)
  if equal lstate resultado then resultado (** senão, tenta-se mais uma volta*)
  else epsilon_trans resultado maq

(** select devolve todas os estados alvo de transições que partem de
    est com o label simb
*)
let select est simb tabela =
  map
    (function a, b -> b)
    (filter (function (a, b), c -> a = est && b = simb) tabela)

(** 

  next calcula os estados atingíveis a partir dos estados em lesta
  com o simbolo simb, combinado com os estados atingíveis por
  transições epsilon a partir daí.

  Se não houver estados atingidos, damos a indicação de que se
  terminou a execução

*)
let next simb maquina memo =
  let lesta, restante = memo in
  let transicoes, b, c = maquina in
  (** tr = os estados atingíveis pela transição de label simb a
      partir dos estado de lesta*)
  let tr = fold_left (fun x y -> select y simb transicoes @ x) [] lesta in
  (** estende-se  tr com os estados atingídos por transições epsilon *)
  let res = epsilon_trans (normalize tr) maquina in
  if res = [] then raise (FIM memo) else res

(**
   step realiza um passo de execução do autómato maq a partir da
   configuração memo.
*)
let step memo maq =
  let laqui, restante = memo in
  (** se o buffer de entrada for vazio, então acabou, senão tratamos
    do primeiro caracter do buffer. Ou seja, vamos ver que novos
    estados atingimos com ele a partir dos estados actualmente
    activos (onde a execução actualmente se encontra) que estão em
    laqui. Chamanos aqui a função next que trata deste
    cálculo. *)
  match restante with
  | [] -> raise (FIM memo)
  | el :: li -> (next el maq memo, li)

(** is_accepted é um predicado que detecta se uma configuração
    memo da execução do autómato maq prefigura a aceitação. Ou seja o
    buffer de entrada encontra-se vazio e há pelo menos um estado final na
    configuração
*)
let is_accepted memo maq =
  let laqui, restante = memo in
  let trans, init, accept = maq in
  restante = [] && exists (fun x -> mem x accept) laqui

(** to_fita é uma função de tradução de char para simbolo.  O
    caracter '_' é entendido como o epsilon *)
let to_fita c = if c = '_' then None else Some c

(** tradução para o formato transição*)
let em_par a b c = ((a, to_fita b), c)

(** função utilitária simples*)
let char_of_string s = s.[0]

(**
Lê no formato texto o autómato por executar, e a palavra por reconhecer.
A leitura devolve as estruturas correspondentes.
*)
let leitura () =
  let dados =
    map
      (fun x -> to_fita (char_of_string x))
      (Str.split (Str.regexp "[ \t]+") (read_line ()))
  in
  let initl =
    map
      (fun x -> int_of_string x)
      (Str.split (Str.regexp "[ \t]+") (read_line ()))
  in
  let finl =
    map
      (fun x -> int_of_string x)
      (Str.split (Str.regexp "[ \t]+") (read_line ()))
  in
  let input = ref [] in
  try
    while true do
      input := scanf " %d %c %d " em_par :: !input
    done;
    (dados, (!input, initl, finl))
  with _ -> (dados, (!input, initl, finl))

(** a função print_output analisa a configuração final e imprime na
    saída standard o veredicto.
*)
let print_output memo maq =
  if is_accepted memo maq then printf "YES\n" else printf "NO\n"

(**
função principal
*)
let main () =
  let dados, maquina = leitura () in
  let a, b, c = maquina in
  try
    let memor = ref (epsilon_trans b maquina, dados) in
    while true do
      memor := step !memor maquina
    done
  with FIM x -> print_output x maquina
;;

(**  executa. *)
main ()
