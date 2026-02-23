package com.jdluques.dsa.data_structures.linear.linked_lists;

import java.util.Iterator;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class SinglyListTests {
    private List<Integer> list;

    @BeforeEach
    void setUp() {
        this.list = new SinglyList<>();
    }

    // -----------------------
    // addFirst
    // -----------------------

    @Test
    void addFirstShouldInsertAtBeginning() {
        list.addFirst(10);
        list.addFirst(20);

        assertEquals(2, list.size());
        assertEquals(20, list.getFirst());
        assertEquals(10, list.getLast());
    }

    // -----------------------
    // addLast
    // -----------------------

    @Test
    void addLastShouldInsertAtEnd() {
        list.addLast(10);
        list.addLast(20);

        assertEquals(2, list.size());
        assertEquals(10, list.getFirst());
        assertEquals(20, list.getLast());
    }

    // -----------------------
    // addAt
    // -----------------------

    @Test
    void addAtShouldInsertInMiddle() {
        list.addLast(1);
        list.addLast(3);

        list.addAt(1, 2);

        assertEquals(3, list.size());
        assertEquals(2, list.get(1));
    }

    @Test
    void addAtInvalidIndexShouldThrow() {
        assertThrows(IndexOutOfBoundsException.class,
                () -> list.addAt(1, 10));
    }

    // -----------------------
    // removeFirst
    // -----------------------

    @Test
    void removeFirstShouldRemoveHead() {
        list.addLast(1);
        list.addLast(2);

        int removed = list.removeFirst();

        assertEquals(1, removed);
        assertEquals(1, list.size());
        assertEquals(2, list.getFirst());
    }

    @Test
    void removeFirstOnEmptyShouldThrow() {
        assertThrows(Exception.class, () -> list.removeFirst());
    }

    // -----------------------
    // removeLast
    // -----------------------

    @Test
    void removeLastShouldRemoveTail() {
        list.addLast(1);
        list.addLast(2);

        int removed = list.removeLast();

        assertEquals(2, removed);
        assertEquals(1, list.size());
        assertEquals(1, list.getLast());
    }

    // -----------------------
    // removeAt
    // -----------------------

    @Test
    void removeAtShouldRemoveMiddle() {
        list.addLast(1);
        list.addLast(2);
        list.addLast(3);

        int removed = list.removeAt(1);

        assertEquals(2, removed);
        assertEquals(2, list.size());
        assertEquals(3, list.get(1));
    }

    @Test
    void removeAtInvalidIndexShouldThrow() {
        assertThrows(IndexOutOfBoundsException.class,
                () -> list.removeAt(0));
    }

    // -----------------------
    // removeIf
    // -----------------------

    @Test
    void removeIfShouldRemoveMatchingElements() {
        list.addLast(1);
        list.addLast(2);
        list.addLast(3);
        list.addLast(4);

        list.removeIf(x -> x % 2 == 0);

        assertEquals(2, list.size());
        assertEquals(1, list.get(0));
        assertEquals(3, list.get(1));
    }

    // -----------------------
    // getFirst / getLast
    // -----------------------

    @Test
    void getFirstAndLastShouldReturnCorrectValues() {
        list.addLast(10);
        list.addLast(20);

        assertEquals(10, list.getFirst());
        assertEquals(20, list.getLast());
    }

    @Test
    void getFirstOnEmptyShouldThrow() {
        assertThrows(Exception.class, () -> list.getFirst());
    }

    // -----------------------
    // get
    // -----------------------

    @Test
    void getShouldReturnCorrectElement() {
        list.addLast(5);
        list.addLast(10);
        list.addLast(20);

        assertEquals(10, list.get(1));
    }

    @Test
    void getInvalidIndexShouldThrow() {
        assertThrows(IndexOutOfBoundsException.class,
                () -> list.get(0));
    }

    // -----------------------
    // size & isEmpty
    // -----------------------

    @Test
    void sizeAndIsEmptyShouldWork() {
        assertTrue(list.isEmpty());

        list.addLast(1);

        assertFalse(list.isEmpty());
        assertEquals(1, list.size());
    }

    // -----------------------
    // Iterator
    // -----------------------

    @Test
    void iteratorShouldTraverseAllElements() {
        list.addLast(1);
        list.addLast(2);
        list.addLast(3);

        Iterator<Integer> it = list.iterator();

        assertTrue(it.hasNext());
        assertEquals(1, it.next());
        assertEquals(2, it.next());
        assertEquals(3, it.next());
        assertFalse(it.hasNext());
    }

    @Test
    void forEachLoopShouldWork() {
        list.addLast(1);
        list.addLast(2);
        list.addLast(3);

        int sum = 0;
        for (int value : list) {
            sum += value;
        }

        assertEquals(6, sum);
    }
}
