#ifndef SETOR_H
#define SETOR_H

#include "lista.h"

/**
 * \class Setor
 * \brief Classe que simula os Setores do HD
 */
class Setor
{
private:
    int id; /**< id do setor */
    int inicio;/**< inicio do setor */
    int fim; /**< fim do setor */

public:
    /**
     * Construtor
     * @param id
     */
    Setor(int id);

    /**
     * Sobrecarda de construtor
     * @param id
     * @param inicio
     * @param fim
     */
    Setor(int id, int inicio, int fim);

    /**
     * Destrutor padrão
     */
    ~Setor();

    /**
     * Retorna o valor do inicio
     * @return inicio
     */
    int getInicio();

    /**
     * Retorna o valor do fim
     * @return fim
     */
    int getFim();

    /**
     * Retorna o valor de id
     * @return id
     */
    int getId();
};

#endif // SETOR_H
