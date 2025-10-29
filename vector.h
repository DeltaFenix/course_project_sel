#pragma once
#include <stdexcept>
#include <cstddef>

class Vector {
private:
    int* data;
    std::size_t sz;
    std::size_t cap;

    void reallocate(std::size_t newCap) {
        int* newData = new int[newCap];
        for (std::size_t i = 0; i < sz; ++i)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        cap = newCap;
    }

public:
    Vector() : data(nullptr), sz(0), cap(0) {}
    ~Vector() { delete[] data; }

    Vector(const Vector& other) : data(nullptr), sz(other.sz), cap(other.cap) {
        if (cap) {
            data = new int[cap];
            for (std::size_t i = 0; i < sz; ++i)
                data[i] = other.data[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            sz = other.sz;
            cap = other.cap;
            data = cap ? new int[cap] : nullptr;
            for (std::size_t i = 0; i < sz; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    void push_back(int value) {
        if (sz == cap)
            reallocate(cap ? cap * 2 : 1);
        data[sz++] = value;
    }

    void pop_back() {
        if (sz == 0)
            throw std::out_of_range("Empty vector");
        --sz;
    }

    int& operator[](std::size_t index) {
        if (index >= sz)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    std::size_t size() const { return sz; }
    std::size_t capacity() const { return cap; }
    int& front() { return data[0]; }
    int& back() { return data[sz - 1]; }
    bool empty() const { return sz == 0; }

    void reserve(std::size_t newCap) {
        if (newCap > cap)
            reallocate(newCap);
    }

    void resize(std::size_t newSize) {
        if (newSize > cap)
            reallocate(newSize);
        sz = newSize;
    }

    void clear() { sz = 0; }
};