primes(N, Primes) :-
	numlist(2, N, Numbers),
    sieve(Numbers, Primes).

sieve([], []).
sieve([P|Numbers], [P|Primes]) :-
    exclude(multiple_p(P), Numbers, Filtered),
    sieve(Filtered, Primes).

multiple_p(P, N) :-
    N mod P =:= 0.

cipher_aux(_, _, [], []).
cipher_aux(encode, [Prime|Rest], [Encoded|RestEncoded], [Decoded|RestDecoded]) :-
	Encoded is Decoded + Prime,
	cipher_aux(encode, Rest, RestEncoded, RestDecoded).
cipher_aux(decode, [Prime|Rest], [Encoded|RestEncoded], [Decoded|RestDecoded]) :-
    Decoded is Encoded - Prime,
    cipher_aux(decode, Rest, RestEncoded, RestDecoded).

encoder(Phrase, [Ascii|Encoded]) :-
	atom_codes(Phrase, [Ascii|RestAscii]),
    primes(Ascii, Primes),
    cipher_aux(encode, Primes, Encoded, RestAscii).

decoder([Ascii|RestAscii], Phrase) :-
    primes(Ascii, Primes),
	cipher_aux(decode, Primes, RestAscii, Decoded),
    atom_codes(Phrase, [Ascii|Decoded]).
