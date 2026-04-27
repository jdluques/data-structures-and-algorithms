.intel_syntax noprefix
.text
.globl singly_list_new
.extern malloc
.extern node_new

struc SinglyLinkedList
   .sentinel_:  resq 1
   .tail_:		resq 1
   .size_:		resq 1
endstruc

singly_list_new:
    push 	rbp
    mov 	rbp, rsp

    mov 	rdi, SinglyLinkedList_size
    call	malloc

    test 	rax, rax
    je		.fail

	mov		rbx, rax

	xor 	rdi, rdi
	xor		rsi, rsi
	call 	node_new

	test	rax, rax
	je		.fail

	mov		[rbx + SinglyLinkedList.sentinel_], rax
	mov		[rbx + SinglyLinkedList.tail_], rax
	mov		qword [rbx + SinglyLinkedList.size_], 0

	mov		rax, rbx

	leave
	ret

.fail:
    xor eax, eax
    leave
    ret
