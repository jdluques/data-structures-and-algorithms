%ifndef SINGLY_INC
%define SINGLY_IN

struc Node
    .value_: resq 1
    .next_:  resq 1
endstruc

struc SinglyLinkedList
   .sentinel_:  resq 1
   .tail_:		resq 1
   .size_:		resq 1
endstruc

%endif
