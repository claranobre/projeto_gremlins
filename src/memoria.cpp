#include "memoria.h"
#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <math.h>

memoria::memoria(int quantBlocos, int tamBlocos, int tammemoria)
{
    this->numBlocos = quantBlocos;
    this->tamBlocos = tamBlocos;
    this->tamanho = tammemoria;
    this->livre = quantBlocos;

    /*
    class StoragePool{
    public:
        virtual ~StoragePool();
        virtual void* Allocate(size_t) = 0;
        virtual void Free(void *) = 0;
    };
    */

    // Inicializando o pool no intervalo [0, quantBlocos]
    Bloco *novo = new Bloco(0, 0, quantBlocos);
    pool.Insert(0, novo);

    this->Mem = new char[tammemoria];
    InicializarArray(Mem, tammemoria);
}

memoria::~memoria()
{
    info.~Lista();
    pool.~Lista();
    delete Mem;
}

int memoria::Salvar(const char *strValue, int tamValue, string strNome)
{
    // Guarda a quantidade de Blocos necessários para armazenar o dado
    int BlocosNecessarios = ceil ((float)tamValue/tamBlocos);

    //Guarda o id dos Blocos onde serão inseridos
    int Blocos[BlocosNecessarios];
    InicializarArray(Blocos, BlocosNecessarios, 0);

    //Testa para saber se existe Blocos livres
    if(isFree(BlocosNecessarios)){
        int achados = 0;
        int contPool = 0;
        int contBlocos = 0;
        while(BlocosNecessarios > achados){
            Bloco *aux;
            pool.GetElem(contPool, aux);

            if((aux->getFim() - aux->getInicio()) == 0){// se o inicio e o fim forem iguais
                Blocos[contBlocos] = aux->getFim();
                achados++;
                contBlocos++;
            } else{
                for(int i = aux->getInicio(); i<= aux->getFim(); i++){
                    Blocos[contBlocos] = i;
                    achados++;
                    contBlocos++;
                    if(BlocosNecessarios <= achados)// se ele já tiver a quantidade necessária então sair o for
                        break;
                }
            }
            contPool++;
        }

        int pos;
        int id = 0;
        for(int i = 0; i<tamValue; i++){
            if(((i%tamBlocos) == 0) && (i>0)){
                id++;
            }
            pos = ((Blocos[id])*tamBlocos) + (i%tamBlocos);
            Mem[pos] = strValue[i];
        }

        File *novoArquivo = new File(strNome, tamValue, Blocos);
        info.Insert(info.Size(), novoArquivo);

        AtualizarPool();
        livre = livre - BlocosNecessarios;
        return 1;

    } else{ // envia uma msg se não tiver espaço suficiente
        cout<<"Não tem espaço suficiente.";
        return 0;
    }
}

int memoria::Excluir(string nome)
{
    File *temp;
    for(int i = 0; i< info.Size(); i++){
        info.GetElem(i,temp);
        if(temp->getNome() == nome){

            int tamanho = temp->getTamanho();

            int BlocosNecessarios = ceil ((float)tamanho/tamBlocos);

            for(int j = 0; j < BlocosNecessarios; j++){
                for(int k = 0; k < tamBlocos; k++){
                    int pos = (temp->getCluster(j)*tamBlocos)+k;
                    Mem[pos] = '0';
                }
            }
            info.Remove(i);
            livre += BlocosNecessarios;
            AtualizarPool();
            return 1;
        }
    }
    return 0;
}

memoria::Buscar(string nome)
{
    File *temp;
    for(int i = 0; i< info.Size(); i++){
        info.GetElem(i,temp);
        if(temp->getNome() == nome){
            char tam[10];
   
            push_back(temp->getNome().c_str());
            itoa(temp->getTamanho(),tam,10); // pega o tamanho e jogar em 'tam'
            push_back( tam);

            int tamanho = temp->getTamanho();
            int BlocosNecessarios = ceil ((float)tamanho/tamBlocos);
            for(int j = 0; j<BlocosNecessarios; j++){
               itoa(temp->getCluster(j), tam, 10);
               if(j == 0)
                push_back(tam);
               else{
                cout<<", ";
                push_back(tam);
               }
            }

            for(int j = 0; j < BlocosNecessarios; j++){
                for(int k = 0; k < tamBlocos; k++){
                    int pos = (temp->getCluster(j)*tamBlocos)+k;
                        push_back(Mem[pos]);
                }
            }
        }
    }
}

memoria::Listar()
{
   File *aux;
   for(int i=0; i<info.Size(); i++){
       char tam[10];
       info.GetElem(i, aux);

       push_back(aux->getNome().c_str());

       itoa(aux->getTamanho(),tam,10); // pega o tamanho e jogar em 'tam'
       push_back( tam);

       int tamanho = aux->getTamanho();
       int BlocosNecessarios = ceil ((float)tamanho/tamBlocos);
       for(int j = 0; j<BlocosNecessarios; j++){
           itoa(aux->getCluster(j), tam, 10);
           if(j == 0)
            push_back(tam);
            else
                cout<<", ";
                push_back(tam);
       }
   }
}

//Inicializa um array com o valor 0
void memoria::InicializarArray(int array[], int tamanho, int valor)
{
    for(int i=0; i<tamanho; i++){
        array[i] = valor;
    }
}

//Inicializa um array com o valor 0
void memoria::InicializarArray(char array[], int tamanho)
{
    for(int i=0; i<tamanho; i++){
        array[i] = '0';
    }
}

// Atualiza o pool com os novos valores
void memoria::AtualizarPool()
{
    int vazio[numBlocos][2];// [0] tem o inicio, [1] tem o final
    int inicio = 0;
    int igual = 0;
    int cont = 0;

    for(int i = 0; i<numBlocos; i++){
        if(Mem[i*tamBlocos] == '0'){
            if(igual == 0){
                igual = 1;
                inicio = i;
            }
        } else{
            if(igual == 1){
                vazio[cont][0] = inicio;
                vazio[cont][1] = (i-1);
                igual = 0;
                cont ++;
            }
        }

        if(i == (numBlocos-1)){ // Testando se é o fim do 'for'
            if(igual == 1){
                vazio[cont][0] = inicio;
                vazio[cont][1] = (i);
                igual = 0;
                cont ++;
            }
        }
    }

    pool.RemoveAll();

    cout<<endl;
    for(int i = 0; i<cont; i++){
        Bloco *novo = new Bloco(i, vazio[i][0], vazio[i][1]);
        cout<<"["<<vazio[i][0]<<", "<<vazio[i][1]<<"] -> ";
        pool.Insert(i, novo);
    }
    cout<<endl;

}

int memoria::Free(){
    if(isFree(1)){
        int auxMem[numBlocos];
        InicializarArray(auxMem, numBlocos, 999);
        File *aux;
        for(int i = 0; i < info.Size(); i++){
            info.GetElem(i, aux);
            int tamanho = aux->getTamanho();
            int BlocosNecessarios = ceil ((float)tamanho/tamBlocos);
            for(int j = 0; j<BlocosNecessarios; j++){
                auxMem[aux->getCluster(j)] = (i+1);
            }
        }

        // Atualizando a lista 'info'
        int cont;
        for(int id = 0; id < info.Size(); id++){
            info.GetElem(id, aux);
            cont = 0;
            for(int j = 0; j<numBlocos; j++){ // j = Bloco; auxMem[j] = arquivo
                if((id+1) == auxMem[j]){ // para garantir que aux vai pegar só os seus Blocos
                    aux->setCluster(j, cont);
                    cont++;
                }
            }
        }
        AtualizarPool();
        return 1;

    } else{
        cout<<"Não tem espaço suficiente.";
        return 0;
    }
}

// retorna se tem espaço suficiente para ler o dado
bool memoria::isFree(int tam){
    return livre>=tam;
}

int memoria::getNumBlocos()
{
    return numBlocos;
}

int memoria::getTamanho()
{
    return tamanho;
}

int memoria::getTamBlocos()
{
    return tamBlocos;
}

char memoria::getMem(int id)
{
    return Mem[id];
}