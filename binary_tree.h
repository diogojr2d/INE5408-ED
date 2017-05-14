// Copyright 2017 <Diogo Junior de Souza>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include "array_list.h"

namespace structures {

/**
 *  @brief Estrutura de dados do tipo Árvore Binária de Busca.
 *
 *  Estrutura onde cada elemento é representado por um nó que pode
 *  possuir até dois filhos, um a esquerda e um a direita. Os filhos,
 *  por sua vez, podem possuir seus filhos, formando uma estrutura 
 *  em árvore, onde cada nível forma uma subárvore de maneira recursiva.
 *  Na Árvore Binária de Busca, todos os nós da subárvore esquerda possuem
 *  valor menor que o nó raiz, e todos os nós da subárvore direita possuem
 *  valor maior que o nó raiz.
 *
 * @tparam  T   Tipo de dado do template.
*/
template<typename T>
class BinaryTree {
 public:
 /**
  * @brief Destrutor da classe BinaryTree.
  * 
  * Deleta o objeto e desaloca memória dos elementos.
 */
    ~BinaryTree() {
    	size_ = 0u;
    }

 /**
  * @brief Insere novo elemento na árvore.
  * 
  * Cria novo elemento com o dado passado, e o insere na posição correta.
  *
  * @param  data    dado do tipo T a ser inserido.
 */
    void insert(const T& data) {
    	if (empty()) {
    		root = new Node{data};
    	} else {
    		root->insert(data);
    	}
    	size_++;
    }

 /**
  * Remove o elemento definido pelo dado passado como argumento.
  * 
  * @param  data    dado do tipo T a ser removido.
 */
    void remove(const T& data) {
    	bool b = false;
    	if (empty()) {
    		return;
    	} else {
    		b = root->remove(data);
    	}
    	if (b) {
    		size_--;
    	}
    }

 /**
  * Verifica se a Árvore está vazia.
  * 
  * @return True se a Árvore estiver vazia, False caso contrário.
 */
    bool empty() const {
    	return (size_ == 0);
    }

 /**
  * Verifica se a Árvore contém o dado passado (data).
  * 
  * @param  data    dado do tipo T a ser procurado.
  * 
  * @return True se a Árvore contém o dado, False caso contrário.
 */
    bool contains(const T& data) const {
    	if (empty()) {
    		return false;
    	} else {
    		return root->contains(data);
    	}
    }

 /**
  * Retorna o número de elementos na árvore.
  * 
  * @return inteiro com o número de elementos.
 */
    std::size_t size() const {
    	return size_;
    }

 /**
  * Organiza a árvore de maneira pré-ordenada, onde primeiro vem a raíz,
  * depois o nó da esquerda, e por último o nó da direita.
  * 
  * @return Lista de Vetor (ArrayList) com a árvore organizada.
 */
	ArrayList<T> pre_order() const {
		ArrayList<T> list{};
		if (!empty()) {
			root->pre_order(list);
		}
		return list;
	}

 /**
  * Organiza a árvore de maneira ordenada, onde primeiro vem o nó da esquerda,
  * depois a raiz, e por último o nó da direita.
  * 
  * @return Lista de Vetor (ArrayList) com a árvore organizada.
 */
	ArrayList<T> in_order() const {
		ArrayList<T> list{};
		if (!empty()) {
			root->in_order(list);
		}
		return list;
	}

 /**
  * Organiza a árvore de maneira pós-ordenada, onde primeiro vem o
  * nó da esquerda, depois o nó da direita, e por último a raiz.
  * 
  * @return Lista de Vetor (ArrayList) com a árvore organizada.
 */
	ArrayList<T> post_order() const {
		ArrayList<T> list{};
		if (!empty()) {
			root->post_order(list);
		}
		return list;
	}

 private:
    struct Node {  // Elemento
        explicit Node(const T& data):
            data_{data}
        {}

        void insert(const T& data) {
        	if (data < data_) {
        		if (left_ == nullptr) {
        			left_ = new Node{data};
        		} else {
        			left_->insert(data);
        		}
        	} else {
        		if (right_ == nullptr) {
        			right_ = new Node{data};
        		} else {
        			right_->insert(data);
        		}
        	}
        }

        bool remove(const T& data) {
        	if (data == data_) {
        		if (right_ != nullptr && left_ != nullptr) {
        			data_ = successor(right_)->data_;
        			return right_->remove(data_);
        		} else {
        			if (right_ != nullptr) {
        				data_ = right_->data_;
        				return right_->remove(data_);
        			} else {
        				if (left_ != nullptr) {
        					data_ = left_->data_;
        					return left_->remove(data_);
        				} else {
        					delete this;
        					return true;
        				}
        			}
        		}
        	} else {
        		if (data > data_ && right_ != nullptr) {
        			return right_->remove(data);
        		} else if (data < data_ && left_ != nullptr) {
        			return left_->remove(data);
        		}
        	}
        	return false;
        }

        Node* successor(Node* node) {
        	while (node->left_ != nullptr)
        		node = node->left_;
        	return node;
        }

        bool contains(const T& data) const {
        	if (data == data_) {
        		return true;
        	} else {
        		if (data < data_ && left_ != nullptr) {
        			return left_->contains(data);
        		} else if (data > data_ && right_ != nullptr) {
        			return right_->contains(data);
        		}
        		return false;
        	}
        }

        void pre_order(ArrayList<T>& v) const {
        	v.push_back(data_);
        	if (left_ != nullptr) {
        		left_->pre_order(v);
        	}
        	if (right_ != nullptr) {
        		right_->pre_order(v);
        	}
        }

        void in_order(ArrayList<T>& v) const {
        	if (left_ != nullptr) {
        		left_->in_order(v);
        	}
        	v.push_back(data_);
        	if (right_ != nullptr) {
        		right_->in_order(v);
        	}
        }

        void post_order(ArrayList<T>& v) const {
        	if (left_ != nullptr) {
        		left_->post_order(v);
        	}
        	if (right_ != nullptr) {
        		right_->post_order(v);
        	}
        	v.push_back(data_);
        }

        T data_;
        Node* left_{nullptr};
        Node* right_{nullptr};
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};
}  // namespace structures

#endif
