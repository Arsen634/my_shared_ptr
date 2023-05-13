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
    void output();
    friend void swapPtr(shared_ptr<T>& p1, shared_ptr<T>& p2);
private:
    T* ptr;
    size_t* count;
};

template<typename T>
void swapPtr(shared_ptr<T>& p1, shared_ptr<T>& p2)
{
    if (p1 != p2) {
        try
        {
            T p = p1.ptr;
            p1.ptr = p2.ptr;
            p2.ptr = p;
            size_t pp = p1.count;
            p1.count = p2.count;
            p2.count = pp;
        }
        catch (const std::exception& f)
        {
            std::cout << f.what() << "\n";
        }
    }

}

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
        if (ptr)
        {
            ptr = other.ptr;
        }
        if (count)
        {
            count = other.count;
            ++(*count);
        }
    }
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    if (count) {
        if (*count == 1) {
            delete count;
            if (ptr)
            {
                delete ptr;
            }
        }
        else --(*count);
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
template<typename T>
void shared_ptr<T>::output()
{
    std::cout << *ptr << "\n";
}



int main()
{
    shared_ptr<int> p1(new int(1));
    p1.output();
    shared_ptr<int> p2(new int(2));
    p2.output();
    std::cout << "-------------";
    // swap_ptr();

}

