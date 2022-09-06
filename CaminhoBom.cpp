/*
Dênis de Souza Cordeiro - 202110235 - 14A
Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
Ronald de Souza Galdino - 202110679 - 14A
*/

/*
Ideia geral do algoritmo:
*/

/*
Observações:
- Usar Dijkstra (já que não temos arestas negativas, e consideramos um grafo ponderado).
- Não pode ser FLOYD Warshall pois a quantidade de Vértices pode ultrapassar 400. 
- Os vértice COMEÇAM EM ZERO.
*/

#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<functional>
using namespace std;

/*
 * Variaveis globais
 */

// lista de adjacencia
vector<pair<int, double>>* LA;

// numero de vertices do grafo
int n;

// numeor de arestas do grafo
int m;

// distancia da origem "org" a cada vertice do grafo
vector<double> d;

int dijkstra(int org)
{
    d.assign(n, 1.0);
    
    // a distance da origem "org" eh sempre zero
    d[org] = 0;
    
    // heap que auxilia na obtencao do vertice com maior prioridade, a cada iteracao
    priority_queue< pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>> > heap;

    // primeiro par inserido na heap: "org" com custo zero
    heap.push(make_pair(0, org));         // ERA 1
 
    vector<bool> visitado;
    visitado.assign(n, false);
 
    // o algoritmo para quando a heap estiver vazia
    while(!heap.empty())
    {
        pair<double, int> vertice = heap.top();
        heap.pop();

        double distancia = vertice.first;
        int u = vertice.second;
        cout << "Distancia: " << distancia << " u: " << u << endl;
     
        if(visitado[u]) // "u" jah foi explorado
          continue;
     
        visitado[u] = true;
     
        double custo;
        for(int j = 0; j < (int) LA[u].size(); j++)
        {
            pair<int, double> vizinho = LA[u][j];
            int v = vizinho.first;
            double prob = vizinho.second;
         
            // tentativa de melhorar a estimativa de menor caminho da origem ao vertice v
            custo = d[u] * prob;
            if(custo < d[v]) 
            { 
                d[v] = custo; 
                heap.push(make_pair(d[v], v)); 
            }
        }
    }
}

int main()
{
    cin >> n >> m;
   
    LA = new vector<pair<int, double>>[n];
    int u, v;
    double p;
    // Entrada das arestas do grafo
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v; 
        cin >> p;
        u--;
        v--;
        LA[u].push_back(make_pair(++v, p)); // Acrescentei "++" AQUI
    }
 
    int x = 0;

    for(int i = 0; i < m; i++)
    {
        
        cout << "vertice " << ++x << " para : ";
        for(int j = 0; j < (int) LA[i].size(); j++)
        {
            cout << LA[i][j].first << " (" << LA[i][j].second << ") ";
        }
        cout << endl;
    }

    dijkstra(0);
 
    for(int i = 0; i < n; i++)
      cout << "d[" << i + 1 << "]: " << d[i] << endl;

    return 0;
}