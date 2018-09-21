section .data
	msg: db "No world", 0

global _start	
	
section .text
%include "colon.inc"

extern read_word
extern find_word
extern string_length
extern print_string

_start: 
	
	mov rsi, 255			; максимум, что мы можем записать в буфер
	sub rsp, 256			; место под буфер
	
	mov rdi, rsp			; скажем ему куда записываем слово
	call read_word			; оно нам вернет где начало слово (в rax)
	mov rdi, rax
	mov rsi, lw
	call find_word			; возвращает указатель на строку
	cmp rax, 0
	je .false
	add rax, 8				; указатель на начало строки, а не на адрес следующего слова	
	mov r10, rax
	
							; дальше нам надо найти строку по метке 
							;(для этого надо найти сначала метку, которая лежит после строки)
		 						
	call string_length
	add r10, rax			; сдвинем указатель на начало метки
	mov rdi, r10		
	call print_string
	
.exit:	
	mov rax, 60 
	mov rdi, rax 			; чтобы echo выводило то, что у нас возвращает find_word
	syscall
	ret
	
.false:
	mov rdi, msg			; если нет слова - то так и напишем :)
	call string_length
	mov rsi, rax
	call print_string
	jmp .exit
	