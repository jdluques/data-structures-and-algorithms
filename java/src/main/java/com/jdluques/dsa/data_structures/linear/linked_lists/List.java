package com.jdluques.dsa.data_structures.linear.linked_lists;

import java.util.function.Predicate;

public interface List<T> extends Iterable<T> {
    void addFirst(T value);
    void addLast(T value);
    void addAt(int index, T value);

    T removeFirst();
    T removeLast();
    T removeAt(int index);
    void removeIf(Predicate<T> cond);

    T getFirst();
    T getLast();
    T get(int index);

    int size();
    boolean isEmpty();
}
