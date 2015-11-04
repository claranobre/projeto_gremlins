#ifndef Memoria_H
#define Memoria_H
#include "file.h"
#include "setor.h"
#include "lista.h"

/**
 * \class Memoria
 * \brief Classe que controla todos as funções da Memoria
 */
class Memoria {

private:
    int numSetores;/**< Guarda a quantidade de setores  */
    int tamSetores;/**< Guarda o tamanho dos setores */
    int tamanho;/**< Tamanho da Memoria */
    int livre;/**< Quantidade de setores livres */
    char *disk;/** array de char que guarda os valores do arquivo */

    Lista<File*> info;/**< Lista com os arquivos */
    Lista<Setor*> pool;/**< Lista de setores livres */

public:

    /**
     * Construtor da Memoria
     * @param quantSetores Quantidade de setores
     * @param tamSetores Tamanho dos setores
     * @param tamMemoria Tamanho total da Memoria
     */
    Memoria(int quantSetores, int tamSetores, int tamMemoria);

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
      *Função get para captar a quantidade de setores indicada pelo usuário
      *@param quantSetores
      *@return quantidade de setores existentes na Memoria
    */
    int getNumSetores();

    /**
     * Função para captar o tamanho da Memoria
     * @return tamanho da Memoria
    */
    int getTamanho();

    /**
    * Função para captar o tamanho de cada setor
    * @return Tamanho total dos setores
    */
    int getTamSetores();

    /**
     * Retorna o valor de um indice do vetor
     * @param id indice do vetor
     * @return disk[id]
     */
};

#endif // Memoria_H
