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
vector<int> grafo;
vector<int>* lista_adj;
int* pai;
int* cor;
int nCiclos;
vector<int> ciclos;


void dfsVisit(auto it){
    cor[*it] = CINZA;

    
    for(auto it2 = lista_adj[*it].begin(); it2 != lista_adj[*it].end(); it2++){
        if(cor[*it2] == BRANCO){
            cout <<"Visitando: " << *it2 << endl;
            pai[*it2] = *it;
            dfsVisit(it2);
        }
        else if(cor[*it2]==CINZA and pai[*it] != *it2){
            nCiclos++;
        }
    }
    cor[*it] = PRETO;
    ciclos.push_back(*it);
}

void dfs(){
    cout << "visitando: 1" << endl;
    for(auto it = grafo.begin(); it != grafo.end(); it++){
        if( cor[*it] == BRANCO ){
            dfsVisit(it);
        }
    }
}



int main()
{  
    int n, m;
    cin >> n >> m;


    // alocando as estruturas auxiliares
    pai = new int[n+1]; // armazena o pai de cada vertice
    cor = new int[n+1]; // armazena a cor de cada vertice
    
    // iniciando as estruturas auxiliares (Todo mundo com pai -1 e Branco)
    for(int i = 1; i <= n; i++){
        pai[i] = -1;
        cor[i] = BRANCO;
    }

    lista_adj = new vector<int>[n+1];

    // leitura do grafo
    int u, v;

    //Preenchimento do grafo
    for(int i =1; i<=n ; i++){
        grafo.push_back(i);
    }

    for(int i = 0; i < m; i++){
        cin >> u >> v; // lendo as arestas do grafo

        // grafo nao-orientado
        lista_adj[u].push_back(v); //u -> v
        lista_adj[v].push_back(u); //v -> u
    }

    // Tratamento de arestas duplas
    for(auto it3 = lista_adj[u].begin(); it3 != lista_adj[u].end(); it3++){
        
    }

    nCiclos = 0;

    dfs();
    cout <<"nCiclos:" <<nCiclos << endl;
    for(auto it3 = ciclos.begin(); it3 != ciclos.end(); it3++){
        cout << *it3 << " ";
    }


    delete[] pai;
    delete[] cor;

    return 0;
}
   