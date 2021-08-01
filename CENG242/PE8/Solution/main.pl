:- module(main, [sum_age/2, max_age_of_hobby/3, person_in_range/4]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

sum_age([],0).
sum_age([X|Y],Age):-sum_age(Y,OldAge),person(X,PersonAge,_),Age is OldAge+PersonAge.


max_age_of_hobby([],H,0):-!.
max_age_of_hobby([X|Y],H,AgeRest):-
    person(X,_,H2),
    max_age_of_hobby(Y,H,AgeRest),
    H2\=H.
max_age_of_hobby([X|Y],H,AgeRest):-
    person(X,Age,H),
    max_age_of_hobby(Y,H,AgeRest),
    AgeRest>=Age.
max_age_of_hobby([X|Y],H,Age):-
    person(X,Age,H),
    max_age_of_hobby(Y,H,AgeRest),
    AgeRest<Age.
    
person_in_range([],_,_,[]).
person_in_range([X|Y],Min,Max,Result):-
    person(X,Age,_),
    person_in_range(Y,Min,Max,RightResult),
    append([X],RightResult,Result),
    Age=<Max,Min=<Age.
person_in_range([X|Y],Min,Max,RightResult):-
    person(X,Age,_),
    person_in_range(Y,Min,Max,RightResult),
    Age>Max.
person_in_range([X|Y],Min,Max,RightResult):-
    person(X,Age,_),
    person_in_range(Y,Min,Max,RightResult),
    Age<Min.
