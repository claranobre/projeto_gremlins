#ifndef FILE_H
#define FILE_H

#include "lista.h"
using namespace std;

/**
 * \class File
 * \brief Classe que guarda os arquivos salvos
 */

class File
{
public:
    /**
     * Construtor que inicia as variaveis nome, tamanho e cluster
     * @param nome do arquivo
     * @param tamanho do arquivo
     * @param cluster array com os clusters
     */
    File(string nome, int tamanho, int cluster[]);

    /**
     * Destrutor padrão
     */
    ~File();

    /**
     * Retorna o nome do arquivo
     * @return nome
     */
    string getNome();

    /**
     * Retorna o tamanho do arquivo
     * @return tamanho
     */
    int getTamanho();

    /**
     * Retorna o valor do indice(id) do cluster
     * @param id do indice
     * @return cluster[id]
     */
    int getCluster(int id);

    /**
     * Insere um valor no cluster
     * @param value a ser inserido no cluster
     * @param id indice a ser inserido
     */
    void setCluster(int value, int id);

private:
    string nome; /**< Nome do arquivo */
    int tamanho; /**< Tamanho do arquivo */
    int *cluster; /**< Array que guarda os setores onde os dados deste arquivo estão */
};

#endif // FILE_H
