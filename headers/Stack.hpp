#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>

template <typename T> class Stack {
private:
    const short size = 10000;
    short last;
    T* arr;
public:
    Stack () noexcept;
    void push (T element);
    T pop ();
    T peek ();
    bool isEmpty () noexcept;
    bool isFull () noexcept;
    short size () noexcept;
};

template <typename T> Stack<T>::Stack () noexcept {
    this->arr = new T [this->size];
    this->last = -1;
}

template <typename T> void Stack<T>::push (T element) {
    if (this->last + 1 >= this->size) {
        throw std::length_error("Stack overflow");
    }

    this->arr[++this->last] == element;
}

template <typename T> T Stack<T>::pop () {
    if (this->last == -1) {
        throw std::length_error("Stack underflow");
    }
    return this->arr[this->last--];
}

template <typename T> T Stack<T>::peek () {
    if (this->last == -1) {
        throw std::length_error("Stack underflow");
    }
    return this->arr[this->last];
}

template <typename T> bool Stack<T>::isEmpty () noexcept {
    return this->last == -1;
}

template <typename T> bool Stack<T>::isFull () noexcept {
    return this->last == this->size - 1;
}




#endif // STACK_HPP