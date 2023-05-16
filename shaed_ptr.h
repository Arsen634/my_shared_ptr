#pragma once

template <typename T>
class shared_ptr {
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(shared_ptr<T>& other);
    ~shared_ptr();
    shared_ptr<T> operator= (shared_ptr<T>& other);
    T operator*();
    size_t use_count() const;
    bool unique() const;
    template<typename T1>
    friend void swap(shared_ptr<T1>& p1, shared_ptr<T1>& p2);
private:
    T* ptr;
    size_t* count;
};

template<typename T1>
void swap(shared_ptr<T1>& p1, shared_ptr<T1>& p2)
{
    shared_ptr<int> p(new T1);
    p = p1;
    p.ptr = p1.ptr;
    p1.ptr = p2.ptr;
    p2.ptr = p.ptr;
    p.count = p1.count;
    p1.count = p2.count;
    p2.count = p.count;
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
T shared_ptr<T>::operator*()
{
    return *ptr;
}

template<typename T>
shared_ptr<T> shared_ptr<T>::operator=(shared_ptr<T>& other) {
    if (this != &other) {
        shared_ptr<T>::~shared_ptr();

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



