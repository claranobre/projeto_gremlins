#include "T.h"

T::T(string tag, int tamanho, int cluster[])
{
    this->tag = tag;
    this->tamanho = tamanho;
    this->cluster = new int[tamanho];

    for(int i = 0; i<tamanho; i++){
        this->cluster[i] = cluster[i];
    }

    //(p.Allocate (bytes + sizeof (Tag)));
}

T::~T()
{
    delete cluster;
}

string T::getTag()
{
    tag->pool = &p;
    //Tag * const tag = reinterpretcast <Tag *> (arg) - 1 U;
    return tag;

    if(nullptr != tag->pool) // Memory block belongs to a particular GM .
        tag->pool->Release (tag);
    else
        std :: free (tag); // Memory block belongs to the operational system .
}

int T::getTamanho()
{
    return tamanho;
}

int T::getCluster(int id)
{
    return cluster[id];
}
void T::setCluster(int value, int id)
{
    cluster[id] = value;
}