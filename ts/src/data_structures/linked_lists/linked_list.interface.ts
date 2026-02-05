import type { ListNode } from "./node.js";

export interface LinkedList<T> {
    size(): number;
    isEmpty(): boolean;

    getAt(index: number): T;
    find(value: T): | ListNode<T> | null;

    append(value: T): void;
    prepend(value: T): void;
    insertAt(value: T, index: number): void;

    deleteHead(): T | null;
    deleteTail(): T | null;
    deleteAt(index: number): T | null;
    delete(value: T): T | null;

    clear(): void;

    merge(other: LinkedList<T>): void;
    reverse(): void;

    toArray(): T[];

    [Symbol.iterator](): Iterator<T>;
}