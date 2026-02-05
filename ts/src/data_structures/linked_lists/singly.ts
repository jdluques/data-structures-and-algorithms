import type { LinkedList } from "./linked_list.interface.js";
import { ListNode as Node } from "./node.js";

export class SinglyLinkedList<T> implements LinkedList<T>, Iterable<T> {
    private sentinel: Node<T | null>
    private tail: Node<T>
    private length: number

    constructor() {
        this.sentinel = new Node<T | null>(null);
        this.tail = this.sentinel as Node<T>;
        this.length = 0;
    }

    size(): number {
        return this.length;
    }

    isEmpty(): boolean {
        return this.length === 0;
    }

    getAt(index: number): T {
        if (index < 0 || index >= this.length) {
            throw new RangeError("Index out of bounds");
        }

        let curr = this.sentinel.next as Node<T>;
        for (let i = 0; i < index; i++) {
            curr = curr.next as Node<T>;
        }

        return curr.value;
    }

    find(value: T): Node<T> | null {
        let curr = this.sentinel.next as Node<T>;
        while (curr) {
            if (curr.value === value) {
                return curr;
            }
            curr = curr.next as Node<T>;
        }
        return null;
    }

    append(value: T): void {
        const newNode = new Node<T>(value);
        this.tail.next = newNode;
        this.tail = newNode;
        this.length++;
    }

    prepend(value: T): void {
        const newNode = new Node<T>(value, this.sentinel.next as Node<T> | null);
        this.sentinel.next = newNode;
        if (this.length === 0) {
            this.tail = newNode;
        }
        this.length++;
    }

    insertAt(value: T, index: number): void {
        if (index < 0 || index > this.length) {
            throw new RangeError("Index out of bounds");
        }

        if (index === 0) {
            this.prepend(value);
            return;
        } else if (index === this.length - 1) {
            this.append(value);
        } else {
            let curr = this.sentinel as Node<T>;
            for (let i = 0; i <= index; i++) {
                curr = curr.next as Node<T>;
            }

            const newNode = new Node<T>(value, curr.next);
            curr.next = newNode;
            this.length++;
        }
    }

    deleteHead(): T | null {
        if (this.length === 0) {
            return null;
        }

        const head = this.sentinel.next as Node<T>;
        this.sentinel.next = head.next;

        this.length--;
        if (this.length === 0) {
            this.tail = this.sentinel as Node<T>;
        }

        return head.value;
    }

    deleteTail(): T | null {
        if (this.length === 0) {
            return null;
        }

        let curr = this.sentinel as Node<T>;
        while (curr.next !== this.tail) {
            curr = curr.next as Node<T>;
        }

        const tailValue = this.tail.value;
        curr.next = null;
        this.tail = curr;
        this.length--;

        return tailValue;
    }

    deleteAt(index: number): T | null {
        if (index < 0 || index >= this.length) {
            throw new RangeError("Index out of bounds");
        }

        if (index === 0) {
            return this.deleteHead();
        } else if (index === this.length - 1) {
            return this.deleteTail();
        } else {
            let curr = this.sentinel as Node<T>;
            for (let i = 0; i < index; i++) {
                curr = curr.next as Node<T>;
            }

            const nodeToDelete = curr.next as Node<T>;
            curr.next = nodeToDelete.next;
            this.length--;

            return nodeToDelete.value;
        }
    }

    delete(value: T): T | null {
        let curr = this.sentinel as Node<T>;

        for (let i = 0; curr.next; i++) {
            if (curr.next.value === value) {
                if (i == 0) {
                    return this.deleteHead();
                } else if (i == this.length - 1) {
                    return this.deleteTail();
                } else {
                    const nodeToDelete = curr.next as Node<T>;
                    curr.next = nodeToDelete.next;
                    this.length--;

                    return nodeToDelete.value;
                }
            }
        }

        return null;
    }

    clear(): void {
        while (this.length > 0) {
            this.deleteHead();
        }
    }

    merge(other: LinkedList<T>): void {
        for (const value of other) {
            this.append(value);
        }
    }

    reverse(): void {
        let prev: Node<T> | null = null;
        let curr = this.sentinel.next as Node<T> | null;
        this.tail = curr as Node<T>;

        while (curr) {
            const next = curr.next as Node<T> | null;
            curr.next = prev;
            prev = curr;
            curr = next;
        }

        this.sentinel.next = prev;
    }

    toArray(): T[] {
        let arr: T[] = [];

        let curr = this.sentinel.next as Node<T>;
        while (curr) {
            arr.push(curr.value);
            curr = curr.next as Node<T>;
        }

        return arr;
    }

    *[Symbol.iterator](): Iterator<T> {
        let curr = this.sentinel.next as Node<T>;
        while (curr) {
            yield curr.value;
            curr = curr.next as Node<T>;
        }
    }
}