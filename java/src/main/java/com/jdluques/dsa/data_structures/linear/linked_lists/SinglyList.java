package com.jdluques.dsa.data_structures.linear.linked_lists;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.function.Predicate;

public class SinglyList<T> implements List<T> {
    private static class Node<T> {
        T value;
        Node<T> next;

        public Node(T value) {
            this.value = value;
            this.next = null;
        }

        public Node(T value, Node<T> next) {
            this.value = value;
            this.next = next;
        }
    }

    private Node<T> sentinel;
    private Node<T> tail;
    private int size;

    public SinglyList() {
        this.sentinel = new Node<>(null);
        this.tail = this.sentinel;
        this.size = 0;
    }

    @Override
    public void addFirst(T value) {
        Node<T> newNode = new Node<>(value);
        newNode.next = this.sentinel.next;
        this.sentinel.next = newNode;
        if (this.size == 0) {
            this.tail = newNode;
        }
        this.size++;
    }

    @Override
    public void addLast(T value) {
        Node<T> newNode = new Node<>(value);
        this.tail.next = newNode;
        this.tail = newNode;
        this.size++;
    }

    @Override
    public void addAt(int index, T value) {
        if (index < 0 || index > this.size) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + this.size);
        }

        if (index == 0) addFirst(value);
        if (index == this.size) addLast(value);
        else {
            Node<T> curr = this.sentinel;
            for (int i = 0; i < index; i++) {
                curr = curr.next;
            }
            Node<T> newNode = new Node<>(value, curr.next);
            curr.next = newNode;
            this.size++;
        }
    }

    @Override
    public T removeFirst() {
        if (this.size == 0) {
            throw new IllegalStateException("List is empty");
        }

        Node<T> first = this.sentinel.next;
        this.sentinel.next = first.next;
        if (this.size == 1) {
            this.tail = this.sentinel;
        }

        this.size--;
        
        return first.value;
    }

    @Override
    public T removeLast() {
        if (this.size == 0) {
            throw new IllegalStateException("List is empty");
        }

        Node<T> curr = this.sentinel;
        while (curr.next != this.tail) {
            curr = curr.next;
        }
        T value = this.tail.value;
        curr.next = null;
        this.tail = curr;

        this.size--;
        
        return value;
    }

    @Override
    public T removeAt(int index) {
        if (index < 0 || index >= this.size) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + this.size);
        }

        if (index == 0) return removeFirst();
        if (index == this.size - 1) return removeLast();
        else {
            Node<T> curr = this.sentinel;
            for (int i = 0; i < index; i++) {
                curr = curr.next;
            }
            T value = curr.next.value;
            curr.next = curr.next.next;
            
            this.size--;
            
            return value;
        }
    }

    @Override
    public void removeIf(Predicate<T> cond) {
        Node<T> curr = this.sentinel;

        while (curr.next != null) {
            if (cond.test(curr.next.value)) {
                curr.next = curr.next.next;
                this.size--;
            } else {
                curr = curr.next;
            }
        }
    }

    @Override
    public T getFirst() {
        if (this.size == 0) {
            throw new IllegalStateException("List is empty");
        }
        return this.sentinel.next.value;
    }

    @Override
    public T getLast() {
        if (this.size == 0) {
            throw new IllegalStateException("List is empty");
        }
        return this.tail.value;
    }

    @Override
    public T get(int index) {
        if (index < 0 || index >= this.size) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + this.size);
        }

        Node<T> curr = this.sentinel.next;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }
        return curr.value;
    }

    @Override
    public int size() {
        return this.size;
    }

    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }

    @Override
    public Iterator<T> iterator() {
        return new SinglyLinkedListIterator();
    }
    
    private class SinglyLinkedListIterator implements Iterator<T> {
        private Node<T> curr = sentinel;

        @Override
        public boolean hasNext() {
            return curr.next != null;
        }

        @Override
        public T next() {
            if (!hasNext()) {
                throw new NoSuchElementException();
            }

            T data = curr.next.value;
            curr = curr.next;
            return data;
        }
    }
}