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
    Optional() : empty(true){};

    Optional(T const &val) {
        new(element) T(val);
        empty = false;
    }

    ~Optional() {
        if (!empty) {
            reinterpret_cast<T *> (element)->~T();
        }
    }

    Optional(Optional<T> const &other): empty(other.empty){
        if (!other.empty) {
            new(element) T(*reinterpret_cast<const T*>(other.element));
        }
    };
    Optional& operator=(const Optional<T>& other) {
        Optional<T> temp(other);
        Swap(temp);
        return *this;
    }
    void clear() {
        if (!empty) {
            reinterpret_cast<T *> (element)->~T();
        }
        empty = true;
    }
    explicit operator bool() const {
        return !empty;
    }
    T& operator*() {
        assert(!empty);
        return *reinterpret_cast< T*>(element);
    }
    T* operator->() {
        assert(!empty);
        return reinterpret_cast< T*>(element);

    };
    void Swap(Optional<T>& other) {
        std::swap(element, other.element);
        std::swap(empty, other.empty);
    }

private:
    bool empty;
    typename std::aligned_storage<sizeof(T), alignof(T)>::type element[1];
};

template< typename T>
void swap (Optional<T>& a, Optional<T>& b) {
    a.Swap(b);
}


#endif //OPTIONAL_H
