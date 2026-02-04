pub(crate) struct SinglyNode<T> {
    pub(crate) value: T,
    pub(crate) next: Option<Box<SinglyNode<T>>>,
}

impl<T> SinglyNode<T> {
    pub(crate) fn new(value: T, next: Option<Box<SinglyNode<T>>>) -> Self {
        SinglyNode {
            value: value,
            next: next,
        }
    }
}
