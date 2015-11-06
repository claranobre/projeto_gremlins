#include "bloco.h"

Bloco::Bloco(int id){
    this->id = id;
}

Bloco::Bloco(int id, int inicio, int fim){
    this->inicio = inicio;
    this->fim = fim;
    this->id = id;
}

Bloco::~Bloco()
{

}

int Bloco::getInicio()
{
    return inicio;
}

int Bloco::getFim()
{
    return fim;
}

int Bloco::getId()
{
    return id;
}
