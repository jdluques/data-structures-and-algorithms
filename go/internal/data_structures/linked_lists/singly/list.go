package singlylists

import "errors"

var (
	EmtpyList       error = errors.New("list is empty")
	IndexOutOfRange error = errors.New("list index out of range")
)

type SinglyLinkedList[T any] struct {
	sentinel *node[T]
	tail     *node[T]
	length   uint
}

func NewSinglyLinkedList[T any]() SinglyLinkedList[T] {
	var zero T
	sentinel := newNode(zero, nil)

	return SinglyLinkedList[T]{
		sentinel: sentinel,
		tail:     sentinel,
		length:   0,
	}
}

func (list SinglyLinkedList[T]) Len() uint {
	return list.length
}

func (list SinglyLinkedList[T]) IsEmpty() bool {
	return list.length == 0
}

func (list SinglyLinkedList[T]) Front() (*T, error) {
	if list.length == 0 {
		return nil, EmtpyList
	}

	return &list.tail.value, nil
}

func (list SinglyLinkedList[T]) Back() (*T, error) {
	if list.length == 0 {
		return nil, EmtpyList
	}

	return &list.sentinel.next.value, nil
}

func (list SinglyLinkedList[T]) GetAT(index uint) (*T, error) {
	if index >= list.length {
		return nil, IndexOutOfRange
	}

	curr := list.sentinel.next
	for ; index > 0; index-- {
		curr = curr.next
	}

	return &curr.value, nil
}

func (list SinglyLinkedList[T]) Find(pred func(T) bool) *T {
	curr := list.sentinel.next
	for ; curr != nil; curr = curr.next {
		if pred(curr.value) {
			return &curr.value
		}
	}
	return nil
}

func (list *SinglyLinkedList[T]) PushFront(value T) {
	list.sentinel.next = newNode(value, list.sentinel.next)
	if list.length == 0 {
		list.tail = list.sentinel.next
	}
	list.length++
}

func (list *SinglyLinkedList[T]) PushBack(value T) {
	list.tail.next = newNode(value, nil)
	list.tail = list.tail.next
	list.length++
}

func (list *SinglyLinkedList[T]) InsertAt(index uint, value T) error {
	if index > list.length {
		return IndexOutOfRange
	}

	switch index {
	case 0:
		list.PushFront(value)
	case list.length:
		list.PushBack(value)
	default:
		curr := list.sentinel
		for ; index > 0; index-- {
			curr = curr.next
		}

		curr.next = newNode(value, curr.next)
		list.length++
	}

	return nil
}

func (list *SinglyLinkedList[T]) InsertAfter(pred func(T) bool, value T) {
	curr := list.sentinel.next
	for ; curr != nil; curr = curr.next {
		if pred(curr.value) {
			curr.next = newNode(value, curr.next)
			list.length++
			break
		}
	}
}

func (list *SinglyLinkedList[T]) InsertBefore(pred func(T) bool, value T) {
	curr := list.sentinel
	for ; curr.next != nil; curr = curr.next {
		if pred(curr.next.value) {
			curr.next = newNode(value, curr.next)
			list.length++
			break
		}
	}
}

func (list *SinglyLinkedList[T]) PopFront() (T, error) {
	if list.length == 0 {
		var zero T
		return zero, EmtpyList
	}

	nodeToDelete := list.sentinel.next
	list.sentinel.next = nodeToDelete.next
	list.length--

	if list.length == 0 {
		list.tail = nil
	}

	return nodeToDelete.value, nil
}

func (list *SinglyLinkedList[T]) PopBack() (T, error) {
	if list.length == 0 {
		var zero T
		return zero, EmtpyList
	}

	tailValue := list.tail.value

	curr := list.sentinel
	for curr.next != list.tail {
		curr = curr.next
	}

	curr.next = nil
	list.tail = curr
	list.length--

	return tailValue, nil
}

func (list *SinglyLinkedList[T]) RemoveAt(index uint) (T, error) {
	if index >= list.length {
		var zero T
		return zero, IndexOutOfRange
	}

	switch index {
	case 0:
		return list.PopFront()
	case list.length - 1:
		return list.PopBack()
	default:
		curr := list.sentinel
		for ; index > 0; index-- {
			curr = curr.next
		}

		nodeToDelete := curr.next
		curr.next = nodeToDelete.next
		list.length--

		return nodeToDelete.value, nil
	}
}

func (list *SinglyLinkedList[T]) RemoveIf(pred func(T) bool) (T, bool) {
	curr := list.sentinel
	for ; curr.next != nil; curr = curr.next {
		if pred(curr.next.value) {
			nodeToDelete := curr.next
			curr.next = nodeToDelete.next
			list.length--

			return nodeToDelete.value, true
		}
	}

	var zero T
	return zero, false
}

func (list *SinglyLinkedList[T]) Reverse() error {
	if list.length == 0 {
		return EmtpyList
	}

	curr := list.sentinel.next
	var prev *node[T]
	list.tail = curr

	for curr != nil {
		next := curr.next
		curr.next = prev

		prev = curr
		curr = next
	}

	list.sentinel.next = prev

	return nil
}

func (list SinglyLinkedList[T]) Iterator() func(func(T) bool) {
	return func(yield func(T) bool) {
		curr := list.sentinel.next
		for ; curr != nil; curr = curr.next {
			if !yield(curr.value) {
				return
			}
		}
	}
}
