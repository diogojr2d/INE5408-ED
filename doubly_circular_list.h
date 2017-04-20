// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_DOUBLY_CIRCULAR_H
#define STRUCTURES_DOUBLY_CIRCULAR_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

/**
 *  Estrutura de dados do tipo Lista Circular Duplamente Encadeada.
 *
 *  Organiza os elementos em uma lista que pode ser ordenada ou não,
 *  permitindo que o usuário insira e retire elementos em qualquer posição
 *  desejada.
 *
 * @tparam  T   Tipo de dado do template.
*/
template<typename T>
class DoublyCircularList {
 public:
 /**
  * @brief Construtor padrão.
  * 
  * Cria um objeto da classe DoublyCircularList.
 */
    DoublyCircularList();

 /**
  * @brief Destrutor da classe DoublyCircularList.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
  *
  * @see DoublyCircularList()
 */
    ~DoublyCircularList();

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
        Node() = default;

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
    std::size_t size_{0u};
};

    template<typename T>
    DoublyCircularList<T>::DoublyCircularList():
        head{new Node{}},
        size_{0u}
    {
        head->next(head);
        head->prev(head);
    }

    template<typename T>
    DoublyCircularList<T>::~DoublyCircularList() {
        clear();
        delete head;
    }

    template<typename T>
    void DoublyCircularList<T>::push_back(const T& data) {
        Node* novo{new Node(data)};
        if (empty()) {
            head->next(novo);
            novo->prev(head);
    	} else {
        	head->prev()->next(novo);
        	novo->prev(head->prev());
    	}
        novo->next(head);
        head->prev(novo);
        size_++;
    }

    template<typename T>
    void DoublyCircularList<T>::push_front(const T& data) {
        Node* novo{new Node(data, head, head->next())};
        if (empty()) {
        	head->prev(novo);
        } else {
        	head->next()->prev(novo);
        }
        head->next(novo);
        size_++;
    }

    template<typename T>
    void DoublyCircularList<T>::insert(const T& data, std::size_t index) {
        if (index > size()) {
            throw std::out_of_range("Posição inválida");
        } else if (empty() || index == 0) {
            push_front(data);
        } else if (index == size()) {
        	push_back(data);
        } else {
            Node* novo{new Node(data)};
            Node* atual = head->next();
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
    void DoublyCircularList<T>::insert_sorted(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            Node* atual = head->next();
            auto index = 0u;
            while (atual->next() != head && data > atual->data()) {
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
    T DoublyCircularList<T>::pop(std::size_t index) {
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
            Node* atual = head->next();
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
    T DoublyCircularList<T>::pop_back() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        Node* atual = head->prev();
        if (size() == 1) {
        	head->prev(head);
        	head->next(head);
        } else {
        	atual->prev()->next(head);
            head->prev(atual->prev());
        }
        T requested = atual->data();
        delete atual;
        size_--;
        return requested;
    }

    template<typename T>
    T DoublyCircularList<T>::pop_front() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        Node* atual = head->next();
        if (size() == 1) {
        	head->prev(head);
            head->next(head);
        } else {
        	head->next(atual->next());
        	atual->next()->prev(head);
        }
        T requested = atual->data();
        delete atual;
        size_--;
        return requested;
    }

    template<typename T>
    void DoublyCircularList<T>::remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (contains(data))
        	pop(find(data));
    }

    template<typename T>
    std::size_t DoublyCircularList<T>::find(const T& data) const {
        Node* atual = head->next();
        auto index = 0u;
        while ( (index < size_) && (data != atual->data()) ) {
            index++;
            atual = atual->next();
        }
        return index;
    }

    template<typename T>
    void DoublyCircularList<T>::clear() {
        Node* atual = head->next();
        while (atual->next() != head->next()) {
            atual = atual->next();
            delete atual->prev();
        }
        head->prev(head);
        head->next(head);
        size_ = 0u;
    }

    template<typename T>
    std::size_t DoublyCircularList<T>::size() const {
        return size_;
    }

    template<typename T>
    bool DoublyCircularList<T>::empty() const {
        return (size_ == 0);
    }

    template<typename T>
    bool DoublyCircularList<T>::contains(const T& data) const {
        return (find(data) >= 0 && find(data) < size_);
    }

    template<typename T>
    T& DoublyCircularList<T>::at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
		} else if (index == size()-1) {
        	return head->prev()->data();
        } else {
            Node* atual = head->next();
            for (auto i = 0u; i < index; ++i) {
                atual = atual->next();
            }
            return atual->data();
        }
    }

    template<typename T>
    T& DoublyCircularList<T>::at(std::size_t index) const {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else if (index == size()-1) {
            return head->prev()->data();
        } else {
            Node* atual = head->next();
            for (auto i = 0u; i < index; ++i) {
                atual = atual->next();
            }
            return atual->data();
        }
    }

}  // namespace structures

#endif
