// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "linked_list.h"

namespace structures {

/**
 *  Estrutura de dados do tipo Pilha Encadeada.
 *
 *  Organiza os elementos em uma Pilha que pode ser ordenada ou não,
 *  permitindo que o usuário insira e retire elementos em qualquer posição
 *  desejada.
 *
 * @tparam  T   Tipo de dado do template.
*/
template<typename T>
class LinkedStack {
 public:
 /**
  * @brief Construtor padrão.
  * 
  * Cria um objeto da classe LinkedStack.
 */
    LinkedStack(): linkedList_{}
    {}

 /**
  * @brief Destrutor da classe LinkedStack.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
  *
  * @see LinkedStack()
 */
    ~LinkedStack() {}

 /**
  * @brief Limpa os dados da Pilha.
  * 
  * Limpa a Pilha e desaloca memória de cada elemento.
 */
    void clear() {
        linkedList_.clear();
    }

 /**
  * @brief Insere novo elemento no topo da Pilha.
  * 
  * @param  data    dado do tipo T a ser inserido.
 */
    void push(const T& data) {
        linkedList_.push_front(data);
    }

 /**
  * @brief Retira o elemento do topo da Pilha.
  * 
  * @throws "std::out_of_range" caso a Pilha esteja vazia
  *
  * @return Elemento que estava no topo da pilha.
 */
    T pop() {
        return linkedList_.pop_front();
    }

 /**
  * Olha o elemento no topo da pilha, sem retirá-lo.
  * 
  * @throws "std::out_of_range" caso a pilha esteja vazia.
  *
  * @return Elemento que está no topo da pilha.
 */
    T& top() const {
        return linkedList_.at(0);
    }

 /**
  * Verifica se a Pilha está vazia.
  * 
  * @return True se a Pilha estiver vazia, False caso contrário.
 */
    bool empty() const {
        return linkedList_.empty();
    }

 /**
  * Verifica o tamanho atual da Pilha.
  * 
  * @return Inteiro com o número de elementos da Pilha.
 */
    std::size_t size() const {
        return linkedList_.size();
    }

 private:
    LinkedList<T> linkedList_;
};

}  // namespace structures

#endif
