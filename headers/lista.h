#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <cstddef>

/**
* enum para o tipo de comportamento das listas
*/
enum BEHAVIOR {LISTASIMPLES, PILHA, FILA}; //0, 1, 2

/**
* \class Lista
*
* \brief Classe genérica de Lista encadeadas, pode se comportar como Lista simples, fila ou pilha.
*
*/
template <class type>
class Lista {
private:
    int tam = 0; /**< Armazena o tamanho atual da lista*/
    BEHAVIOR bhvr; /**< Armazena o comportamento da lista: lista simples, pilha ou fila. Não pode ser alterado*/

public:
    /**
    * Estrutura de um nó da lista
    */
    struct node{
        type val; /**< Armazena o valor do nó atual*/
        node* next = NULL; /**< Armazena o endereço de memória para o próximo nó. Por padrão é NULO*/
    };

    /**
    * Nó cabeça. Assim que a classe é criada um endereço de memória é dinamicamente
    * alocado pra ele, evitando que aponte para os endereços 0x0 e 0x1 vindos de lixo de memória.
    */
    node* head = new node;

    /**
    * Construtor padrão
    * Inicializa uma ListaSimples aponta o valor next de head para NULO
    */
    Lista();

    /**
    * Construtor
    * Inicializa uma Lista do tipo enviado por padrão.
    * Aponta o valor next de head para NULO
    * @param b tipo da lista a ser criada: simples, pilha ou fila
    */
    Lista(BEHAVIOR b);

    /**
    * Construtor de cópia
    * Faz cópia profunda da lista enviada por referência.
    * @param &l recebe, por referência, lista a ser copiada
    */
    Lista(const Lista &l);

    /**
    * Destrutor.
    * Desaloca todos os nós da lista. Caso a lista seja de ponteiros, NÃO desaloca os ponteiros.
    */
    ~Lista();

    /**
    * Sobrecarga do operador =
    * Faz cópia profunda da lista enviada por referência.
    * @param &l recebe, por referência, lista a ser copiada
    */
    Lista& operator=(const Lista &l);

    /**
    * Retorna o tamanho atual da lista
    */
    int Size();

    /**
    * Retorna, por referência valor da posição enviada
    * Funciona apenas para Listas com comportamento LISTASIMPLES, posições vão de 0 a tamanho - 1
    * \return Retorna se conseguiu recuperar o valor da posição.
    * @param pos Posição da onde será resgatado o valor
    * @param &get receberá, por referência, valor da posição desejada
    */
    bool GetElem(int pos, type &get) const;

    /**
    * Retorna, por referência próximo valor a ser retirado da pilha ou fila
    * Funciona apenas para Listas com comportamento PILHA ou FILA
    * \return Retorna se conseguiu recuperar o valor.
    * @param &get receberá, por referência, próximo valor a ser retirado da pilha ou fila
    */
    bool GetElem(type &get) const;

    /**
    * Procura por um valor na lista
    * \return Retorna primeira instação do valor na lista. -1 caso não exista
    * @param val contém valor a ser pesquisado
    */
    int Search(type val);

    /**
    * Insere elemento na posição da lista.
    * Funciona apenas para Listas com comportamento LISTASIMPLES, posições vão de 0 a tamanho - 1
    * \return Retorna se conseguiu inserir valor na posição
    * @param pos Posição onde será inserido o valor
    * @param val valor a ser inserido na posição desejada
    */
    bool Insert(int pos, type val);

    /**
    * Insere elemento na lista.
    * Funciona apenas para Listas com comportamento FILA ou PILHA
    * \return Retorna se conseguiu inserir valor
    * @param val valor a ser inserido na fila ou pilha
    */
    bool Insert(type val);

    /**
    * Remove valor de uma posição da lista
    * Só funciona para listas simples. Posições vão de 0 a tamanho - 1
    * \return Retorna se removeu o elemento da posição enviada
    * @param pos posição da qual elemento será removido
    */
    bool Remove(unsigned int pos);

    /**
    * Remove todos os elementos, limpa a lista
    * \return Retorna se removeu tudo
    */
    bool RemoveAll();

    /**
    * Remove valor de uma posição da lista, retornando-o por referência
    * Só funciona para listas simples. Posições vão de 0 a tamanho - 1
    * \return Retorna se removeu o elemento da posição enviada
    * @param pos posição da qual elemento será removido
    * @param &get recebe, por referência, valor removido da lista
    */
    bool Remove(int pos, type &get);

    /**
    * Remove valor de uma posição da lista, retornando-o por referência
    * Só funciona para filas ou pilhas.
    * \return Retorna se removeu o elemento
    * @param &get recebe, por referência, valor removido da fila/pilha
    */
    bool Remove(type &get);

    /**
    * Imprime conteúdo da lista/fila/pilha
    * @param separator caractere separador entre os valores, por padrão é o espaço
    */
    void Print(char separator = ' ');

    /**
    * Retorna comportamento da lista
    * \return Tipo de comportamento da lista
    */
    BEHAVIOR GetBehavior() const;
};
    #include "lista.inl"
#endif
