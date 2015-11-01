#ifndef Memoria_H
#define Memoria_H
#include "file.h"
#include "setor.h"
#include "lista.h"
#include <QMainWindow>

/**
 * \class Memoria
 * \brief Classe que controla todos as funções do Memoria
 */
class Memoria {

private:
    int numSetores;/**< Guarda a quantidade de setores  */
    int tamSetores;/**< Guarda o tamanho dos setores */
    int tamanho;/**< Tamanho do Memoria */
    int livre;/**< Quantidade de setores livres */
    char *disk;/** array de char que guarda os valores do arquivo */

    Lista<File*> info;/**< Lista com os arquivos */
    Lista<Setor*> pool;/**< Lista de setores livres */

public:

    /**
     * Construtor do Memoria
     * @param quantSetores Quantidade de setores
     * @param tamSetores Tamanho dos setores
     * @param tamMemoria Tamanho total do Memoria
     */
    Memoria(int quantSetores, int tamSetores, int tamMemoria);

    /**
     * Destrutor padrão
     */
    ~Memoria();

    /**
    * Função para salvar as informações do arquivo
    * @param strValue Valor da string a ser salva no Memoria
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
     * Busca um arquivo e retorna os seus dados
     * @param Nome que será procurado
     * @return html que será inserido no widget
     */
    QString Buscar(string nome);

    /**
     * Lista os arquivos salvos
     * @return html para ser inserido no widget
     */
    QString Listar();

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
     * Atualiza o pool após alguma modificação no Memoria (salvar, excluir, formatar, desfragmentar)
     */
    void AtualizarPool();

    /**
     * Formata o Memoria apagando todo o seu conteúdo como um todo, sem a possibilidade de recuperação de nenhum dado
     * @return 1 se o Memoria foi formatado corretamente ou 0 caso tenha erro
     */
    int Formatar();

    /**
     * Desfragmenta o Memoria, deixando os arquivos sem clustes contiguos
     * @return 1 se formatou, 0 se teve erro
     */
    int Desfragmentar();

    /**
     * Verifica se o Memoria está fragmentado
     * @return 1 se tiver fragmentado, 0 se não tiver
     */
    int isFragmented(int Memoria[]);

    /**
    * Função para verificar se o Memoria tem espaço para receber o dado
    * @param tam
    * @return retorna verdadeiro ou falso
    */
    bool isFree(int tam);

    /**
      *Função get para captar a quantidade de setores indicada pelo usuário
      *@param quantSetores
      *@return quantidade de setores existentes no Memoria
    */
    int getNumSetores();

    /**
     * Função para captar o tamanho do Memoria
     * @return tamanho do Memoria
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
    char getDisk(int id);

    char* itoa(int value, char* result, int base);
};

#endif // Memoria_H
