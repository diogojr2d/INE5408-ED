// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

/**
 *  Estrutura de dados do tipo Lista Encadeada.
 *
 *  Organiza os elementos em uma lista que pode ser ordenada ou não,
 *  permitindo que o usuário insira e retire elementos em qualquer posição
 *  desejada.
 *
 * @tparam  T   Tipo de dado do template.
*/
template<typename T>
class LinkedList {
 public:
    LinkedList();
    ~LinkedList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    T& at(std::size_t index);

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

 /**
  * Construtor padrão.
  * 
  * Cria um objeto da classe LinkedList com tamanho máximo padrão (DEFAULT_SIZE).
  *
  * @see LinkedList(std::size_t max)
 */
    template<typename T>
    LinkedList<T>::LinkedList():
        head{nullptr},
        size_{0u}
    {}

 /**
  * Destrutor da classe LinkedList.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
 */
    template<typename T>
    LinkedList<T>::~LinkedList() {
        clear();
    }

 /**
  * Insere novo elemento no final da Lista.
  * 
  * @throws "std::out_of_range" caso a lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    template<typename T>
    void LinkedList<T>::push_back(const T& data) {
        Node* last = end();
        Node* novo{new Node(data)};
        last->next(novo);
        novo->next(nullptr);
        size_++;
    }

 /**
  * Insere novo elemento no início da Lista.
  * 
  * @throws "std::out_of_range" caso a lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    template<typename T>
    void LinkedList<T>::push_front(const T& data) {
        Node* novo{new Node(data)};
        if (novo == nullptr) {
            throw std::out_of_range("Lista cheia");
        }
        novo->next(head);
        head = novo;
        size_++;
    }

 /**
  * Insere novo elemento em posição definida pelo usuário.
  * 
  * Move uma posição para trás todos os elementos que estiverem
  * após a posição definida, e insere o novo elemento nesta
  * posição que foi liberada.
  * 
  * @throws "std::out_of_range" caso a lista esteja cheia
  *             ou a posição seja inválida.
  *
  * @param  data    dado do tipo T a ser inserido.
  * @param  index   (inteiro) indica a posição a ser inserido o dado.
 */
    template<typename T>
    void LinkedList<T>::insert(const T& data, std::size_t index) {
        if (index > size()) {
            throw std::out_of_range("Posição inválida");
        } else if (index == 0) {
            push_front(data);
        } else {
            Node* novo{new Node(data)};
            if (novo == nullptr) {
                throw std::out_of_range("Lista cheia");
            }
            Node* anterior = head;
            for (auto i = 0u; i < index-1; ++i) {
                anterior = anterior->next();
            }
            novo->next(anterior->next());
            anterior->next(novo);
            size_++;
        }
    }

 /**
  * Insere novo elemento de acordo com a ordem natural dos elementos
  * da lista (ordenada).
  *
  * @throws "std::out_of_range" caso a Lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    template<typename T>
    void LinkedList<T>::insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* anterior = head;
            auto index = 0u;
            while (anterior->next() != nullptr && data > anterior->data()) {
                index++;
                anterior = anterior->next();
            }
            if (data > anterior->data()) {
                insert(data, index+1);
            } else {
                insert(data, index);
            }
        }
    }

 /**
  * Retira o elemento da posição definida por index.
  * 
  * Retira e retorna o elemento da posição dada por index
  * e realoca todos os outros elementos uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return Elemento que estava na posição index.
 */
    template<typename T>
    T LinkedList<T>::pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else if (index == 0) {
            return pop_front();
        } else {
            Node* anterior = head;
            for (auto i = 0u; i < index-1; ++i) {
                anterior = anterior->next();
            }
            Node* atual = anterior->next();
            T requested = atual->data();
            anterior->next(atual->next());
            delete atual;
            size_--;
            return requested;
        }
    }

 /**
  * Retira o último elemento da Lista.
  * 
  * Retira e retorna o último elemento.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na última posição da Lista.
 */
    template<typename T>
    T LinkedList<T>::pop_back() {
        return pop(size_-1);
    }

 /**
  * Retira o primeiro elemento da Lista.
  * 
  * Retira o primeiro elemento e realoca todos os outros elementos
  * uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na primeira posição da Lista.
 */
    template<typename T>
    T LinkedList<T>::pop_front() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        Node* atual = head;
        head = head->next();
        T requested = atual->data();
        delete atual;
        size_--;
        return requested;
    }

 /**
  * Remove o elemento definido pelo dado passado como argumento.
  * 
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @param  data    dado do tipo T a ser removido.
 */
    template<typename T>
    void LinkedList<T>::remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        pop(find(data));
    }

 /**
  * Procura e retorna a posição do elemento (data) na lista.
  * 
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @param  data    dado do tipo T a ser procurado.
  *
  * @return inteiro com a posição do dado.
 */
    template<typename T>
    std::size_t LinkedList<T>::find(const T& data) const {
        Node* anterior = head;
        auto index = 0u;
        while ( (index < size_) && (data != anterior->data()) ) {
            index++;
            anterior = anterior->next();
        }
        return index;
    }

 /**
  * Limpa os dados da Lista.
  * 
 */
    template<typename T>
    void LinkedList<T>::clear() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        Node* anterior = nullptr;
        Node* atual = head;
        while (atual != nullptr) {
            anterior = atual;
            atual = atual->next();
            delete anterior;
        }
        head = nullptr;
        size_ = 0u;
    }

 /**
  * Verifica o tamanho atual da Lista.
  * 
  * @return Inteiro com o número de elementos da Lista.
 */
    template<typename T>
    std::size_t LinkedList<T>::size() const {
        return size_;
    }

 /**
  * Verifica se a Lista está vazia.
  * 
  * @return True se a Lista estiver vazia, False caso contrário.
 */
    template<typename T>
    bool LinkedList<T>::empty() const {
        return (size_ == 0);
    }

 /**
  * Verifica se a Lista contém o dado passado (data).
  * 
  * @param  data    dado do tipo T a ser procurado.
  * 
  * @return True se a lista contém o dado, False caso contrário.
 */
    template<typename T>
    bool LinkedList<T>::contains(const T& data) const {
        return (find(data) >= 0 && find(data) < size_);
    }

 /**
  * Retorna o dado da posição recebida.
  * 
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return dado do tipo T da posição.
 */
    template<typename T>
    T& LinkedList<T>::at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else if (index == 0) {
            return head->data();
        } else {
            Node* atual = head;
            for (auto i = 0u; i < index; ++i) {
                atual = atual->next();
            }
            return atual->data();
        }
    }

}  // namespace structures

#endif
