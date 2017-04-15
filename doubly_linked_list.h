// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_DOUBLY_LIST_H
#define STRUCTURES_DOUBLY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

/**
 *  Estrutura de dados do tipo Lista Duplamente Encadeada.
 *
 *  Organiza os elementos em uma lista que pode ser ordenada ou não,
 *  permitindo que o usuário insira e retire elementos em qualquer posição
 *  desejada.
 *
 * @tparam  T   Tipo de dado do template.
*/
template<typename T>
class DoublyLinkedList {
 public:
 /**
  * @brief Construtor padrão.
  * 
  * Cria um objeto da classe DoublyLinkedList.
 */
    DoublyLinkedList();

 /**
  * @brief Destrutor da classe DoublyLinkedList.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
  *
  * @see DoublyLinkedList()
 */
    ~DoublyLinkedList();

 /**
  * @brief Limpa os dados da Lista.
  * 
  * Limpa a lista e desaloca memória de cada elemento.
 */
    void clear();

 /**
  * @brief Insere novo elemento no final da Lista.
  * 
  * @param  data    dado do tipo T a ser inserido.
  *
  * @see void push_front(const T& data);
 */
    void push_back(const T& data);
 /**
  * @brief Insere novo elemento no início da Lista.
  * 
  * @param  data    dado do tipo T a ser inserido.
  *
  * @see void push_back(const T& data);
 */
    void push_front(const T& data);
 /**
  * @brief Insere novo elemento em posição definida pelo usuário.
  * 
  * Cria novo elemento com o dado passado, e o insere na posição definida,
  * "empurrando" uma posição para trás todos os elementos após ele
  * (inclusive o que estava na posição).
  *
  * @throws "std::out_of_range" caso a lista esteja cheia
  *             ou a posição seja inválida.
  *
  * @param  data    dado do tipo T a ser inserido.
  * @param  index   (inteiro) indica a posição a ser inserido o dado.
  *
  * @see void insert_sorted(const T& data);
 */
    void insert(const T& data, std::size_t index);
 /**
  * @brief Insere elemento em lista de maneira ordenada.
  *
  * Considerando uma lista ordenada, por exemplo, inteiros em ordem crescente,
  * insere novo elemento de acordo com a ordem natural dos elementos.
  *
  * @param  data    dado do tipo T a ser inserido.
  *
  * @see void insert(const T& data, std::size_t index);
 */
    void insert_sorted(const T& data);
 /**
  * @brief Retira o elemento da posição definida.
  * 
  * Retira e retorna o elemento da posição dada por index
  * e realoca todos os outros elementos uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia
  * 			ou a posição seja inválida.
  *
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return Elemento que estava na posição index.
 */
    T pop(std::size_t index);
 /**
  * @brief Retira o último elemento da Lista.
  * 
  * Retira e retorna o último elemento da Lista.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na última posição da Lista.
 */
    T pop_back();
 /**
  * @brief Retira o primeiro elemento da Lista.
  * 
  * Retira o primeiro elemento e realoca todos os outros elementos
  * uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na primeira posição da Lista.
 */
    T pop_front();
 /**
  * Remove o elemento definido pelo dado passado como argumento.
  * 
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @param  data    dado do tipo T a ser removido.
 */
    void remove(const T& data);
 /**
  * Verifica se a Lista está vazia.
  * 
  * @return True se a Lista estiver vazia, False caso contrário.
 */
    bool empty() const;
 /**
  * Verifica se a Lista contém o dado passado (data).
  * 
  * @param  data    dado do tipo T a ser procurado.
  * 
  * @return True se a lista contém o dado, False caso contrário.
 */
    bool contains(const T& data) const;
 /**
  * Procura e retorna a posição do elemento (data) na lista.
  * 
  * @param  data    dado do tipo T a ser procurado.
  *
  * @return inteiro com a posição do dado.
 */
    std::size_t find(const T& data) const;
 /**
  * Verifica o tamanho atual da Lista.
  * 
  * @return Inteiro com o número de elementos da Lista.
 */
    std::size_t size() const;
 /**
  * Retorna o dado da posição recebida.
  * 
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return dado do tipo T da posição.
 */
    T& at(std::size_t index);
/**
  * Retorna o dado da posição recebida.
  *
  * Versão const de at().
  * 
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return dado do tipo T da posição.
 */
    T& at(std::size_t index) const;

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data},
            prev_{nullptr},
            next_{nullptr}
        {}

        Node(const T& data, Node* next):
            data_{data},
            prev_{nullptr},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* prev() {  // getter: anterior
        	return prev_;
        }

        const Node* prev() const {  // getter const: anterior
        	return prev_;
        }

        void prev(Node* node) {  // setter: anterior
        	prev_ = node;
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
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList():
        head{nullptr},
        tail{nullptr},
        size_{0u}
    {}

    template<typename T>
    DoublyLinkedList<T>::~DoublyLinkedList() {
        clear();
    }

    template<typename T>
    void DoublyLinkedList<T>::push_back(const T& data) {
        Node* novo{new Node(data)};
        if (empty()) {
    		head = novo;
    	} else {
        	tail->next(novo);
        	novo->prev(tail);
    	}
    	tail = novo;
        size_++;
    }

    template<typename T>
    void DoublyLinkedList<T>::push_front(const T& data) {
        Node* novo{new Node(data, nullptr, head)};
        if (empty()) {
        	tail = novo;
        } else {
        	head->prev(novo);
        }
        head = novo;
        size_++;
    }

    template<typename T>
    void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
        if (index > size()) {
            throw std::out_of_range("Posição inválida");
        } else if (empty() || index == 0) {
            push_front(data);
        } else if (index == size()) {
        	push_back(data);
        } else {
            Node* novo{new Node(data)};
            Node* atual = head;
            for (auto i = 0u; i < index; ++i) {
                atual = atual->next();
            }
            novo->next(atual);
            novo->prev(atual->prev());
            novo->prev()->next(novo);
            atual->prev(novo);
            size_++;
        }
    }

    template<typename T>
    void DoublyLinkedList<T>::insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* atual = head;
            auto index = 0u;
            while (atual->next() != nullptr && data > atual->data()) {
                index++;
                atual = atual->next();
            }
            if (data > atual->data()) {
                insert(data, index+1);
            } else {
                insert(data, index);
            }
        }
    }

    template<typename T>
    T DoublyLinkedList<T>::pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else if (index == 0) {
            return pop_front();
        } else if (index == size()-1) {
        	return pop_back();
        } else {
            Node* atual = head;
            for (auto i = 0u; i < index; ++i) {
                atual = atual->next();
            }
            T requested = atual->data();
            atual->prev()->next(atual->next());
            atual->next()->prev(atual->prev());
            delete atual;
            size_--;
            return requested;
        }
    }

    template<typename T>
    T DoublyLinkedList<T>::pop_back() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        Node* atual = tail;
        if (size() == 1) {
        	tail = nullptr;
        	head = nullptr;
        } else {
        	tail = tail->prev();
        	tail->next(nullptr);
        }
        T requested = atual->data();
        delete atual;
        size_--;
        return requested;
    }

    template<typename T>
    T DoublyLinkedList<T>::pop_front() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        Node* atual = head;
        if (size() == 1) {
        	head = nullptr;
        	tail = nullptr;
        } else {
        	head = head->next();
        	head->prev(nullptr);
        }
        T requested = atual->data();
        delete atual;
        size_--;
        return requested;
    }

    template<typename T>
    void DoublyLinkedList<T>::remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (contains(data))
        	pop(find(data));
    }

    template<typename T>
    std::size_t DoublyLinkedList<T>::find(const T& data) const {
        Node* atual = head;
        auto index = 0u;
        while ( (index < size_) && (data != atual->data()) ) {
            index++;
            atual = atual->next();
        }
        return index;
    }

    template<typename T>
    void DoublyLinkedList<T>::clear() {
        Node* atual = head;
        while (atual != nullptr && atual->next() != nullptr) {
            atual = atual->next();
            delete atual->prev();
        }
        if (atual != nullptr) {
        	delete atual;
        }
        head = nullptr;
        tail = nullptr;
        size_ = 0u;
    }

    template<typename T>
    std::size_t DoublyLinkedList<T>::size() const {
        return size_;
    }

    template<typename T>
    bool DoublyLinkedList<T>::empty() const {
        return (size_ == 0);
    }

    template<typename T>
    bool DoublyLinkedList<T>::contains(const T& data) const {
        return (find(data) >= 0 && find(data) < size_);
    }

    template<typename T>
    T& DoublyLinkedList<T>::at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else if (index == 0) {
            return head->data();
		} else if (index == size()-1) {
        	return tail->data();
        } else {
            Node* atual = head;
            for (auto i = 0u; i < index; ++i) {
                atual = atual->next();
            }
            return atual->data();
        }
    }

    template<typename T>
    T& DoublyLinkedList<T>::at(std::size_t index) const {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else if (index == 0) {
            return head->data();
		} else if (index == size()-1) {
        	return tail->data();
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
