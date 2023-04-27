#pragma once

template <typename T>
class shared_ptr
{
public:
    shared_ptr(T* ptr) : ptr(ptr == nullptr? nullptr : ptr), count(new size_t(1) == nullptr ? nullptr : new size_t(1)) {}

    ~shared_ptr()
    {
     if (count)
        if (*count == 1)
        {
           delete count;
           delete ptr;
        }
        else
        {
           (*count)--;
        }
    }

    shared_ptr(shared_ptr<T>& other) : count(other.count), ptr(other.ptr)
    {
     (*count)++;
    }

    shared_ptr<T> operator= (shared_ptr<T>& other)
    {
        if (this != &other) {
            if (count) {
                if (*count == 1) {
                    delete count;
                    delete ptr;
                }
                else (*count)--;
            }

            ptr = other.ptr;
            count = other.count;
            (*count)++;
        }
        return *this;
    }
    
    size_t use_count() const 
    {
        return (count) ? *count : 0;
    }

    bool unique() const 
    {
        return (*count == 1);
    }

private:
    T* ptr;
    size_t* count;
};
