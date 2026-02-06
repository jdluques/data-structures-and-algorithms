from abc import ABC, abstractmethod
from typing import Generic, Iterator, TypeVar

T = TypeVar("T")


class LinkedList(ABC, Generic[T]):
    @abstractmethod
    def __init__(self) -> None:
        pass

    @abstractmethod
    def __len__(self) -> int:
        pass

    @abstractmethod
    def is_empty(self) -> bool:
        pass

    @abstractmethod
    def front(self) -> T | None:
        pass

    @abstractmethod
    def back(self) -> T | None:
        pass

    @abstractmethod
    def __getitem__(self, index: int) -> T:
        pass

    @abstractmethod
    def find(self, value: T) -> int:
        pass

    @abstractmethod
    def prepend(self, value: T) -> None:
        pass

    @abstractmethod
    def append(self, value: T) -> None:
        pass

    @abstractmethod
    def insert_at(self, index: int, value: T) -> None:
        pass

    @abstractmethod
    def __setitem__(self, index: int, value: T) -> None:
        pass

    @abstractmethod
    def pop_front(self) -> T:
        pass

    @abstractmethod
    def pop_back(self) -> T:
        pass

    @abstractmethod
    def remove_at(self, index: int) -> T:
        pass

    @abstractmethod
    def __iter__(self) -> Iterator[T]:
        pass

    @abstractmethod
    def __str__(self) -> str:
        pass
