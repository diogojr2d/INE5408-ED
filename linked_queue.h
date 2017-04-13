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
 *  Organiza os elementos em uma Fila que pode ser ordenada ou não,
 *  permitindo que o usuário insira e retire elementos em qualquer posição
 *  desejada.
 *
 * @tparam  T   Tipo de dado do template.
*/
template<typename T>
class LinkedQueue: private LinkedList<T> {
 public:
 /**
  * @brief Construtor padrão.
  * 
  * Cria um objeto da classe LinkedQueue.
 */
    LinkedQueue(): LinkedList<T>(), tail{nullptr}
    {}

 /**
  * @brief Destrutor da classe LinkedQueue.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
  *
  * @see LinkedQueue()
 */
    ~LinkedQueue() {
        delete tail;
    }

 /**
  * @brief Limpa os dados da Fila.
  * 
  * Limpa a Fila e desaloca memória de cada elemento.
 */
    void clear() {
        LinkedList<T>::clear();
        tail = nullptr;
    }

 /**
  * @brief Insere novo elemento no final da Fila.
  * 
  * @param  data    dado do tipo T a ser inserido.
  *
  * @see void push_front(const T& data);
 */
    void enqueue(const T& data) {
        Node* novo{new Node(data, nullptr)};
        if (empty()) {
            head = novo;
            tail = novo;
        } else {
            tail->next(novo);
            tail = novo;
        }
        size_++;
    }

 /**
  * @brief Retira o elemento da posição definida.
  * 
  * Retira e retorna o elemento da posição dada por index
  * e realoca todos os outros elementos uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Fila esteja vazia
  * 			ou a posição seja inválida.
  *
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return Elemento que estava na posição index.
 */
    T dequeue() {
        return LinkedList<T>::pop_front();
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
    T& front() const {
        return LinkedList<T>::at(0);
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
    T& back() const {
        return LinkedList<T>::at(size()-1);
    }

 /**
  * Verifica se a Fila está vazia.
  * 
  * @return True se a Fila estiver vazia, False caso contrário.
 */
    bool empty() const {
        return LinkedList<T>::empty();
    }

 /**
  * Verifica o tamanho atual da Fila.
  * 
  * @return Inteiro com o número de elementos da Fila.
 */
    std::size_t size() const {
        return LinkedList<T>::size();
    }

 private:
    Node* tail;
};

}  // namespace structures

#endif
