//
// Created by Nika on 13.10.2018.
//

#ifndef OPTIONAL_H
#define OPTIONAL_H
#include <iostream>
#include <cassert>
template<typename T>
struct Optional {
public:
    Optional() : empty(true){}

    Optional(T const &val) {
        new(&element) T(val);
        empty = false;

    }

    ~Optional() {
        clear();
    }

    Optional(Optional<T> const &other): empty(other.empty){
        if (!other.empty) {
            new(&element) T(*reinterpret_cast<const T*>(&other.element));
        }
    };
    Optional& operator=(const Optional<T>& other) {
        Optional<T> temp(other);
        Swap(temp);
        return *this;
    }
    void clear() {
        if (!empty) {
            reinterpret_cast<T *> (&element)->~T();
        }
        empty = true;
    }
    explicit operator bool() const {
        return !empty;
    }
    T& operator*() {
        assert(!empty);
        return *reinterpret_cast< T*>(&element);
    }
    T* operator->() {
        assert(!empty);
        return reinterpret_cast< T*>(&element);

    };
    const T& operator*() const{
        assert(!empty);
        return *reinterpret_cast<const T*>(&element);
    }
    const T* operator->() const {
        assert(!empty);
        return reinterpret_cast<const T*>(&element);

    };
    void Swap(Optional<T>& other) {
        using std::swap;
        if (!empty && !other.empty) {
            swap(*reinterpret_cast< T *>(&element), *reinterpret_cast< T *>(&other.element));
        } else if (!empty){
            new(&other.element) T(*reinterpret_cast<const T*>(&element));
            reinterpret_cast<T *> (&element)->~T();
        } else if (!other.empty) {
            new(&element) T(*reinterpret_cast<const T*>(&other.element));
            reinterpret_cast<T *> (&other.element)->~T();
        }
        swap(empty, other.empty);
    }

private:
    bool empty;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type element;
};

template< typename T>
void swap (Optional<T>& a, Optional<T>& b) {
    a.Swap(b);
}


#endif //OPTIONAL_H
