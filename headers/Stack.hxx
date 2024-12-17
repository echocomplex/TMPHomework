#ifndef STACK_HXX
#define STACK_HXX


#define STACK_SIZE 10000


#include <stdexcept>
#include <iostream>



template <typename T> class Stack {
private:
    short last;
    T* arr;
    unsigned long long* nop;

public:
    Stack (unsigned long long* nop) noexcept;
    ~Stack () noexcept;
    void push (T element);
    T pop ();
    T peek ();
    T& peekWithPointer ();
    bool isEmpty () noexcept;
    bool isFull () noexcept;
    short size () noexcept;
};



template <typename T> Stack<T>::Stack (unsigned long long* nop) noexcept { // O(1) or 3
    this->nop = nop;
    this->arr = new T [STACK_SIZE];
    this->last = -1;
    *this->nop += 3;
}


template <typename T> Stack<T>::~Stack () noexcept { // O(1) or 1
    ++*this->nop;
    delete[] this->arr;
}


template <typename T> void Stack<T>::push (T element) { // O(1) or 4
    *this->nop += 2;
    if (this->last + 1 >= STACK_SIZE) {
        throw std::overflow_error("Stack overflow");
    }
    this->arr[++this->last] = element;
    *this->nop += 2;
}


template <typename T> T Stack<T>::pop () { // O(1) or 4
    ++*this->nop;
    if (this->last == -1) {
        throw std::underflow_error("Stack underflow");
    }
    *this->nop += 3;
    return this->arr[this->last--];
}


template <typename T> T Stack<T>::peek () { // O(1) or 3
    ++*this->nop;
    if (this->last == -1) {
        throw std::underflow_error("Stack underflow");
    }
    *this->nop += 2;
    return this->arr[this->last];
}


template <typename T> bool Stack<T>::isEmpty () noexcept { // O(1) or 2
    *this->nop += 2;
    return this->last <= -1;
}


template <typename T> bool Stack<T>::isFull () noexcept { // O(1) or 2
    *this->nop += 2;
    return this->last >= STACK_SIZE - 1;
}


template <typename T> short Stack<T>::size () noexcept { // O(1) or 2
    *this->nop += 2;
    return this->last + 1;
}


template <typename T> T& Stack<T>::peekWithPointer () { // O(1) or 3
    ++*this->nop;
    if (this->last == -1) {
        throw std::underflow_error("Stack underflow");
    }
    *this->nop += 2;
    return this->arr[this->last];
}



#endif // STACK_HXX