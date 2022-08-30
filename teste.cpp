#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// cores dos vertices
#define BRANCO 0 // vertice nao descoberto
#define CINZA 1 // vertice descoberto
#define PRETO 2 // vertice fechado

//Vertices do Grafo
int* grafo;
int* pai;
int* cor;
int nCiclos;
vector<int> ciclos;

int** M; // matriz de adjacencia
int** W; // matriz do fecho transitivo

int n, m;


/*void dfsVisit(auto it){
    cor[*it] = CINZA;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(M[i][j] != 0){
                if(cor[M[i][j]] == BRANCO){
                    cout <<"Visitando: " << M[i][j] << endl;
                    pai[M[i][j]] = *it;
                    dfsVisit(M[i][j]);
                }else if(cor[M[i][j]]==CINZA and pai[*it] != M[i][j]){
                    nCiclos++;
                }
            }
        }
    }
    cor[*it] = PRETO;
    ciclos.push_back(*it);
}*/

void dfsVisit(int it){
    cor[it] = CINZA;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(M[i][j] != 0){
                if(cor[M[i][j]] == BRANCO){
                    cout <<"Visitando: " << M[i][j] << endl;
                    pai[M[i][j]] = it;
                    dfsVisit(M[i][j]);
                }else if(cor[M[i][j]]==CINZA and pai[it] != M[i][j]){
                    nCiclos++;
                }
            }
        }
    }
    cor[it] = PRETO;
    ciclos.push_back(it);
}


/*if(cor[i] == BRANCO){
                cout <<"Visitando: " << *i << endl;
                pai[i] = *it;
                dfsVisit(i);
            }else if(cor[i]==CINZA and pai[*it] != *i){
                nCiclos++;
            }
*/

void dfs(){
    cout << "visitando: 1" << endl;
    for(int i = 0; i < n; i++){
        if( cor[i] == BRANCO ){
            dfsVisit(i);
        }
    }
}


int main()
{  
    cin >> n >> m;

    grafo = new int[n];

    // alocando as estruturas auxiliares
    pai = new int[n+1]; // armazena o pai de cada vertice
    cor = new int[n+1]; // armazena a cor de cada vertice
    
    // iniciando as estruturas auxiliares (Todo mundo com pai -1 e Branco)
    for(int i = 1; i <= n; i++){
        pai[i] = -1;
        cor[i] = BRANCO;
    }

    // ---------------------------------------------------------------------------------------
    M = new int*[n+1]; // matriz de adjacencia
    W = new int*[n+1];

    for(int i = 1; i <= n; i++){
        M[i] = new int[n+1];
        W[i] = new int[n+1];
    }

    for(int u = 1; u <= n; u++){
        for(int v = 1; v <= n; v++){
            M[u][v] = W[u][v] = 0;
        }
    }
    
    // leitura do grafo
    int u, v;
    for(int i = 0; i < m; i++){
        cin >> u >> v; // lendo as arestas do grafo
        M[u][v] = W[u][v] += 1;
    }

    //Preenchimento do grafo
    for(int i =1; i<=n ; i++){
        grafo[i] = i;
    }
    // ---------------------------------------------------------
    // Tratamento de arestas duplas
    //for(auto it3 = lista_adj[u].begin(); it3 != lista_adj[u].end(); it3++){
        
    //}

    cout << "Matriz de adjacencia" << endl;
    for(int u = 1; u <= n; u++){
        for(int v = 1; v <= n; v++){
            cout << M[u][v] << " ";
        }
        cout << endl;
    }

    nCiclos = 0;

    dfs();
    cout <<"nCiclos:" <<nCiclos << endl;
    for(auto it3 = ciclos.begin(); it3 != ciclos.end(); it3++){
        cout << *it3 << " ";
    }



    // Desalocação de memória
    delete[] pai;
    delete[] cor;
    delete[] grafo;

    for(int u = 0; u <= n; u++){
        delete M[u];
        delete W[u];
    }

     delete[] M;
     delete[] W;

    return 0;
}
   