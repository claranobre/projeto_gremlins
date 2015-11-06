#ifndef T_H
#define T_H

#include "lista.h"
using namespace std;

/**
 * \class 
 * \brief Classe que verifica o arquivo
 */

class T
{
public:
    /**
     * Construtor que inicia as variaveis Tag, tamanho e cluster
     * @param Tag do arquivo
     * @param tamanho do arquivo
     * @param cluster array com os clusters
     */
    T(string Tag, int tamanho, int cluster[]);

    /**
     * Destrutor padrão
     */
    ~T();

    /**
     * Retorna a Tag do arquivo
     * @return Tag
     */
    string getTag();

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
    string Tag; /**< Tag do arquivo */
    int tamanho; /**< Tamanho do arquivo */
    int *cluster; /**< Array que guarda os setores onde os dados deste arquivo estão */
};

#endif // T_H