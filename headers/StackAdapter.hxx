#ifndef STACK_ADAPTER_HXX
#define STACK_ADAPTER_HXX



#include <Stack.hxx>
#include <stdexcept>



template <typename T> class StackAdapter {
private:
    unsigned long long* nop;
    Stack <T>* unit;

public:
    StackAdapter (unsigned long long* nop) noexcept;
    ~StackAdapter () noexcept;
    void push (T element);
    T pop ();
    T peek ();
    bool isEmpty () noexcept;
    bool isFull () noexcept;
    short size () noexcept;
    T& operator[] (const short index);
    void sort ();
};



template <typename T> StackAdapter<T>::StackAdapter (unsigned long long* nop) noexcept { // O(1)
    this->nop = nop;
    this->unit = new Stack <T> (nop);
    *this->nop += 3;
}


template <typename T> StackAdapter<T>::~StackAdapter () noexcept { // O(1)
    ++*this->nop;
    delete this->unit;
}


template <typename T> void StackAdapter<T>::push (T element) { // O(1)
    ++*this->nop;
    this->unit->push(element);
}


template <typename T> T StackAdapter<T>::pop () { // O(1) or 5
    ++*this->nop;
    return this->unit->pop();
}


template <typename T> T StackAdapter<T>::peek () { // O(1) or 4
    ++*this->nop;
    return this->unit->peek();
}


template <typename T> bool StackAdapter<T>::isEmpty () noexcept { // O(1) or 3
    ++*this->nop;
    return this->unit->isEmpty();
}


template <typename T> bool StackAdapter<T>::isFull () noexcept { // O(1) or 3
    ++*this->nop;
    return this->unit->isFull();
}


template <typename T> short StackAdapter<T>::size () noexcept { // O(1) or 3
    ++*this->nop;
    return this->unit->size();
}


template <typename T> T& StackAdapter<T>::operator[] (short index) { // O(2n) or (27+8n)
    ++*this->nop;
    if (this->unit->isEmpty()) {
        throw std::underflow_error("Stack underflow");
    }

    if (index >= this->unit->size() - 1) {
        *this->nop += 5;
        return this->unit->peekWithPointer();
    }
    else if (index < 0) {
        *this->nop += 6;
        if (this->unit->size() + index >= 0) {
            *this->nop += 3;
            index = this->unit->size() + index;
        }
        else {
            ++*this->nop;
            index = 0;
        }
    }
    else {
        *this->nop += 3;
    }
    
    short size = this->unit->size() - index - 1;
    T temp[size];
    *this->nop += 8;

    for (short i = size - 1; i >= 0; --i) {
        temp[i] = this->unit->pop();
        *this->nop += 4;
    }

    T& element = this->unit->peekWithPointer();
    
    *this->nop += 4;
    for (short i = 0; i < size; ++i) {
        this->unit->push(temp[i]);
        *this->nop += 4;
    }

    ++*this->nop;
    return element;
}


template <typename T> void StackAdapter<T>::sort () { // O(2n + n^2) or (9 + 15n + 15n^2)
    ++*this->nop;
    if (this->unit->isEmpty()) {
        throw std::underflow_error("Stack underflow");
    }

    short size = this->unit->size();
    T temp[size];
    *this->nop += 6;

    for (short i = size - 1; i >= 0; --i) {
        temp[i] = this->unit->pop();
        *this->nop += 4;
    }

    for (int i = 0; i < size - 1; ++i) {
        *this->nop += 7;
        for (int j = 0; j < size - i - 1; ++j) {
            *this->nop += 8;
            if (temp[j] > temp[j + 1]) {
                T tempValue = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = tempValue;
                *this->nop += 7;
            }
        }
    }

    *this->nop += 2;
    for (short i = 0; i < size; ++i) {
        this->unit->push(temp[i]);
        *this->nop += 4;
    }
}



#endif // STACK_ADAPTER_HXX