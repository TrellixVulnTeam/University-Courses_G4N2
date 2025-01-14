%used 3 instead of X
gen(5, []):-!.

gen(N, [1|T]):-
    N1 is N+1,
    gen(N1, T).

gen(N, [2|T]):-
    N =\= 4,
    N1 is N+1,
    gen(N1, T).

gen(N, [3|T]):-
    N1 is N+1,
    gen(N1, T).


countX([], 0).
countX([3|T], C):-
    !,
    countX(T, C1),
    C is C1 +1.


countX([_|T], C):-
    !,
    countX(T, C).

solve( LR):-
    gen(1, LR),
    countX(LR, X),
    X =:= 1.


main(LR):-
    findall(X, solve(X), LR).

