%include "../../../include/linked_lists/singly.inc"

.intel_syntax noprefix

.text

.globl singly_list_new

.extern malloc
.extern node_new


singly_list_new:
    push	rbp
    mov	rbp, rsp

    push	rbx
    sub	rsp, 8

    mov	rdi, SinglyLinkedList_size
    call	malloc

    test	rax, rax
    je	.fail

    mov	rbx, rax

    xor	rdi, rdi
    xor	rsi, rsi
    call	node_new

    test	rax, rax
    je	.fail

    mov	[rbx + SinglyLinkedList.sentinel_], rax
    mov	[rbx + SinglyLinkedList.tail_], rax
    mov	qword [rbx + SinglyLinkedList.size_], 0

    mov	rax, rbx

    add	rsp, 8
    pop	rbx
    
    leave
    ret

.fail:
    xor eax, eax
    
    add	rsp, 8
    pop	rbx

    leave
    ret
