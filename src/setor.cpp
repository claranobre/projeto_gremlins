#include "setor.h"

Setor::Setor(int id){
    this->id = id;
}

Setor::Setor(int id, int inicio, int fim){
    this->inicio = inicio;
    this->fim = fim;
    this->id = id;
}

Setor::~Setor()
{

}

int Setor::getInicio()
{
    return inicio;
}

int Setor::getFim()
{
    return fim;
}

int Setor::getId()
{
    return id;
}
