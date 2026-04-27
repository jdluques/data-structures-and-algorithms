%include "../../../include/linked_lists/singly.inc"

.intel_syntax noprefix

.text

.globl size
.globl empty

size:
	mov 	rax, qword [rdi + SinglyLinkedList.size_]

	ret

empty:
	mov		rax, [rdi + SinglyLinkedList.size_]

	test	rax, rax
	setz	al
	movzx	rax, al

	ret
