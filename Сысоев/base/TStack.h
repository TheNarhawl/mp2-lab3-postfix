#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

const int MaxStackSize = 100;

template <typename T>
class TStack {
private:
    T* pMem;
    size_t reserved;
    size_t memorySize;

    friend void swap(TStack<T>& lhs, TStack<T>& rhs)
    {
        using std::swap;
        swap(lhs.pMem, rhs.pMem);
        swap(lhs.reserved, rhs.reserved);
        swap(lhs.memorySize, rhs.memorySize);
    }

public:
    TStack();
    TStack(int reserved);
    TStack(const std::vector<T>& vec);
    ~TStack();

    TStack(const TStack<T>& other);
    TStack<T>& operator=(TStack<T> other);
    TStack(TStack<T>&& other);
    TStack<T>& operator=(TStack<T>&& other);

    T& back();
    void resize(size_t newReserved);
    void push(T obj);
    void pop();
    bool empty() const;
    inline size_t getSize() const;
    inline size_t getReserved() const;

    bool operator==(const TStack<T>& other) const;
    bool operator!=(const TStack<T>& other) const;

    void debugPrintState();

    friend std::ostream& operator<<(std::ostream& os, const TStack<T>& ds)
    {
        os << "{ ";
        for (size_t i = 0; i < ds.memorySize; i++)
        {
            os << ds.pMem[i];
            os << " ";
        }
        os << "}";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, TStack<T>& ds)
    {
        T obj;
        while (is >> obj)
            ds.push(obj);
        
        return is;
    }   
};

template <typename T>
TStack<T>::TStack()
{
    pMem = new T[1];
    reserved = 1;
    memorySize = 0;
}

template <typename T>
TStack<T>::TStack(int reserved)
{
    if (reserved <= 0)
        throw std::invalid_argument("Reserved stack size must be bigger or equal 1");

    pMem = new T[reserved];
    this->reserved = reserved;
    memorySize = 0;
}

template <typename T>
TStack<T>::TStack(const std::vector<T>& v)
{
    pMem = new T[v.size()];
    this->reserved = v.size();
    this->memorySize = v.size();

    for (int i = 0; i < memorySize; i++)
    {
        *(pMem + i) = v[i];
    }
}

template <typename T>
TStack<T>::~TStack()
{
    delete[] pMem;
}

template <typename T>
TStack<T>::TStack(const TStack<T>& other)
{
    pMem = nullptr;
    reserved = 0;
    memorySize = 0;

    if (other.pMem != nullptr)
    {
        pMem = new T[other.reserved];
        reserved = other.reserved;
        memorySize = other.memorySize;

        for (size_t i = 0; i < memorySize; i++)
        {
            pMem[i] = other.pMem[i];
        }
    }
}


template <typename T>
TStack<T>& TStack<T>::operator=(TStack<T> other)
{
    swap(*this, other);
    return *this;
}

template <typename T>
TStack<T>::TStack(TStack<T>&& other)
{
    pMem = other.pMem;
    reserved = other.reserved;
    memorySize = other.memorySize;

    other.pMem = nullptr;
    other.reserved = 0;
    other.memorySize = 0;
}

template <typename T>
TStack<T>& TStack<T>::operator=(TStack<T>&& other)
{
    TStack tmp = std::move(other);
    swap(*this, tmp);
    return *this;
}

template <typename T>
T& TStack<T>::back()
{
    if (memorySize == 0)
        throw std::out_of_range("Trying back() on empty stack");
    
    return pMem[memorySize - 1];
}

template <typename T>
void TStack<T>::resize(size_t newReserved)
{
    T* newPMem = new T[newReserved];
    
    if (newReserved < memorySize)
        std::move(pMem, pMem + newReserved, newPMem);
    else
        std::move(pMem, pMem + memorySize, newPMem);
    
    delete[] pMem;
    pMem = newPMem;
    memorySize = std::min(memorySize, newReserved);
    reserved = newReserved;
}

template <typename T>
void TStack<T>::push(T obj)
{
    if (memorySize == reserved)
        resize(reserved * 2);

    pMem[memorySize++] = obj;
}

template <typename T>
void TStack<T>::pop()
{
    if (memorySize == 0)
        throw std::out_of_range("Trying pop() on empty stack");
    
    memorySize--;
}

template <typename T>
bool TStack<T>::empty() const
{
    return memorySize == 0;
}

template <typename T>
inline size_t TStack<T>::getSize() const
{
    return memorySize;
}

template <typename T>
inline size_t TStack<T>::getReserved() const
{
    return reserved;
}

template<typename T>
bool TStack<T>::operator==(const TStack<T>& other) const
{
    if (memorySize != other.memorySize)
        return false;

    for (size_t i = 0; i < memorySize; i++)
    {
        if (pMem[i] != other.pMem[i])
            return false;
    }

    return true;
}

template<typename T>
bool TStack<T>::operator!=(const TStack<T>& other) const
{
    return !(*this == other);
}

template <typename T>
void TStack<T>::debugPrintState()
{
    std::cout << "s: " << this->memorySize << " r: "
              << this->reserved << '\n';
}

#endif
