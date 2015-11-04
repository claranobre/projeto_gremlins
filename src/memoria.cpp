#include "memoria.h"
#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include <math.h>

memoria::memoria(int quantSetores, int tamSetores, int tammemoria)
{
    this->numSetores = quantSetores;
    this->tamSetores = tamSetores;
    this->tamanho = tammemoria;
    this->livre = quantSetores;

    // Inicializando o pool no intervalo [0, quantSetores]
    Setor *novo = new Setor(0, 0, quantSetores);
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
    // Guarda a quantidade de setores necessários para armazenar o dado
    int setoresNecessarios = ceil ((float)tamValue/tamSetores);

    //Guarda o id dos setores onde serão inseridos
    int setores[setoresNecessarios];
    InicializarArray(setores, setoresNecessarios, 0);

    //Testa para saber se existe setores livres
    if(isFree(setoresNecessarios)){
        int achados = 0;
        int contPool = 0;
        int contSetores = 0;
        while(setoresNecessarios > achados){
            Setor *aux;
            pool.GetElem(contPool, aux);

            if((aux->getFim() - aux->getInicio()) == 0){// se o inicio e o fim forem iguais
                setores[contSetores] = aux->getFim();
                achados++;
                contSetores++;
            } else{
                for(int i = aux->getInicio(); i<= aux->getFim(); i++){
                    setores[contSetores] = i;
                    achados++;
                    contSetores++;
                    if(setoresNecessarios <= achados)// se ele já tiver a quantidade necessária então sair o for
                        break;
                }
            }
            contPool++;
        }

        int pos;
        int id = 0;
        for(int i = 0; i<tamValue; i++){
            if(((i%tamSetores) == 0) && (i>0)){
                id++;
            }
            pos = ((setores[id])*tamSetores) + (i%tamSetores);
            Mem[pos] = strValue[i];
        }

        File *novoArquivo = new File(strNome, tamValue, setores);
        info.Insert(info.Size(), novoArquivo);

        AtualizarPool();
        livre = livre - setoresNecessarios;
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

            int setoresNecessarios = ceil ((float)tamanho/tamSetores);

            for(int j = 0; j < setoresNecessarios; j++){
                for(int k = 0; k < tamSetores; k++){
                    int pos = (temp->getCluster(j)*tamSetores)+k;
                    Mem[pos] = '0';
                }
            }
            info.Remove(i);
            livre += setoresNecessarios;
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
            html.push_back( tam);

            int tamanho = temp->getTamanho();
            int setoresNecessarios = ceil ((float)tamanho/tamSetores);
            for(int j = 0; j<setoresNecessarios; j++){
               itoa(temp->getCluster(j), tam, 10);
               if(j == 0)
                push_back(tam);
               else{
                cout<<", ";
                push_back(tam);
               }
            }

            for(int j = 0; j < setoresNecessarios; j++){
                for(int k = 0; k < tamSetores; k++){
                    int pos = (temp->getCluster(j)*tamSetores)+k;
                    html.push_back(Mem[pos]);
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
       int setoresNecessarios = ceil ((float)tamanho/tamSetores);
       for(int j = 0; j<setoresNecessarios; j++){
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
    int vazio[numSetores][2];// [0] tem o inicio, [1] tem o final
    int inicio = 0;
    int igual = 0;
    int cont = 0;

    for(int i = 0; i<numSetores; i++){
        if(Mem[i*tamSetores] == '0'){
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

        if(i == (numSetores-1)){ // Testando se é o fim do 'for'
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
        Setor *novo = new Setor(i, vazio[i][0], vazio[i][1]);
        cout<<"["<<vazio[i][0]<<", "<<vazio[i][1]<<"] -> ";
        pool.Insert(i, novo);
    }
    cout<<endl;

}

int memoria::Free(){
    if(isFree(1)){
        int auxMem[numSetores];
        InicializarArray(auxMem, numSetores, 999);
        File *aux;
        for(int i = 0; i < info.Size(); i++){
            info.GetElem(i, aux);
            int tamanho = aux->getTamanho();
            int setoresNecessarios = ceil ((float)tamanho/tamSetores);
            for(int j = 0; j<setoresNecessarios; j++){
                auxMem[aux->getCluster(j)] = (i+1);
            }
        }

        // Atualizando a lista 'info'
        int cont;
        for(int id = 0; id < info.Size(); id++){
            info.GetElem(id, aux);
            cont = 0;
            for(int j = 0; j<numSetores; j++){ // j = setor; auxMem[j] = arquivo
                if((id+1) == auxMem[j]){ // para garantir que aux vai pegar só os seus setores
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

int memoria::getNumSetores()
{
    return numSetores;
}

int memoria::getTamanho()
{
    return tamanho;
}

int memoria::getTamSetores()
{
    return tamSetores;
}

char memoria::getMem(int id)
{
    return Mem[id];
}