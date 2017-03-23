// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
class ArrayStack {
 public:
    ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        top_ = -1;
    }

    explicit ArrayStack(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        top_ = -1;
    }

    ~ArrayStack() {
        delete contents;
    }

    void push(const T& data) {  // empilha
        if (full()) {
            throw std::out_of_range("Pilha cheia");
        } else {
            top_ += 1;
            contents[top_] = data;
        }
    }

    T pop() {  // desempilha
        if (empty()) {
            throw std::out_of_range("Pilha vazia");
        } else {
            top_ -= 1;
            return (contents[top_ + 1]);
        }
    }

    T& top() {
        if (empty()) {
            throw std::out_of_range("Pilha vazia");
        } else {
            return (contents[top_]);
        }
    }

    void clear() {  // limpa
        top_ = -1;
    }

    std::size_t size() {  // tamanho
        return (top_+1);
    }

    std::size_t max_size() {
        return max_size_;
    }

    bool empty() {  // vazia
        return (top_ == -1);
    }

    bool full() {  // cheia
        return (top_ == static_cast<int>(max_size_ - 1));
    }

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};
}  // namespace structures

#endif
