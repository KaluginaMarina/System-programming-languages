%define lw 0		

%macro colon 2			; начало макроса - принимает 2 параметра: строку и указатель

%%lw: dq lw 			; временная переменная для хранения указателя на след строку
db %1, 0 			
%2:						; метка из 2 параметра

%define lw %%lw			; константа для адреса следующей строки
%endmacro

colon "hello", hello
db "goodbye", 0 

colon "world", world
db "world", 0