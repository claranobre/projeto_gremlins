#ifndef MEMORIA_H
#define MEMORIA_H
#include "file.h"
#include "bloco.h"
#include "lista.h"

/**
 * \class Memoria
 * \brief Classe que controla todos as funções da Memoria
 */
class Memoria {

private:
    int numBlocos;/**< Guarda a quantidade de Blocos  */
    int tamBlocos;/**< Guarda o tamanho dos Blocos */
    int tamanho;/**< Tamanho da Memoria */
    int livre;/**< Quantidade de Blocos livres */
    char *memory;/** array de char que guarda os valores do arquivo */

    Lista<File*> info;/**< Lista com os arquivos */
    Lista<Bloco*> pool;/**< Lista de Blocos livres */

public:

    /**
     * Construtor da Memoria
     * @param quantBlocos Quantidade de Blocos
     * @param tamBlocos Tamanho dos Blocos
     * @param tamMemoria Tamanho total da Memoria
     */
    Memoria(int quantBlocos, int tamBlocos, int tamMemoria);

    /**
     * Destrutor padrão
     */
    ~Memoria();

    /**
    * Função para salvar as informações do arquivo
    * @param strValue Valor da string a ser salva na Memoria
    * @param tamValue Tamanho da string
    * @param strNome Nome do arquivo
    * @return 1 se salvou, 0 se não salvou
    */
    int Salvar(const char *strValue, int tamValue, string strNome);

    /**
     * Exclui um arquivo
     * @param Nome do arquivo que será excluido
     * @return 1 se exclusão foi correta ou 0 caso não tenha excluido
     */
    int Excluir(string Nome);

    /**
     * Inicializa um vetor com todos os valores iguais
     * @param array que será inicializado
     * @param tamanho do array
     * @param valor que inicializará o array
     */
    void InicializarArray(int array[], int tamanho, int valor);

    /**
     * Inicializa um vetor com todos seus indices com valores zero
     * @param array que será inicializado
     * @param tamanho do array
     */
    void InicializarArray(char array[], int tamanho);

    /**
     * Atualiza o pool após alguma modificação na Memoria
     */
    void AtualizarPool();

    /**
     * Verifica se a Memoria está com espaços livres
     * @return 1 se tiver fragmentado, 0 se não tiver
     */
    int Free(int Memoria[]);

    /**
    * Função para verificar se a Memoria tem espaço para receber o dado
    * @param tam
    * @return retorna verdadeiro ou falso
    */
    bool isFree(int tam);

    /**
      *Função get para captar a quantidade de Blocos indicada pelo usuário
      *@param quantBlocos
      *@return quantidade de Blocos existentes na Memoria
    */
    int getNumBlocos();

    /**
     * Função para captar o tamanho da Memoria
     * @return tamanho da Memoria
    */
    int getTamanho();

    /**
    * Função para captar o tamanho de cada Bloco
    * @return Tamanho total dos Blocos
    */
    int getTamBlocos();

    /**
     * Retorna o valor de um indice do vetor
     * @param id indice do vetor
     * @return memory[id]
     */
};

#endif // MEMORIA_H
