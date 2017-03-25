// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

/**
 *	Estrutura de dados do tipo Lista.
 *
 *	Organiza os elementos no padrão FIFO (First In First Out),
 *	onde o primeiro elemento a ser inserido é o primeiro a ser retirado.
 *	Conforme a definição geralmente conhecida de "Lista".
 *
 * @tparam	T	Tipo de dado do template.
*/
template<typename T>
class ArrayList {
 public:
    ArrayList();
    explict ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

 /**
  * Construtor padrão.
  * 
  * Cria um objeto da classe ArrayList com tamanho máximo padrão (DEFAULT_SIZE).
  *
  * @see ArrayList(std::size_t max)
 */
    template<typename T>
    ArrayList<T>::ArrayList() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        size_ = 0u;
    }

 /**
  * Construtor de Lista com tamanho definido.
  * 
  * Cria um objeto da classe ArrayList com tamanho parametrizado.
  *
  * @param  max inteiro positivo que representa o tamanho máximo da Lista.
  *
  * @see ArrayList()
 */
    ArrayList<T>::ArrayList(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        size_ = 0u;
    }

 /**
  * Destrutor da classe ArrayList.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
 */
    ArrayList<T>::~ArrayList() {
        delete [] contents;
    }

 /**
  * Insere novo elemento no final da Lista.
  * 
  * @throws "std::out_of_range" caso a Lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    void ArrayList<T>::push_back(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista cheia");
        } else {
            contents[size_] = data;
            size_++;
        }
    }

 /**
  * Insere novo elemento no início da Lista.
  * 
  * @throws "std::out_of_range" caso a Lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    void ArrayList<T>::push_front(const T& data) {
        insert(data, 0);
    }
 
 /**
  * Insere novo elemento em posição definida pelo usuário.
  * 
  * @throws "std::out_of_range" caso a Lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    void ArrayList<T>::insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("Lista cheia");
        } else {
            if (index > size_ || index < 0) {
                throw std::out_of_range("Posição inválida")
            }
            for (auto i = size_; i > index; --i) {
                contents[i] = contents[i-1];
            }
            contents[index] = data;
            size_++;
        }
    }

 /**
  * Insere novo elemento em posição definida pelo usuário.
  * 
  * @throws "std::out_of_range" caso a Lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    void ArrayList<T>::insert_sorted(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista cheia");
        } else {
            auto index = 0u;
            while (index < size_ && data > contents[index]) {
                index++;
            }
            insert(data, index);
        }
    }

 /**
  * Retira o primeiro elemento do início da Lista.
  * 
  * Retira o primeiro elemento e realoca todos os outros elementos
  * uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na primeira posição da Lista.
 */
    T ArrayList<T>::pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        } else {
            if (index >= size_ || index < 0) {
                throw std::out_of_range("Posição inválida")
            }
            T requested = contents[index];
            for (auto i = index; i < (size_-1); ++i) {
                contents[i] = contents[i+1];
            }
            size_--;
            return requested;
        }
    }

 /**
  * Retira o primeiro elemento do início da Lista.
  * 
  * Retira o primeiro elemento e realoca todos os outros elementos
  * uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na primeira posição da Lista.
 */
    T ArrayList<T>::pop_back() {
        return pop(size_-1);
    }

 /**
  * Retira o primeiro elemento do início da Lista.
  * 
  * Retira o primeiro elemento e realoca todos os outros elementos
  * uma posição a frente.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na primeira posição da Lista.
 */
    T ArrayList<T>::pop_front() {
        return pop(0);
    }

 /**
  * Olha o elemento no final da Lista, sem retirá-lo.
  * 
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que está no final da Lista.
 */
    T& back() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        } else {
            return (contents[size_-1]);
        }
    }

 /**
  * Limpa os dados da Lista.
  * 
 */
    void clear() {
        size_ = 0u;
    }

 /**
  * Verifica o tamanho atual da Lista.
  * 
  * @return Inteiro com o número de elementos da Lista.
 */
    std::size_t size() {
        return size_;
    }

 /**
  * Verifica o tamanho máximo da Lista.
  * 
  * @return Inteiro com o tamanho máximo da Lista.
 */
    std::size_t max_size() {
        return max_size_;
    }

 /**
  * Verifica se a Lista está vazia.
  * 
  * @return True se a Lista estiver vazia, False caso contrário.
 */
    bool empty() {
        return (size_ == 0);
    }

 /**
  * Verifica se a Lista está cheia.
  * 
  * @return True se a Lista estiver cheia, False caso contrário.
 */
    bool ArrayList<T>::full() {
        return (size_ == max_size_);
    }


}  // namespace structures

#endif
