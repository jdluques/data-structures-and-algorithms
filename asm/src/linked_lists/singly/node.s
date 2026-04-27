.intel_syntax noprefix
.text
.globl node_new
.extern malloc

struc Node
    .value_: resq 1
    .next_:  resq 1
endstruc

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
