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

    this->disk = new char[tammemoria];
    InicializarArray(disk, tammemoria);
}

// Falta terminar de consertar
memoria::~memoria()
{
    info.~Lista();
    pool.~Lista();
    delete disk;
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
            disk[pos] = strValue[i];
        }

        File *novoArquivo = new File(strNome, tamValue, setores);
        info.Insert(info.Size(), novoArquivo);

        AtualizarPool();
        livre = livre - setoresNecessarios;
        return 1;

    } else{ // envia uma msg se não tiver espaço suficiente
        QMessageBox msgBox;
        msgBox.setText("Não tem espaço suficiente.");
        msgBox.exec();
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
                    disk[pos] = '0';
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

QString memoria::Buscar(string nome)
{
    File *temp;
    QString html;
    for(int i = 0; i< info.Size(); i++){
        info.GetElem(i,temp);
        if(temp->getNome() == nome){
            char tam[10];
            html = "<table border=1><tr><th>Nome</th><th>Tamanho</th><th>Cluster</th></tr>";

            html.push_back("<tr> <td align = 'center'>");
            html.push_back(temp->getNome().c_str());
            html.push_back("</td>");

            html.push_back("<td align = 'center'>");
            itoa(temp->getTamanho(),tam,10); // pega o tamanho e jogar em 'tam'
            html.push_back( tam);
            html.push_back("</td>");

            html.push_back("<td align = 'center'>");
            int tamanho = temp->getTamanho();
            int setoresNecessarios = ceil ((float)tamanho/tamSetores);
            for(int j = 0; j<setoresNecessarios; j++){
               itoa(temp->getCluster(j), tam, 10);
               if(j == 0)
                   html.push_back(tam);
               else{
                   html.push_back(", ");
                   html.push_back(tam);
               }
            }
            html.push_back("</td></tr>");

            html.push_back("<tr><td colspan='3' align='center'><b>Valor</b></td></tr>");

            html.push_back("<tr><td colspan='3' align='center'>");

            for(int j = 0; j < setoresNecessarios; j++){
                for(int k = 0; k < tamSetores; k++){
                    int pos = (temp->getCluster(j)*tamSetores)+k;
                    html.push_back(disk[pos]);
                }
            }

            html.push_back("</td></tr>");
            html.push_back("<table>");
            return html;
        }
    }
    return html;
}

QString memoria::Listar()
{
   QString html = "<table border=1><tr><th>Nome</th><th>Tamanho</th><th>Cluster</th></tr>";
   File *aux;
   for(int i=0; i<info.Size(); i++){
       char tam[10];
       info.GetElem(i, aux);

       html.push_back("<tr> <td align = 'center'>");
       html.push_back(aux->getNome().c_str());
       html.push_back("</td>");

       html.push_back("<td align = 'center'>");
       itoa(aux->getTamanho(),tam,10); // pega o tamanho e jogar em 'tam'
       html.push_back( tam);
       html.push_back("</td>");

       html.push_back("<td align = 'center'>");
       int tamanho = aux->getTamanho();
       int setoresNecessarios = ceil ((float)tamanho/tamSetores);
       for(int j = 0; j<setoresNecessarios; j++){
           itoa(aux->getCluster(j), tam, 10);
           if(j == 0)
               html.push_back(tam);
           else{
               html.push_back(", ");
               html.push_back(tam);
           }
       }
       html.push_back("</td></tr>");
   }
   html.push_back("<table>");
   return html;
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
        if(disk[i*tamSetores] == '0'){
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

int memoria::Formatar(){
    pool.RemoveAll();
    info.RemoveAll();
    livre = numSetores;
    InicializarArray(disk, tamanho);

    // Inicializando o pool no intervalo [0, quantSetores]
    Setor *novo = new Setor(0, 0, numSetores);
    pool.Insert(0, novo);

    return 1;
}

int memoria::Desfragmentar(){
    if(isFree(1)){
        // vetor que vai informar qual arquivo está em qual setor
        // ex: auxDisk[0] = 1; Setor 0 tá com uma parte do arquivo 1
        // ex: auxDisk[9] = 5; Setor 9 tá com uma parte do arquivo 5
        int auxDisk[numSetores];
        InicializarArray(auxDisk, numSetores, 999);
        File *aux;
        for(int i = 0; i < info.Size(); i++){
            info.GetElem(i, aux);
            int tamanho = aux->getTamanho();
            int setoresNecessarios = ceil ((float)tamanho/tamSetores);
            for(int j = 0; j<setoresNecessarios; j++){
                auxDisk[aux->getCluster(j)] = (i+1);
            }
        }

        // se não tiver fragmentado ele encerra a função
        if(!isFragmented(auxDisk)){
            cout<<"I'm fine!"<<endl;
            return 1;
        }
        cout<<"i'm sick =/"<<endl;

        for(int i = 0; i<numSetores; i++){
            for(int j = 0; j<numSetores-1; j++){
                if(auxDisk[j] > auxDisk[j+1]) {
                    std::swap(auxDisk[j], auxDisk[j+1]);
                    for(int k = 0; k<tamSetores; k++){
                        int pos1 = (tamSetores*j)+k;
                        int pos2 = (tamSetores*(j+1))+k;

                        // troca os valores do memoria
                        std::swap(disk[pos1], disk[pos2]);
                    }
                }
            }
        }

        // Atualizando a lista 'info'
        int cont;
        for(int id = 0; id < info.Size(); id++){
            info.GetElem(id, aux);
            cont = 0;
            for(int j = 0; j<numSetores; j++){ // j = setor; auxDisk[j] = arquivo
                if((id+1) == auxDisk[j]){ // para garantir que aux vai pegar só os seus setores
                    aux->setCluster(j, cont);
                    cont++;
                }
            }
        }
        AtualizarPool();
        return 1;

    } else{
        QMessageBox msgBox;
        msgBox.setText("Não tem espaço suficiente.");
        msgBox.exec();
        return 0;
    }
}

int memoria::isFragmented(int memoria[])
{
    if(pool.Size()>1)
        return 1;

    int prox;
    for(int i = 0; i<numSetores; i++){
        prox = i;
        for(int j = i; j<numSetores; j++){
            if(memoria[i] == memoria[j]){
                if(j == (prox+1) || j == prox){
                    prox = j;
                }
                else{
                    return 1;
                }
            }
        }
    }
    return 0;

}

// retorna se tem espaço suficiente para colocar o dado
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

char memoria::getDisk(int id)
{
    return disk[id];
}

/**
     * C++ version 0.4 char* style "itoa":
     * Written by Lukás Chmela
     * Released under GPLv3.
     */
char* memoria::itoa(int value, char* result, int base) {
        // check that the base if valid
        if (base < 2 || base > 36) { *result = '\0'; return result; }

        char* ptr = result, *ptr1 = result, tmp_char;
        int tmp_value;

        do {
            tmp_value = value;
            value /= base;
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
        } while ( value );

        // Apply negative sign
        if (tmp_value < 0) *ptr++ = '-';
        *ptr-- = '\0';
        while(ptr1 < ptr) {
            tmp_char = *ptr;
            *ptr--= *ptr1;
            *ptr1++ = tmp_char;
        }
        return result;
    }
