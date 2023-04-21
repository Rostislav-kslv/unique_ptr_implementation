#ifndef U_PTR_
#define U_PTR_

#include <iostream>

template<typename T>
class U_ptr {
  private:
    T* ptr_;

  public:
    U_ptr() : ptr_(nullptr){};
    U_ptr(T* ptr) : ptr_(ptr){};
    U_ptr(std::nullptr_t) : ptr_(nullptr){};
    U_ptr(U_ptr&& u_ptr);
    U_ptr<T>& operator=(std::nullptr_t);
    U_ptr<T>& operator=(U_ptr<T>&& u_ptr);

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    operator bool() const {
        if (ptr_)
            return true;
        else
            return false;
    }

    U_ptr(U_ptr const& u_ptr) = delete;
    U_ptr& operator=(U_ptr const& u_ptr) = delete;

    T* release();
    void reset(T* ptr = nullptr);
    void swap(U_ptr<T>& u_ptr);

    T* get();

    ~U_ptr();
};

template<typename T>
class U_ptr<T[]> {
  private:
    T* ptr_;

  public:
    U_ptr() : ptr_(nullptr){};
    U_ptr(T* ptr) : ptr_(ptr){};
    U_ptr(std::nullptr_t) : ptr_(nullptr){};
    U_ptr(U_ptr&& u_ptr);
    U_ptr<T>& operator=(std::nullptr_t);
    U_ptr<T>& operator=(U_ptr<T[]>&& u_ptr);

    T& operator*() {
        return *ptr_;
    }

    T* operator->() {
        return ptr_;
    }

    T& operator[](int idx) {
        return *(ptr_ + idx);
    }

    operator bool() const {
        if (ptr_)
            return true;
        else
            return false;
    }

    U_ptr(U_ptr const& u_ptr) = delete;
    U_ptr& operator=(U_ptr const& u_ptr) = delete;

    T* release();
    void reset(T* ptr = nullptr);
    void swap(U_ptr<T[]>& u_ptr);

    T* get();

    ~U_ptr();
};

#include "U_ptr.inl"
#endif /* U_PTR_ */
