#pragma once
#include <iostream>

class Test;

template <typename T>
class shared_ptr {
public:
    friend class Test;
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(shared_ptr<T>& other);
    ~shared_ptr();
    shared_ptr<T> operator= (shared_ptr<T>& other);
    T operator*();
    T* original();
    size_t use_count() const;
    template<typename T>
    friend void swap(shared_ptr<T>& p1, shared_ptr<T>& p2);
    void clearing();
    bool unique() const;
    bool existsPtr() const;
    bool existsCount() const;
private:
    T* m_ptr;
    size_t* m_count;
};

template<typename T>
void swap(shared_ptr<T>& p1, shared_ptr<T>& p2)
{
    T* ptr = p1.m_ptr;
    p1.m_ptr = p2.m_ptr;
    p2.m_ptr = ptr;
    size_t* size = p1.m_count;
    p1.m_count = p2.m_count;
    p2.m_count = size;
}

template<typename T>
shared_ptr<T>::shared_ptr() :m_ptr(nullptr), m_count(nullptr) {}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr) : m_ptr(ptr), m_count(new size_t(1)) {}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>& other) : m_count(other.m_count), m_ptr(other.m_ptr) {
    if (m_count)
    {
        ++(*m_count);
    }
}

template<typename T>
T shared_ptr<T>::operator*()
{
    try
    {
        return *m_ptr;
    }
    catch (const std::exception& is)
    {
        std::cout << is.what();
    }

} 

template<typename T>
void shared_ptr<T>::clearing()
{
    if (m_count)
        delete m_count;
    if (m_ptr)
        delete m_ptr;
    m_count = nullptr;
    m_ptr = nullptr;
}

template<typename T>
T* shared_ptr<T>::original()
{
    try
    {
        return m_ptr;
    }
    catch (const std::exception& is)
    {
        std::cout << is.what();
    }
}

template<typename T>
shared_ptr<T> shared_ptr<T>::operator=(shared_ptr<T>& other) {
    if (this != &other)
    {
        if (m_count)
        {
            if (*m_count == 1)
            {
                clearing();
            }
            else --(*m_count);
        }
        m_ptr = other.m_ptr;
        m_count = other.m_count;
        if (m_count)
        {
            ++(*m_count);
        }

    }
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr()
{
    if (m_count)
    {
        if (*m_count == 1)
        {
            clearing();
        }
        else --(*m_count);
    }

}

template<typename T>
size_t shared_ptr<T>::use_count() const
{
    return (m_count) ? *m_count : 0;
}

template<typename T>
bool shared_ptr<T>::unique() const
{
    return use_count() == 1;
}

template<typename T>
bool shared_ptr<T>::existsPtr() const
{
    return (m_ptr);
}

template<typename T>
bool shared_ptr<T>::existsCount() const
{
    return (m_count);
}
