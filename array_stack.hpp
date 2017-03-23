// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

/**
 *	Estrutura de dados do tipo Pilha.
 *
 *	Organiza os elementos no padrão LIFO (Last In First Out),
 *	onde o último elemento a ser inserido é o primeiro a ser retirado.
 *
 * @tparam	T	Tipo de dado do template.
*/
template<typename T>
class ArrayStack {
 public:
 /**
  *	Construtor padrão.
  *	
  *	Cria um objeto da classe Pilha com tamanho máximo padrão (DEFAULT_SIZE).
  *
  *	@see ArrayStack(std::size_t max)
 */
    ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        top_ = -1;
    }

 /**
  *	Construtor de Pilha com tamanho definido.
  *	
  *	Cria um objeto da classe Pilha com tamanho parametrizado.
  *
  *	@param	max	inteiro positivo que representa o tamanho máximo da pilha.
  *
  * @see ArrayStack()
 */
    explicit ArrayStack(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        top_ = -1;
    }

 /**
  *	Destrutor da classe Pilha.
  *	
  *	Deleta o objeto e desaloca memória.
 */
    ~ArrayStack() {
        delete [] contents;
    }

 /**
  *	Insere novo elemento no topo da pilha.
  *	
  *	@throws	"std::out_of_range" caso a pilha esteja cheia.
  *
  *	@param	data	dado do tipo T a ser inserido.
 */
    void push(const T& data) {
        if (full()) {
            throw std::out_of_range("Pilha cheia");
        } else {
            top_ += 1;
            contents[top_] = data;
        }
    }

 /**
  *	Retira elemento do topo da pilha.
  *	
  *	@throws	"std::out_of_range" caso a pilha esteja vazia.
  *
  *	@return	Elemento que estava no topo da pilha.
 */
    T pop() {
        if (empty()) {
            throw std::out_of_range("Pilha vazia");
        } else {
            top_ -= 1;
            return (contents[top_ + 1]);
        }
    }

 /**
  *	Olha o elemento no topo da pilha, sem retirá-lo.
  *	
  *	@throws	"std::out_of_range" caso a pilha esteja vazia.
  *
  *	@return	Elemento que está no topo da pilha.
 */
    T& top() {
        if (empty()) {
            throw std::out_of_range("Pilha vazia");
        } else {
            return (contents[top_]);
        }
    }

 /**
  *	Limpa os dados da pilha.
  *	
 */
    void clear() {
        top_ = -1;
    }

 /**
  *	Verifica o tamanho da pilha.
  *	
  *	@return	Inteiro com o número de elementos da pilha.
 */
    std::size_t size() {
        return (top_+1);
    }

 /**
  *	Verifica o tamanho máximo da pilha.
  *	
  *	@return	Inteiro com o tamanho máximo da pilha.
 */
    std::size_t max_size() {
        return max_size_;
    }

 /**
  *	Verifica se a pilha está vazia.
  *	
  *	@return	True se a pilha estiver vazia, False caso contrário.
 */
    bool empty() {
        return (top_ == -1);
    }

 /**
  *	Verifica se a pilha está cheia.
  *	
  *	@return	True se a pilha estiver cheia, False caso contrário.
 */
    bool full() {
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
