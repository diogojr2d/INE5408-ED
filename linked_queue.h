// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "./linked_list.h"

namespace structures {

/**
 *  Estrutura de dados do tipo Fila Encadeada.
 *
 *  Organiza os elementos em uma Fila (FIFO) que pode ser ordenada ou não,
 *  onde o primeiro elemento a ser inserido é o primeiro a ser retirado.
 *
 * @tparam  T   Tipo de dado do template.
*/
template<typename T>
class LinkedQueue {
 public:
 /**
  * @brief Construtor padrão.
  * 
  * Cria um objeto da classe LinkedQueue.
 */
    LinkedQueue(): linkedList_{}
    {}

 /**
  * @brief Destrutor da classe LinkedQueue.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
  *
  * @see LinkedQueue()
 */
    ~LinkedQueue() {}

 /**
  * @brief Limpa os dados da Fila.
  * 
  * Limpa a Fila e desaloca memória de cada elemento.
 */
    void clear() {
        linkedList_.clear();
    }

 /**
  * @brief Insere novo elemento no final da Fila.
  * 
  * @param  data    dado do tipo T a ser inserido.
 */
    void enqueue(const T& data) {
    	linkedList_.push_back(data);
    }

 /**
  * @brief Retira o primeiro elemento da Fila.
  * 
  * Retira o primeiro elemento e realoca todos os outros elementos
  * uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Fila esteja vazia.
  *
  * @return Elemento que estava na primeira posição da Fila.
 */
    T dequeue() {
        return linkedList_.pop_front();
    }

 /**
  * Olha o primeiro elemento da fila, sem retirá-lo.
  * 
  * @throws "std::out_of_range" caso a fila esteja vazia.
  *
  * @return Elemento que está no final da fila.
 */
    T& front() const {
        return linkedList_.at(0);
    }

 /**
  * Olha o elemento no final da fila, sem retirá-lo.
  * 
  * @throws "std::out_of_range" caso a fila esteja vazia.
  *
  * @return Elemento que está no final da fila.
 */
    T& back() const {
        return linkedList_.at(size()-1);
    }

 /**
  * Verifica se a Fila está vazia.
  * 
  * @return True se a Fila estiver vazia, False caso contrário.
 */
    bool empty() const {
        return linkedList_.empty();
    }

 /**
  * Verifica o tamanho atual da Fila.
  * 
  * @return Inteiro com o número de elementos da Fila.
 */
    std::size_t size() const {
        return linkedList_.size();
    }

 private:
    LinkedList<T> linkedList_;
};

}  // namespace structures

#endif
