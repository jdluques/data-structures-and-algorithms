use core::ptr::NonNull;

use super::node::SinglyNode as Node;

pub struct SinglyList<T> {
    head: Box<Node<T>>,
    tail: NonNull<Node<T>>,
    size: usize,
}

impl<T: Default> SinglyList<T> {
    pub fn new() -> Self {
        let mut sentinel = Box::new(Node::new(T::default(), None));
        let sentinel_ptr = NonNull::from(sentinel.as_mut());

        SinglyList {
            head: sentinel,
            tail: sentinel_ptr,
            size: 0,
        }
    }

    pub fn len(&self) -> usize {
        self.size
    }

    pub fn is_empty(&self) -> bool {
        self.size == 0
    }

    pub fn push_back(&mut self, value: T) {
        let mut new_node = Box::new(Node::new(value, None));
        let new_tail = NonNull::from(new_node.as_mut());

        unsafe {
            self.tail.as_mut().next = Some(new_node);
        }

        self.tail = new_tail;
        self.size += 1;
    }

    pub fn push_front(&mut self, value: T) {
        let mut new_node = Box::new(Node::new(value, self.head.next.take()));
        let new_node_ptr = NonNull::from(new_node.as_mut());

        self.head.next = Some(new_node);
        if self.size == 0 {
            self.tail = new_node_ptr;
        }

        self.size += 1;
    }

    pub fn insert_at(&mut self, pos: usize, value: T) {
        if pos > self.size {
            panic!("index out of bounds");
        }

        if pos == 0 {
            self.push_front(value);
        } else if pos == self.size {
            self.push_back(value);
        } else {
            let mut curr = self.head.as_mut();
            for _ in 0..pos {
                curr = curr.next.as_mut().unwrap().as_mut();
            }

            let new_node = Box::new(Node::new(value, curr.next.take()));
            curr.next = Some(new_node);

            self.size += 1;
        }
    }

    pub fn pop_back(&mut self) -> Option<T> {
        match self.size {
            0 | 1 => self.pop_front(),
            _ => {
                let mut curr = self.head.as_mut();
                for _ in 0..self.size - 1 {
                    curr = curr.next.as_mut().unwrap().as_mut();
                }

                let deleted_node = curr.next.take().unwrap();

                self.tail = NonNull::from(curr);

                self.size -= 1;

                Some(deleted_node.value)
            }
        }
    }

    pub fn pop_front(&mut self) -> Option<T> {
        if self.size == 0 {
            return None;
        }

        let mut first_node = self.head.next.take().unwrap();
        self.head.next = first_node.next.take();

        self.size -= 1;

        if self.len() == 0 {
            self.tail = NonNull::from(self.head.as_mut());
        }

        Some(first_node.value)
    }

    pub fn delete_at(&mut self, pos: usize) -> Option<T> {
        if pos >= self.size {
            panic!("index out of bounds");
        }

        if pos == 0 {
            self.pop_front()
        } else if pos == self.size - 1 {
            self.pop_back()
        } else {
            let mut curr = self.head.as_mut();
            for _ in 0..pos {
                curr = curr.next.as_mut().unwrap().as_mut();
            }

            let node_to_delete = curr.next.take().unwrap();
            curr.next = Some(node_to_delete.next.unwrap());

            self.size -= 1;

            Some(node_to_delete.value)
        }
    }

    pub fn update_at(&mut self, pos: usize, value: T) {
        if pos >= self.size {
            panic!("index out of bounds");
        }

        if pos == self.size - 1 {
            unsafe {
                self.tail.as_mut().value = value;
            }
        } else {
            let mut curr = self.head.as_mut();
            for _ in 0..pos {
                curr = curr.next.as_mut().unwrap().as_mut();
            }

            curr.value = value;
        }
    }

    pub fn peek_back(&self) -> Option<&T> {
        if self.size == 0 {
            return None;
        }
        unsafe { Some(&self.tail.as_ref().value) }
    }

    pub fn peek_back_mut(&mut self) -> Option<&mut T> {
        if self.size == 0 {
            return None;
        }
        unsafe { Some(&mut self.tail.as_mut().value) }
    }

    pub fn peek_front(&self) -> Option<&T> {
        if self.size == 0 {
            return None;
        }
        Some(&self.head.next.as_ref().unwrap().value)
    }

    pub fn peek_front_mut(&mut self) -> Option<&mut T> {
        if self.size == 0 {
            return None;
        }
        Some(&mut self.head.next.as_mut().unwrap().value)
    }

    pub fn get(&self, pos: usize) -> Option<&T> {
        if pos >= self.size {
            panic!("index out of bounds");
        }

        if pos == 0 {
            self.peek_back()
        } else if pos == self.size - 1 {
            self.peek_front()
        } else {
            let mut curr = self.head.as_ref();
            for _ in 0..pos {
                curr = curr.next.as_ref().unwrap().as_ref();
            }

            Some(&curr.value)
        }
    }

    pub fn get_mut(&mut self, pos: usize) -> Option<&mut T> {
        if pos >= self.size {
            panic!("index out of bounds");
        }

        if pos == 0 {
            self.peek_back_mut()
        } else if pos == self.size - 1 {
            self.peek_front_mut()
        } else {
            let mut curr = self.head.as_mut();
            for _ in 0..pos {
                curr = curr.next.as_mut().unwrap().as_mut();
            }

            Some(&mut curr.value)
        }
    }

    pub fn clear(&mut self) {
        while self.size != 0 {
            self.pop_front();
        }
    }
}
