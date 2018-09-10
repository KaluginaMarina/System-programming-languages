section .text

string_length:
    xor rax, rax									; обнуляем rax
	.loop:
		cmp byte[rdi + rax], 0 						; установит ZF = 0, только если [rdi + rax] = 0
		jz .exit 									; если ZF == 0, заканчиваем цикл 
		inc rax 									; увеличиваем счетчик
		jmp .loop
	.exit:
   ret

   
print_string:
	mov rsi, rdi									; адрес строки
	call string_length								; считаем длинну строки, помещаем ее в rax
	mov rdx, rax									; помещаем в rdx длинну строки
	mov rax, 1 										; номер системного вызова write
	mov rdi, 1										; дескриптор stdout
	syscall
    ret


print_char:
    xor rax, rax
	push rsi										; сохраним rsi
	push rdi										; помещаем в char стек
	mov rsi, rsp 									; адрес строки
	mov rdx, 1										; длинна строки (1)
	mov rax, 1 										; номер системного вызова write
	mov rdi, 1										; дескриптор stdout
	syscall
	pop rsi											; восстановим rsi
	add rsp, 8										; добавим 8 байт в rsp => уменьшим адрес стека => вернем регистр в изначальное состояние
    ret

print_newline:
    xor rax, rax
    ret


print_uint:
													; rsp - голова стека, rdi - переданное число
	push r12
	push r13
	mov r12, rsp									; сохраним вершину стека в r12
	mov r13, 10										; сохраним основание системы счисления для деления
	mov rax, rdi									; сохраним переданное чило в rax
	dec rsp
	mov byte[rsp], 0								; dec+mov - "руками" делаем однобайтовый pop
	.loop:
		dec rsp										; сдвигаем указатель
		xor rdx, rdx								; обнуляем rdx
		div  r13 									; делим на 10, остаток в rdx
		add rdx, 0x30								; переводим в ASCII
		mov  byte[rsp], dl 							; сохраняем в стeк
		test rax, rax								; установит ZF = 0, если rax = 0
		jz .print									; если ZF == 0, заканчиваем деление
		jmp .loop
	.print:
	mov rdi, rsp 									; аргумент для print_string
	call print_string 								; выводим число в stdout
	mov rsp, r12						
    pop r13
    pop r12 										; восстановим регистры
    ret


print_int:
    xor rax, rax
													; rdi - переданное число
	mov rax, rdi									; сохраняем в rax
	test rax, rax									; установим флаги
	jns .not_minus									; если отрицательное, то пицем знак '-'
	mov  rdi, '-'  									; помещаем минус для print_char
	push rax
	call print_char									; выводим минус
	pop rax
	neg rax											; приводим к положительному
	mov rdi, rax
	.not_minus:
	call print_uint									; выводим число 
	ret

string_equals:
    xor rax, rax
    ret


read_char:
	dec rsp
	mov rax, 0 										; код системного вызова
	mov rdi, 0 										; дескриптор stdin
	mov rdx, 1										; длинна слова
	mov rsi, rsp									; указатель на начало (и конец)
	syscall
	mov al, [rsp]									; сохраним в младший байт rax
    inc rsp
    ret 

read_word:
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_uint:
    xor rax, rax
    ret

; rdi points to a string
; returns rax: number, rdx : length
parse_int:
    xor rax, rax
    ret 


string_copy:
														; в rsi- указатель куда, в rdi - указатель откуда, rdx - длинна строки
	xor rcx, rcx										; обнуляем счетчик
	push r13											; сохраним значение регистра
	.loop:
		cmp rcx, rdx									; сравниваем счетчик и количество символов в строке
		je .exit										; если все символы скопированы - выходим
		mov r13, [rdi + rcx]							; сохраним в r13 текущий символ
		mov [rsi + rcx], r13							; скопируем
		inc rcx											; увеличиваем счетчик
		jmp .loop
	.exit:
	mov byte[rsi + rcx + 1], 0
	pop r13												; вернем значение r13	
	ret