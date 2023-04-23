#pragma once

#include <iostream>

template <typename T>
class shared_ptr {
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(shared_ptr<T>& other);
    shared_ptr<T> operator= (shared_ptr<T>& other);
    ~shared_ptr();
    size_t use_count() const;
    bool unique() const;
private:
    T* ptr;
    size_t* count;
};

template<typename T>
shared_ptr<T>::shared_ptr() :ptr(nullptr), count(nullptr) {}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr) : ptr(ptr), count(new size_t(1)) {}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>& other) : count(other.count), ptr(other.ptr) {
    (*count)++;
}

template<typename T>
shared_ptr<T> shared_ptr<T>::operator=(shared_ptr<T>& other) {
    if (this != &other) {
        shared_ptr<T>::~shared_ptr();

        ptr = other.ptr;
        count = other.count;
        (*count)++;
    }
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    if (count) {
        if (*count == 1) {
            delete count;
            delete ptr;
        }
        else (*count)--;
    }
}

template<typename T>
size_t shared_ptr<T>::use_count() const {
    return (count) ? *count : 0;
}
template<typename T>
bool shared_ptr<T>::unique() const {
    return (*count == 1);
}