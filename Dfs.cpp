#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;

// cores dos vertices
#define BRANCO 0 // vertice nao descoberto
#define CINZA 1 // vertice descoberto
#define PRETO 2 // vertice fechado

int main()
{  
    int n, m;
    cin >> n >> m;


    // alocando as estruturas auxiliares
    int* pai = new int[n+1]; // armazena o pai de cada vertice
    int* cor = new int[n+1]; // armazena a cor de cada vertice
    
    // iniciando as estruturas auxiliares
    for(int i = 1; i <= n; i++){
        pai[i] = -1;
        cor[i] = BRANCO;
    }

    vector<int>* lista_adj = new vector<int>[n+1];

    // leitura do grafo
    int u, v;
    for(int i = 0; i < m; i++){
        cin >> u >> v; // lendo as arestas do grafo

      // evitando a leitura de vertices repetidos nas listas
      /*
      if(find(lista_adj[u].begin(), lista_adj[u].end(), v) != lista_adj[u].end())
      {
        continue;
      }
      */

        // grafo nao-orientado
        lista_adj[u].push_back(v); //u -> v
        lista_adj[v].push_back(u); //v -> u
    }

    int s = 1; // vertice origem           // Tem que ser fornecido pelo usuário
    stack<int> pilha; // fila de vertices a serem explorados na BFS
    pilha.push(s);
    cor[s] = CINZA;

    while(!pilha.empty())
    {
      int u = pilha.top();  // Acessa o elemento do topo
      cout << u << " ";
      pilha.pop();          // Já remove da pilha
      cor[u]= PRETO;

      for(auto it = lista_adj[u].begin(); it != lista_adj[u].end(); it++)
      { 
          // se o vertice ainda nao foi descoberto
          if(cor[*it] == BRANCO)
          {
              cor[*it] = CINZA;
              pai[*it] = u;
              pilha.push(*it);
          }   
      }
    }

    delete[] pai;
    delete[] cor;

    return 0;
}
   