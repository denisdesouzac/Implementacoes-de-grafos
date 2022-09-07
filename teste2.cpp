#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<pair<int, int> > * adj;

int dijkstra(int n, int s, int t){
    // vetor de distâncias
    int dist[n];

    //vetor de visitados serve para caso o vértice já tenha sido
    // expandido (visitado), não expandir mais
    bool visitados[n];

    // fila de prioridades de pair (distancia, vértice)
    priority_queue < pair<int, int>,vector<pair<int, int> >, greater<pair<int, int> > > heap;

    // inicia o vetor de distâncias e visitados
    for(int i = 0; i < n; i++){
        dist[i] = 10000000;
        visitados[i] = false;
    }

    // distância da origem para origem é 0
    dist[s] = 0;

    // insere na fila
    heap.push(make_pair(dist[s], s));

    // loop do algoritmo
    while(!heap.empty()){

        pair<int, int> p = heap.top(); // extrai o pair do topo
        int u = p.second; // obtém o vértice do pair
        heap.pop(); // remove da fila

        // verifica se o vértice não foi expandido
        if(visitados[u] == false){

            // marca como visitado
            visitados[u] = true;

            // percorre os vértices "v" adjacentes de "u"
            for(auto it = adj[u].begin(); it != adj[u].end(); it++){
                int v = it->first; // vértice adjacente
                int p = it->second; // custo da aresta

                // relaxamento (u, v)
                if(dist[v] > (dist[u] + p)){                    
                    // atualiza a distância de "v" e insere na fila
                    dist[v] = dist[u] + p;
                    heap.push(make_pair(dist[v], v));
                }
            }
        }
    }
    return dist[t];
}

int main(){
    int n, m; // num de vértices e arestas
    int s, t; // origem e destino
    int u, v, p; //  pontos u e v com distância p

    cin >> n >> m;
    cin >> s >> t;

    adj = new vector<pair<int, int> >[n];

    // leitura do grafo
    for(int i = 0; i < m; i++){
        cin >> u >> v >> p;
        adj[u].push_back(make_pair(v, p));
    }

    cout << dijkstra(n,s,t) << endl;

    return 0;
}