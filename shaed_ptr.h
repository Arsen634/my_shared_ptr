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
    void clearing();
    bool existsPtr() const;
    bool existsCount() const;
    template<typename T>
    friend void swap(shared_ptr<T>& p1, shared_ptr<T>& p2);

private:
    T* mPtr;
    size_t* mCount;
};

template<typename T>
void swap(shared_ptr<T>& p1, shared_ptr<T>& p2)
{
    T* p_ptr = p1.mPtr;
    p1.mPtr = p2.mPtr;
    p2.mPtr = p_ptr;
    size_t* p_zize_t = p1.mCount;
    p1.mCount = p2.mCount;
    p2.mCount = p_zize_t;
}

template<typename T>
shared_ptr<T>::shared_ptr() :mPtr(nullptr), mCount(nullptr) {}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr) : mPtr(ptr), mCount(new size_t(1)) {}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>& other) : mCount(other.mCount), mPtr(other.mPtr) {
    if (mCount)
    {
        ++(*mCount);
    }
}

template<typename T>
T shared_ptr<T>::operator*()
{
    return *mPtr;
}

template<typename T>
void shared_ptr<T>::clearing()
{
    delete mCount;
    if (mPtr)
    {
        delete mPtr;
    }
    mCount = nullptr;
    mPtr = nullptr;
}

template<typename T>
shared_ptr<T> shared_ptr<T>::operator=(shared_ptr<T>& other) {
    if (this != &other)
    {
        if (mCount)
        {
            if (*mCount == 1)
            {
                clearing();
            }
            else --(*mCount);
        }
        mPtr = other.mPtr;
        mCount = other.mCount;
        if (mCount)
        {
            ++(*mCount);
        }

    }
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr()
{
    if (mCount)
    {
        if (*mCount == 1)
        {
            clearing();
        }
        else --(*mCount);
    }

}

template<typename T>
size_t shared_ptr<T>::use_count() const
{
    return (mCount) ? *mCount : 0;
}

template<typename T>
bool shared_ptr<T>::unique() const
{
    return (mCount) ? (*mCount == 1) : false;
}

template<typename T>
bool shared_ptr<T>::existsPtr() const
{
    return (mPtr);
}

template<typename T>
bool shared_ptr<T>::existsCount() const
{
    return (mCount);
}
