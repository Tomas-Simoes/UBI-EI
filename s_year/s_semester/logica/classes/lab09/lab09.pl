% output(command, command_output)
output(on, "ligado, a espera de comandos").
output(off, "aparelhagem desligada").

output(sint, "foi escolhido o modo sintonizador").
output(lcd, "foi escolhido o modo de cd").
output(lcasset, "foi escolhido o modo de leitor de cassete").

output(am, "foi escolhido o modo am").
output(fm, "foi escolhido o modo fm").
output(freq, "esta a ouvir uma frequência escolhida").

output(ff, "leitor de cassete a andar para a frente").
output(rw, "leitor de cassete a andar para traz").
output(play, "de play no leitor de cassete").
output(stop, "cassete foi parada").

output(erro, "sequência de comandos errada").

% estadoInicial(state, msg_state)
estadoInicial(on, "ligado, a espera de comandos").

% delta(prev_state, action, new_state)
delta(on, sint, sint).
delta(on, lcd, lcd).
delta(on, lcasset, lcasset).
delta(_, off, off).

delta(sint, am, am).
delta(sint, fm, fm).
delta(am, freq, freq).
delta(fm, freq, freq).

delta(lcd, pista, pista).

delta(lcasset, ff, ff).
delta(lcasset, rw, rw).
delta(lcasset, play, play).

delta(ff, stop, stop).
delta(rw, stop, stop).
delta(play, stop, stop).

delta(_, _, erro).

simulaControlador([], _).
simulaControlador([H|T], Output) :-
    estadoInicial(H, _),
    controladorAux(T, on, Output).
simulaControlador(_, "é preciso ligar a aparelhagem").

% controladorAux(command_list, state, output)
controladorAux([], State, Output) :-
    output(State, Output).
controladorAux(_, erro, Output) :-
    output(erro, Output).
controladorAux([H|T], State, Output) :-
	delta(State, H, NewState),
    controladorAux(T, NewState, Output).

    


    
