package stack

type Stack[T any] struct {
	data []T
}

func NewStack[T any]() *Stack[T] {
	return &Stack[T]{}
}

func (stack Stack[T]) Len() uint {
	return uint(len(stack.data))
}

func (stack Stack[T]) IsEmpty() bool {
	return len(stack.data) == 0
}

func (stack Stack[T]) Peek() *T {
	if len(stack.data) == 0 {
		return nil
	}
	return &stack.data[len(stack.data)-1]
}

func (stack *Stack[T]) Push(element T) {
	stack.data = append(stack.data, element)
}

func (stack *Stack[T]) Pop() T {
	top_element := stack.data[len(stack.data)-1]
	stack.data = stack.data[:len(stack.data)-1]
	return top_element
}
