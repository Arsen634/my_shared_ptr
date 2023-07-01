#pragma once

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
    T* SetM_ptr();
    size_t use_count() const;
    template<typename T>
    friend void swap(shared_ptr<T>& p1, shared_ptr<T>& p2);
    bool unique() const;
    bool existsPtr() const;
    bool existsCount() const;
private:
    void link_does_not_exist();
    void clear();
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
void shared_ptr<T>::link_does_not_exist()
{
    if (not(m_ptr))
        throw std::exception("error: the link does not exist ");
}

template<typename T>
T shared_ptr<T>::operator*()
{
    link_does_not_exist();
    return *m_ptr;
}

template<typename T>
void shared_ptr<T>::clear()
{
    if (m_count)
        delete m_count;
    if (m_ptr)
        delete m_ptr;
    m_count = nullptr;
    m_ptr = nullptr;
}

template<typename T>
T* shared_ptr<T>::SetM_ptr()
{
    link_does_not_exist();
    return m_ptr;
}

template<typename T>
shared_ptr<T> shared_ptr<T>::operator=(shared_ptr<T>& other) {
    if (this != &other)
    {
        if (m_count)
        {
            if (*m_count == 1)
            {
                clear();
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
            clear();
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
