%include "../../../include/linked_lists/singly.inc"

.intel_syntax noprefix

.text

.globl node_new

.extern malloc

node_new:
    push 	rbp
    mov 	rbp, rsp

    push 	rdi
    push	rsi

    mov 	rdi, Node_size
    call 	malloc

    pop		rsi
    pop 	rdi

    test 	rax, rax
    je		.fail
 
    mov		[rax + Node.value_], rdi
    mov 	[rax + Node.next_], rsi

    leave
    ret

.fail:
    xor 	eax, eax
    leave
    ret
