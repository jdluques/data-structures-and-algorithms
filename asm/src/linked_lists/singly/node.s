%include "../../../include/linked_lists/singly.inc"

.intel_syntax noprefix

.text

.globl node_new

.extern malloc

node_new:
    push 	rbp
    mov 	rbp, rsp

    push 	rdi

    mov 	rdi, Node_size
    call 	malloc

    test 	rax, rax
    je		.fail

    pop 	rdi

    mov		[rax + Node.value_], rdi
    mov 	[rax + Node.next_], rsi

    leave
    ret

.fail:
    xor 	eax, eax
    leave
    ret
