#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

//Uma "lista de controle dos distritos"
vector<int>* controle;  // Array de Vectors (representando os GRUPOS que controlam determinado DISTRITO)
//bool* visitados; // Array de distritos já visitados
int d;
int entregues; // Numero de pizzas enregues
vector<int> visitados; // Array de distritos já visitados

bool ehElemento(vector<int> visitados, int elemento){
    for(int x : visitados){
        if( elemento == x){
            return true;
        }
    }
    return false;
}

void chegamos(){
    if(visitados.size() == d){
        cout << endl << "\t\t chegamos \t\t" << endl;
    }
}

void sairDistrito(int distrito, int ticket);

bool entrarDistrito(int distrito, int ticket){  //retorna false se o Pizzaiolo for bloqueado
    // agora temos que verificar se o ticket que estamos tentando entrar é "VALIDO"
    // Entrada
    cout << " dados recebidos pela funcao de ENTRADA: distrito = " << distrito << ' ' << " ticket = " << ticket << endl;
    if(controle[distrito].size() == 2){ // se é controlado por 2 deve ser aceito por PELO MENOS 1
        if(ticket == controle[distrito].at(0) or ticket == controle[distrito].at(1)){
            cout << " Fui aceito no distrito " << distrito << " com o ticket " << ticket << endl;
            visitados.push_back(distrito);
            chegamos();
            //Saída do distrito
            if(ticket == controle[distrito].at(0)){
                sairDistrito(distrito,controle[distrito].at(1));
            }
            else{
                sairDistrito(distrito,controle[distrito].at(0));
            }
            /* for(int i = 0; i < 2; i++){ // TEM QUE SAIR COM O OPOSTO
               sairDistrito(distrito,controle[distrito].at(i));
            } */
        }
        else{
            cout << " Fui Denied no distrito " << distrito << " com o ticket " << ticket << endl; 
        }
    }
    else{ // é controlado por 1
        if(controle[distrito].at(0) != ticket){
            cout << " Fui Denied no distrito " << distrito << "com o ticket " << ticket << endl; 
            //return false;
        }
        else{ // foi aceito
            cout << " Fui Aceito no distrito " << distrito << "com o ticket " << ticket << endl; 
            visitados.push_back(distrito);
            chegamos();
            sairDistrito(distrito,controle[distrito].at(0)); // temos que sair com o mesmo
        }
    }

    return false;
}

// Essa tá inicialmente OK
void sairDistritoInicial(int distrito, int ticket){  //controlar o ticket de saída
    //std::cout << endl << "case de sair com size() = " << controle[distrito].size() << endl;
    // Saída
    cout << " dados recebidos pela funcao de sairInicial: distrito = " << distrito << ' ' << " ticket = " << ticket << endl;
    if(controle[distrito].size() == 2){ // se é controlado por 2 grupos -> sair com o ticket oposto
        if( ticket == controle[distrito].at(0)){ 
            for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
                visitados.clear(); // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
                visitados.push_back(distrito); // adicionar ele mesmo à lista dos já visitados
                if( ehElemento(visitados, i)){
                    cout << "Vou pular esse pq já foi visitado " << i << endl;
                    continue;
                }
                else{
                    cout << "Estoy saindo do distrito " << distrito << " com o ticket " << controle[distrito].at(1) << " e indo para " <<  i << endl;
                    entrarDistrito(i,controle[distrito].at(1));
                }
                   
                
            }
        }
        else{
            for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
                visitados.clear(); // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
                visitados.push_back(distrito); // adicionar ele mesmo à lista dos já visitados
                if( ehElemento(visitados, i)){
                    cout << "Vou pular esse pq já foi visitado " << i << endl;
                    continue;
                }
                else{ 
                    cout << "Estou saindo do distrito " << distrito << " com o ticket " << controle[distrito].at(0) << " e indo para " <<  i << endl;
                    entrarDistrito(i,controle[distrito].at(0));
                }
                
            }
        }
    }
    else{ // se não é controlado por 2 é por apenas 1 -> sai com o ticket oposto
        for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
            cout << "isso que deu merda" << endl;
            visitados.clear(); // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
            visitados.push_back(distrito); // adicionar ele mesmo à lista dos já visitados
            if( ehElemento(visitados, i)){
                cout << "Vou pular esse pq já foi visitado " << i << endl;
                continue;
            }
            else{ 
                cout << "Estou saindo do distrito " << distrito << " (1) com o ticket " << controle[distrito].at(0) << " e indo para " <<  i << endl;
                entrarDistrito(i,controle[distrito].at(0));
            }
        }
    }

}

void sairDistrito(int distrito, int ticket){
    //std::cout << endl << "case de sair com size() = " << controle[distrito].size() << endl;
    // Saída
    cout << " dados recebidos pela funcao de sairDistrito: distrito = " << distrito << ' ' << " ticket = " << ticket << endl;

    for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
        if( ehElemento(visitados, i)){
            cout << "Vou pular esse pq já foi visitado " << i << endl;
            continue;
        }
        else{
            cout << "Estou saindo do distrito " << distrito << " com o ticket " << ticket << " e indo para " <<  i << endl;
            entrarDistrito(i,ticket);
        } 
    }
}

void tentarEntregar(int inicial, int ticket){
    cout << endl << "Começando entrega por inicial: " << inicial << " ticket :" << ticket << endl;
    //A entrada no distrito inicial não precisa ser testada (já garantimos que será com um ticket válido)
    sairDistritoInicial(inicial,ticket);
}

int main(){

    int g;

    cin >> d >> g;

    controle = new vector<int> [d];

    // isso aqui é só teste
    /* visitados.push_back(false);

    for(bool x : visitados){
        cout << endl << x << endl;
    } */

    //Receber as relações do grafo (não é necessário uma M.A ou L.A pois temos um grafo COMPLETO.
    for(int i = 0; i < g; i++){
        int aux;   // sendo a primeira entrada de cada linha (quantidade de distritos controlados por aquele grupo)
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

    cout << endl;

    //Print da lista de controle

    cout << "Lista de Controle:" << endl;
    for(int i = 0 ; i <  d; i++){
        for(int x : controle[i]){
            cout << x << ' ';
        }
        cout << endl;
    }
    cout << endl;

    //print dos sizes
    for(int i =0; i<d; i++){
        cout << endl << controle[i].size() << endl;
    }


    //
    for(int i = 0; i < d; i++){ // Com "i" sendo o vértice inicial
        for(int x = 0; x < controle[i].size(); x++){
            int ticket = controle[i].at(x);
            visitados.clear(); // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
            visitados.push_back(i); // adicionar ele mesmo à lista dos já visitados
            tentarEntregar(i, ticket);
        }
    }

    cout << "fim";

    return 0;
}