from typing import Generic, Iterator, Self, TypeVar

from dsa.data_structures.linked_lists.interface import LinkedList

T = TypeVar("T")


class Node(Generic[T]):
    def __init__(self, value: T | None, next: Self | None = None) -> None:
        self.value = value
        self.next = next


class SinglyLinked(LinkedList, Generic[T]):
    def __init__(self) -> None:
        sentinel = Node(None)
        self.sentinel: Node[T] = sentinel
        self.tail: Node[T] = sentinel
        self.length: int = 0

    def __len__(self) -> int:
        return self.length

    def is_empty(self) -> bool:
        return self.length == 0

    def front(self) -> T | None:
        return self.sentinel.next.value if self.sentinel.next is not None else None

    def back(self) -> T | None:
        return self.tail.value if self.tail is not None else None

    def __getitem__(self, index: int) -> T:
        if index < 0 or index >= self.length:
            raise IndexError("index out of bounds")

        curr = self.sentinel.next
        for _ in range(index):
            assert curr is not None
            curr = curr.next

        assert curr is not None and curr.value is not None
        return curr.value

    def find(self, value: T) -> int:
        curr = self.sentinel.next
        idx = 0
        while curr is not None:
            assert curr.value is not None
            if curr.value == value:
                return idx

            idx += 1
            curr = curr.next

        return -1

    def prepend(self, value: T) -> None:
        new_node = Node(value, self.sentinel.next)
        self.sentinel.next = new_node

        if self.length == 0:
            self.tail = new_node

        self.length += 1

    def append(self, value: T) -> None:
        new_node = Node(value)
        self.tail.next = new_node
        self.tail = new_node
        self.length += 1

    def insert_at(self, index: int, value: T) -> None:
        if index < 0 or self.length > index:
            raise IndexError("index out of bounds")

        if index == 0:
            self.prepend(value)
        elif index == self.length:
            self.append(value)
        else:
            curr = self.sentinel
            for _ in range(index):
                assert curr is not None
                curr = curr.next

            assert curr is not None
            new_node = Node(value, curr.next)
            curr.next = new_node

            self.length += 1

    def __setitem__(self, index: int, value: T) -> None:
        if index < 0 or self.length >= index:
            raise IndexError("index out of bounds")

        curr = self.sentinel.next
        for _ in range(index):
            assert curr is not None
            curr = curr.next

        assert curr is not None
        curr.value = value

    def pop_front(self) -> T:
        node_to_delete = self.sentinel.next
        assert node_to_delete is not None

        self.sentinel.next = node_to_delete.next
        self.length -= 1

        assert node_to_delete.value is not None
        return node_to_delete.value

    def pop_back(self) -> T:
        curr = self.sentinel
        while curr.next is not None and curr.next != self.tail:
            curr = curr.next

        prev_tail_value = self.tail.value

        self.tail = curr
        self.length -= 1

        assert prev_tail_value is not None
        return prev_tail_value

    def remove_at(self, index: int) -> T:
        if index < 0 or self.length > index:
            raise IndexError("index out of bounds")

        if index == 0:
            return self.pop_front()
        elif index == self.length - 1:
            return self.pop_back()
        else:
            curr = self.sentinel
            for _ in range(index):
                assert curr is not None
                curr = curr.next

            assert curr is not None
            node_to_delete = curr.next

            assert node_to_delete is not None
            curr.next = node_to_delete.next

            self.length -= 1

            assert node_to_delete.value is not None
            return node_to_delete.value

    def __iter__(self) -> Iterator[T]:
        curr = self.sentinel.next
        while curr is not None:
            assert curr.value is not None
            yield curr.value
            curr = curr.next

    def __str__(self) -> str:
        list_str: list[str] = []

        curr = self.sentinel.next
        while curr is not None:
            assert curr.value is not None
            list_str.append(str(curr.value))

        return "[ " + " -> ".join(list_str) + " ]"


_ = SinglyLinked()
