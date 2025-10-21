(* FUNÇÃO: destinos_por_estado *)
let rec destinos_por_estado estado transicoes alfabeto =
  match alfabeto with
  | [] -> []
  | ref_simbolo :: tail_alfabeto ->
      let destinos = List.fold_left
        (fun acc transicao ->
          let ((origem, simbolo), destino) = transicao in
          if origem = estado && simbolo = ref_simbolo then
            destino :: acc
          else
            acc
        ) [] transicoes
      in
      ((estado, ref_simbolo), destinos) :: destinos_por_estado estado transicoes tail_alfabeto

(* FUNÇÃO: mapear_estados *)
let rec mapear_estados ref_parte estados map =
  match map with
  | [] ->
      let novo_estado = (List.hd (List.rev estados)) + 1 in
      let map_atualizado = (ref_parte, novo_estado) :: map in
      (map_atualizado, novo_estado)
  | (parte, _) :: tail_map ->
      if ref_parte = parte then
        (map, List.assoc ref_parte map)
      else
        mapear_estados ref_parte estados tail_map

(* FUNÇÃO: reverter *)
let reverter nfa =
  let (estados, alfabeto, transicoes, iniciais, finais) = nfa in
  let transicoes_inv =
    List.map (fun transicao ->
      let ((origem, simbolo), destino) = transicao in
      ((destino, simbolo), origem)
    ) transicoes in
  (estados, alfabeto, transicoes_inv, finais, iniciais)

(* FUNÇÃO: converter_aux *)
let rec converter_aux nfa map =
  let (estados, alfabeto, transicoes, iniciais, finais) = nfa in
  match estados with
  | [] -> (transicoes, map)
  | head_estados :: tail_estados ->
      let new_transicoes = destinos_por_estado head_estados transicoes alfabeto in
      let (map_atualizado, novos_estados) =
        List.fold_left (
          fun (map_acc, novos_acc) transicao ->
            let ((estado, simbolo), destinos) = transicao in
            let destinos_ordenados = List.sort_uniq compare destinos in
            let (map_updated, novo_est) = mapear_estados destinos_ordenados estados map_acc in
            (map_updated, novos_acc @ [novo_est])
        ) (map, []) new_transicoes
      in
      
      let new_transicoes_mapeadas = List.map (fun transicao ->
        let ((estado, simbolo), destinos) = transicao in
        let destinos_ordenados = List.sort_uniq compare destinos in
        let destino_mapeado = List.assoc destinos_ordenados map_atualizado in
        ((estado, simbolo), destino_mapeado)
      ) new_transicoes in
      
      let nfa_atualizado = (tail_estados @ novos_estados, alfabeto, transicoes @ new_transicoes_mapeadas, iniciais, finais) in
      
      converter_aux nfa_atualizado map_atualizado

(* FUNÇÃO: converter *)
let converter nfa =
  let (estados, alfabeto, transicoes, iniciais, finais) = nfa in
  let inicial_conjunto = List.sort_uniq compare iniciais in
  let (transicoes_finais, map_final) = converter_aux nfa [(inicial_conjunto, List.hd estados)] in
  
  let novos_finais = List.filter (fun estado ->
    let conjunto = List.find_opt (fun (conj, num) -> num = estado) map_final in
    match conjunto with
    | Some (conj, _) -> List.exists (fun f -> List.mem f finais) conj
    | None -> false
  ) (snd (List.split map_final)) in
  
  let novos_estados = List.sort_uniq compare (snd (List.split map_final)) in
  (novos_estados, alfabeto, transicoes_finais, [List.hd estados], novos_finais)