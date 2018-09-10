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
    xor rax, rax
    ret


print_int:
    xor rax, rax
    ret

string_equals:
    xor rax, rax
    ret


read_char:
    xor rax, rax
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