/*
Dênis de Souza Cordeiro - 202110235 - 14A
Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
Ronald Souza Galdino - 202110679 - 14A
*/

// A ideia geral do algoritmo que normalmente é inserida aqui foi descrita no relatório :)

#include <iostream>
#include <vector>
using namespace std;

vector<int>* controle;  // Uma "lista de controle dos distritos", Array de Vectors (representando os GRUPOS que controlam determinado DISTRITO)
vector<int> visitados;  // vector de distritos já visitados (usamos array para podermos utilizar ".clear()", sua capacidade nunca ultrapassa "d")
bool encerrar;          // Variável que defino encerramento do algoritmo (um caminho foi encontrado)
int bomInicial = 0;     // Variável que indica o distrito inicial que obteve sucesso (a partir dele chegamos a todos os outros)

// Função que verifica se um elemento está contido no vector visitados
bool ehElemento(vector<int> visitados, int elemento){
    for(int x : visitados){
        if( elemento == x){
            return true;
        }
    }
    return false;
}

// Função que verifica se a condição de parada (ter passado em todos os "d" distritos) já foi satisfeita
// obs: A corretude é asseguradaa pois tems trechos que evitam a "visita" de distritos repetidos
void chegamos(int d){
    if((int)visitados.size() == d){
        cout << bomInicial << endl;
        encerrar = true;
    }
}

// Prototipação da função "sairDistrito", para que ela possa ser usada logo abaixo
int sairDistrito(int distrito, int ticket, int d);

// Função para realização da ENTRADA no distrito
// Verifica se a entrada pode ser feita, faz a chama da função de saída passando o ticket correto (ticket oposto ou igual, depende de quantos grupos controlam esse distrito)
int entrarDistrito(int distrito, int ticket, int d){ 
    if(encerrar == true){   // if de encerramento
        return 0;
    } 
    if(controle[distrito].size() == 2){     // É controlado por 2 grupos
        if(ticket == controle[distrito].at(0) or ticket == controle[distrito].at(1)){   // se é controlado por 2 deve ser aceito por PELO MENOS 1
            visitados.push_back(distrito);  // Adiciona ao vector de visitados
            chegamos(d);                     // Verifica já visitamos todos
            if(encerrar){                   // if de encerramento 
                return 0;
            }

            // Chama a função de saída do distrito com o TICKET OPOSTO
            if(ticket == controle[distrito].at(0)){
                sairDistrito(distrito,controle[distrito].at(1), d);
            }
            else{
                sairDistrito(distrito,controle[distrito].at(0), d);
            }
        }
        else{   
            // A entrada não foi permitida
            return 0;
        }
    }
    else{ // é controlado por 1 grupo
        if(controle[distrito].at(0) != ticket){     
            // A entrada não foi permitida
            return 0;
        }
        else{ // foi aceito
            visitados.push_back(distrito);      // Adiciona ao vector de visitados
            chegamos(d);                         // Verifica se já visitamos todos
            if(encerrar){                       // if de encerramento
                return 0;
            }
            sairDistrito(distrito,controle[distrito].at(0), d); // Chama a função de saída com O MESMO TICKET
        }
    }
    return 0;
}

// Chama a função de saída EXCLUSIVAMENTE para o vértice inicial (ela é diferente pois deve testar, se necessário, as 2 possibilidades de entrada no distrito inicial)
int sairDistritoInicial(int distrito, int ticket, int d){  //controlar o ticket de saída
    bomInicial = distrito;  // A saída é incial
    if(encerrar == true){   // if de encerramento
        return 0;
    }
    if(controle[distrito].size() == 2){ // é controlado por 2 grupos
        if( ticket == controle[distrito].at(0)){        // garantir que saíremos com o ticket oposto
            for(int i = 0; i < d; i++){                 // Vai testar entrar em todos os distritos
                visitados.clear();                      // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
                visitados.push_back(distrito);          // adicionar ele mesmo à lista dos já visitados
                if( ehElemento(visitados, i)){          // Vai pular os vértices já visitados
                    continue;
                }
                else{
                    entrarDistrito(i,controle[distrito].at(1), d); // Chama a função de entrada com o ticket oposto
                }
            }
        }
        else{
            for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
                visitados.clear();                  // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
                visitados.push_back(distrito);      // adicionar ele mesmo à lista dos já visitados
                if( ehElemento(visitados, i)){      // Pular os vértices já visitados
                    continue;
                }
                else{ 
                    entrarDistrito(i,controle[distrito].at(0), d); // Chama a função de entrada com o ticket oposto
                }
            }
        }
    }
    else{ // se não é controlado por 2 é por apenas 1 -> sai com o mesmo ticket
        for(int i = 0; i < d; i++){             // Vai testar entrar em todos os distritos
            visitados.clear();                  // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
            visitados.push_back(distrito);      // adicionar ele mesmo à lista dos já visitados
            if( ehElemento(visitados, i)){      // Pular os vértices já visitados
                continue;
            }
            else{ 
                entrarDistrito(i,controle[distrito].at(0), d); // Chama a função de entrada com o mesmo ticket
            }
        }
    }
    return 0;
}

// Função de saída do distrito para todos os casos excluso o inicial 
int sairDistrito(int distrito, int ticket, int d){
    if(encerrar == true){   // if de encerramento
        return 0;
    }
    for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
        if( ehElemento(visitados, i)){  // Pular os já visitados
            continue;
        }
        else{
            entrarDistrito(i,ticket, d);   // Chamar a função de entrada com o ticket correto que já recebeu como parâmetro
        } 
    }
    return 0;
}

int main(){

    int g;  // Número de grupos que controlam os distritos 
    int d;  // Número de distritos
    encerrar = false; // Não encerrar programa
    cin >> d >> g;

    while(d != 0 and g != 0){

        controle = new vector<int> [d]; // Instância o array de vectors (a "lista de controle")
        encerrar = false; // Não encerrar programa

        //Receber as relações do grafo (não é necessário uma M.A ou L.A pois temos um grafo COMPLETO)
        for(int i = 0; i < g; i++){
            int aux;        // sendo a primeira entrada de cada linha (quantidade de distritos controlados por aquele grupo)
            cin >> aux;
            if(aux == 0){
                continue;
            }
            for( int x = 0; x < aux; x++){
                int y; // um distrito a ser adicionado
                cin >> y;
                controle[y].push_back(i);
            }

        }

        // Realizar os testes com TODOS os distritos como INICIAIS (combinando com seus respectivos tickets)
        for(int i = 0; i < d; i++){ // Com "i" sendo o vértice inicial
            if(encerrar){
                break;
            }
            for(int x = 0; x < (int)controle[i].size(); x++){
                int ticket = controle[i].at(x);
                visitados.clear();      // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
                visitados.push_back(i); // adicionar ele mesmo à lista dos já visitados
                sairDistritoInicial(i, ticket, d);
                if(encerrar){
                    break;
                }
            }
        }

        // Caso não tenhamos encontrado com caminho hamiltoniano -> -1
        if(encerrar == false){
            cout << -1 << endl;
        }

        cin >> d >> g;
    }

    return 0;
}