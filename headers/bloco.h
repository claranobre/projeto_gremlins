#ifndef BLOCO_H
#define BLOCO_H

#include "lista.h"

/**
 * \class Bloco
 * \brief Classe que simula uma memória separada por Blocos
 */
class Bloco
{
private:
    int id; /**< id do Bloco */
    int inicio;/**< inicio do Bloco */
    int fim; /**< fim do Bloco */

public:
    /**
     * Construtor
     * @param id
     */
    Bloco(int id);

    /**
     * Sobrecarda de construtor
     * @param id
     * @param inicio
     * @param fim
     */
    Bloco(int id, int inicio, int fim);

    /**
     * Destrutor padrão
     */
    ~Bloco();

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

#endif // BLOCO_H
