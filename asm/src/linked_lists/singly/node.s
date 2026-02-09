.intel_syntax noprefix
.text

; System V AMD64 ABI
; rdi, rsi, rdx, rcx, r8, r9
; return in rax

; struct Node
; 0  : void* value_
; 8  : Node* next_

; struct SinglyLinkedList
; 0  : Node* sentinel_
; 8  : Node* tail_
; 16 : size_t size_

node_new:
    push rbp
    mov rbp, rsp

    ; rdi = value_
    ; rsi = next_

    ; malloc(sizeof(Node)) = 16
    mov rdi, 16
    call malloc

    test rax, rax
    je .fail

    mov [rax], rdi	; value_
    mov [rax + 1], rsi	; next_

    leave
    ret

.fail
    xor rax, rax
    leave ret
