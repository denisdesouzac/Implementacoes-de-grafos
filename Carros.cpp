#include <iostream>
#include <vector>
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
    if(controle[distrito].size() == 2){ // se é controlado por 2 deve ser aceito por PELO MENOS 1
        if(ticket == controle[distrito].at(0) or ticket == controle[distrito].at(1)){
            cout << " Fui aceito no distrito " << distrito << " com o ticket " << ticket << endl;
            visitados.push_back(distrito);
            chegamos();
            for(int i = 0; i < 2; i++){ // vai testar sair com ambos os tickets
               sairDistrito(distrito,controle[distrito].at(i));
            }
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
void sairDistrito(int distrito, int ticket){  //controlar o ticket de saída
    if(controle[distrito].size() == 2){ // se é controlado por 2 grupos -> pode sair com qualquer ticket
        if( ticket == controle[distrito].at(0)){ 
            for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
                if( ehElemento(visitados, i)){
                    cout << "Vou pular esse pq já foi visitado " << i << endl;
                    continue;
                }
                else{
                    cout << "Estou saindo do distrito " << distrito << " com o ticket " << controle[distrito].at(1) << " e indo para " <<  i << endl;
                    entrarDistrito(i,controle[distrito].at(1));
                }
                   
                
            }
        }
        else{
            for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
                if( ehElemento(visitados, i)){
                    cout << "Vou pular esse pq já foi visitado " << i << endl;
                    continue;
                }
                else{ 
                    cout << "Estou saindo do distrito " << distrito << " com o ticket " << controle[distrito].at(0) << " e indo para " <<  i << endl;
                    entrarDistrito(i,controle[distrito].at(1));
                }
                
            }
        }
    }
    else{ // se não é controlado por 2 é por apenas 1 -> sai com o ticket oposto
        for(int i = 0; i < d; i++){ // Vai testar entrar em todos os distritos
            if( ehElemento(visitados, i)){
                cout << "Vou pular esse pq já foi visitado " << i << endl;
                continue;
            }
            else{ 
                cout << "Estou saindo do distrito " << distrito << " com o ticket " << controle[distrito].at(1) << " e indo para " <<  i << endl;
                entrarDistrito(i,controle[distrito].at(0));
            }
        }
    }

}

void tentarEntregar(int inicial, int ticket){
    cout << endl << "Começando entrega por inicial: " << inicial << " ticket :" << ticket << endl;
    //A entrada no distrito inicial não precisa ser testada (já garantimos que será com um ticket válido)
    sairDistrito(inicial,ticket);
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

    //
    for(int i = 0; i < d; i++){ // Com "i" sendo o vértice inicial
        for(int x = 0; x < controle[i].size(); x++){
            int ticket = controle[i].at(x);
            visitados.clear(); // Limpar o vector de visitados pois cada vez que começamos por um ponto ou ticket novo temos Mudar TUDO
            visitados.push_back(i); // adicionar ele mesmo à lista dos já visitados
            tentarEntregar(i, ticket);
        }
    }

    return 0;
}