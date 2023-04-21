#include "U_ptr.hpp"

template<typename T>
U_ptr<T>::U_ptr(U_ptr&& u_ptr) {
    if (ptr_ != u_ptr.ptr_) {
        ptr_ = u_ptr.ptr_;
        u_ptr.ptr_ = nullptr;
    }
}

template<typename T>
U_ptr<T>& U_ptr<T>::operator=(std::nullptr_t) {
    reset();
    return *this;
}

template<typename T>
U_ptr<T>& U_ptr<T>::operator=(U_ptr<T>&& u_ptr) {
    if (ptr_ == u_ptr.ptr_) {
        return *this;
    }

    delete ptr_;
    ptr_ = u_ptr.ptr_;
    u_ptr.ptr_ = nullptr;
    return *this;
}

template<typename T>
T* U_ptr<T>::release() {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template<typename T>
void U_ptr<T>::reset(T* ptr) {
    if (ptr_) {
        delete ptr_;
    }
    ptr_ = ptr;
}

template<typename T>
void U_ptr<T>::swap(U_ptr<T>& u_ptr) {
    std::swap(ptr_, u_ptr.ptr_);
}

template<typename T>
T* U_ptr<T>::get() {
    return ptr_;
}

template<typename T>
U_ptr<T>::~U_ptr() {
    //std::cout << "Called delete without []" << std ::endl;
    delete ptr_;
}

template<typename T, typename... Args>
typename std::enable_if<!std::is_array<T>::value, U_ptr<T> >::type make_uptr(Args&&... args) {
    return U_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
U_ptr<T[]>::U_ptr(U_ptr&& u_ptr) {
    if (ptr_ != u_ptr.ptr_) {
        ptr_ = u_ptr.ptr_;
        u_ptr.ptr_ = nullptr;
    }
}

template<typename T>
U_ptr<T>& U_ptr<T[]>::operator=(std::nullptr_t) {
    reset();
    return *this;
}

template<typename T>
U_ptr<T>& U_ptr<T[]>::operator=(U_ptr<T[]>&& u_ptr) {
    if (ptr_ == u_ptr.ptr_) {
        return *this;
    }

    delete[] ptr_;
    ptr_ = u_ptr.ptr_;
    u_ptr.ptr_ = nullptr;
    return *this;
}

template<typename T>
T* U_ptr<T[]>::release() {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
}

template<typename T>
void U_ptr<T[]>::reset(T* ptr) {
    if (ptr_) {
        delete[] ptr_;
    }
    ptr_ = ptr;
}

template<typename T>
void U_ptr<T[]>::swap(U_ptr<T[]>& u_ptr) {
    std::swap(ptr_, u_ptr.ptr_);
}

template<typename T>
T* U_ptr<T[]>::get() {
    return ptr_;
}

template<typename T>
U_ptr<T[]>::~U_ptr() {
    //std::cout << "Called delete[]" << std ::endl;
    delete[] ptr_;
}

template<typename T>

typename std::enable_if<std::is_array<T>::value, U_ptr<T> >::type make_uptr(int size) {
    typedef typename std::remove_extent<T>::type RT;
    return U_ptr<T>(new RT[size]());
}
