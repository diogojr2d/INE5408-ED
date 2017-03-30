// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

/**
 *	Estrutura de dados do tipo Lista.
 *
 *	Organiza os elementos em uma lista que pode ser ordenada ou não,
 *	permitindo que o usuário insira e retire elementos em qualquer posição
 *  desejada.
 *
 * @tparam	T	Tipo de dado do template.
*/
template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
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
    template<typename T>
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
    template<typename T>
    ArrayList<T>::~ArrayList() {
        delete [] contents;
    }

 /**
  * Insere novo elemento no final da Lista.
  * 
  * @throws "std::out_of_range" caso a lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    template<typename T>
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
  * @throws "std::out_of_range" caso a lista esteja cheia.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    template<typename T>
    void ArrayList<T>::push_front(const T& data) {
        insert(data, 0);
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
    void ArrayList<T>::insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("Lista cheia");
        } else {
            if (index > size_ || index < 0) {
                throw std::out_of_range("Posição inválida");
            }
            for (auto i = size_; i > index; --i) {
                contents[i] = contents[i-1];
            }
            contents[index] = data;
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
    T ArrayList<T>::pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        } else {
            if (index >= size_ || index < 0) {
                throw std::out_of_range("Posição inválida");
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
  * Retira o último elemento da Lista.
  * 
  * Retira e retorna o último elemento.
  *
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @return Elemento que estava na última posição da Lista.
 */
    template<typename T>
    T ArrayList<T>::pop_back() {
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
    T ArrayList<T>::pop_front() {
        return pop(0);
    }

 /**
  * Remove o elemento definido pelo dado passado como argumento.
  * 
  * @throws "std::out_of_range" caso a Lista esteja vazia.
  *
  * @param  data    dado do tipo T a ser removido.
 */
    template<typename T>
    void ArrayList<T>::remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        } else {
            pop(find(data));
        }
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
    std::size_t ArrayList<T>::find(const T& data) const {
        auto index = 0u;
        while ( (index < size_) && (data != contents[index]) ) {
            index++;
        }
        return index;
    }

 /**
  * Limpa os dados da Lista.
  * 
 */
    template<typename T>
    void ArrayList<T>::clear() {
        size_ = 0u;
    }

 /**
  * Verifica o tamanho atual da Lista.
  * 
  * @return Inteiro com o número de elementos da Lista.
 */
    template<typename T>
    std::size_t ArrayList<T>::size() const {
        return size_;
    }

 /**
  * Verifica o tamanho máximo da Lista.
  * 
  * @return Inteiro com o tamanho máximo da Lista.
 */
    template<typename T>
    std::size_t ArrayList<T>::max_size() const {
        return max_size_;
    }

 /**
  * Verifica se a Lista está vazia.
  * 
  * @return True se a Lista estiver vazia, False caso contrário.
 */
    template<typename T>
    bool ArrayList<T>::empty() const {
        return (size_ == 0);
    }

 /**
  * Verifica se a Lista está cheia.
  * 
  * @return True se a Lista estiver cheia, False caso contrário.
 */
    template<typename T>
    bool ArrayList<T>::full() const {
        return (size_ == max_size_);
    }

 /**
  * Verifica se a Lista contém o dado passado (data).
  * 
  * @param  data    dado do tipo T a ser procurado.
  * 
  * @return True se a lista contém o dado, False caso contrário.
 */
    template<typename T>
    bool ArrayList<T>::contains(const T& data) const {
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
    T& ArrayList<T>::at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else {
            return contents[index];
        }
    }

 /**
  * Sobrescreve o operador [], retornando o dado da posição recebida.
  * 
  * Sobrescreve o operador [], para que a ArrayList funcione de maneira
  * similar a uma array, onde os dados da lista podem ser acessados
  * pelo seu índice na forma ArrayList[index].
  * 
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return dado do tipo T da posição indicada.
 */
    template<typename T>
    T& ArrayList<T>::operator[](std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else {
            return contents[index];
        }
    }

 /**
  * Versão const do at().
  * 
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return dado do tipo T da posição indicada.
  * 
  * @see ArrayList<T>::at(std::size_t index)
 */
    template<typename T>
    const T& ArrayList<T>::at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else {
            return contents[index];
        }
    }

 /**
  * Versão const do operador [].
  * 
  * @param  index   (inteiro) indica a posição do dado.
  *
  * @return dado do tipo T da posição indicada.
  * 
  * @see ArrayList<T>::operator[](std::size_t index)
 */
    template<typename T>
    const T& ArrayList<T>::operator[](std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Posição inválida");
        } else {
            return contents[index];
        }
    }

}  // namespace structures

#endif
