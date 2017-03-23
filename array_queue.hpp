// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

/**
 *	Estrutura de dados do tipo Fila.
 *
 *	Organiza os elementos no padrão FIFO (First In First Out),
 *	onde o primeiro elemento a ser inserido é o primeiro a ser retirado.
 *	Conforme a definição geralmente conhecida de "fila".
 *
 * @tparam	T	Tipo de dado do template.
*/
template<typename T>
class ArrayQueue {
 public:
 /**
  *	Construtor padrão.
  *	
  *	Cria um objeto da classe ArrayQueue com tamanho máximo padrão (DEFAULT_SIZE).
  *
  *	@see ArrayQueue(std::size_t max)
 */
    ArrayQueue() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        size_ = 0u;
    }

 /**
  *	Construtor de Fila com tamanho definido.
  *	
  *	Cria um objeto da classe ArrayQueue com tamanho parametrizado.
  *
  *	@param	max	inteiro positivo que representa o tamanho máximo da fila.
  *
  * @see ArrayQueue()
 */
    explicit ArrayQueue(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        size_ = 0u;
    }

 /**
  *	Destrutor da classe ArrayQueue.
  *	
  *	Deleta o objeto e desaloca memória dos elementos.
 */
    ~ArrayQueue() {
        delete [] contents;
    }

 /**
  *	Insere novo elemento no final da fila.
  *	
  *	@throws	"std::out_of_range" caso a fila esteja cheia.
  *
  *	@param	data	dado do tipo T a ser inserido.
 */
    void enqueue(const T& data) {
        if (full()) {
            throw std::out_of_range("Fila cheia");
        } else {
            contents[size_] = data;
            size_++;
        }
    }

 /**
  *	Retira o primeiro elemento do início da fila.
  *	
  * Retira o primeiro elemento e realoca todos os outros elementos
  *	uma posição a frente.
  *
  *	@throws	"std::out_of_range" caso a fila esteja vazia.
  *
  *	@return	Elemento que estava na primeira posição da fila.
 */
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Fila vazia");
        } else {
            T first = contents[0];
            for (auto i = 0u; i < size_-1; ++i) {
            	contents[i] = contents[i+1];
            }
            size_--;
            return first;
        }
    }

 /**
  *	Olha o elemento no final da fila, sem retirá-lo.
  *	
  *	@throws	"std::out_of_range" caso a fila esteja vazia.
  *
  *	@return	Elemento que está no final da fila.
 */
    T& back() {
        if (empty()) {
            throw std::out_of_range("Fila vazia");
        } else {
            return (contents[size_-1]);
        }
    }

 /**
  *	Limpa os dados da fila.
  *	
 */
    void clear() {
        size_ = 0u;
    }

 /**
  *	Verifica o tamanho atual da fila.
  *	
  *	@return	Inteiro com o número de elementos da fila.
 */
    std::size_t size() {
        return size_;
    }

 /**
  *	Verifica o tamanho máximo da fila.
  *	
  *	@return	Inteiro com o tamanho máximo da fila.
 */
    std::size_t max_size() {
        return max_size_;
    }

 /**
  *	Verifica se a fila está vazia.
  *	
  *	@return	True se a fila estiver vazia, False caso contrário.
 */
    bool empty() {
        return (size_ == 0);
    }

 /**
  *	Verifica se a fila está cheia.
  *	
  *	@return	True se a fila estiver cheia, False caso contrário.
 */
    bool full() {
        return (size_ == max_size_);
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};
}  // namespace structures

#endif
