/*
Dênis de Souza Cordeiro - 202110235 - 14A
Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
Ronald Souza Galdino - 202110679 - 14A
*/

#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;

#define INF 10000000
#define NIL -1

vector<pair<int, int>>* adj;
vector<int> caminhos;

//Função para registrar o caminho percorrido
void registrarCaminho(int start, int end, int pai[]){
    if(pai[start] != end){
        caminhos.push_back(pai[start]);
        registrarCaminho(pai[start], end, pai);
    }
    else{
        caminhos.push_back(end);
    }
}

// Função para realizar a remoção das arestas de acordo como fornecido
void removerArestas(int start, int end, int pai[]){
    while(pai[start] != NIL){//enquanto o pai da origem não for encontrado

        for(int i = 0; i < int(adj[pai[start]].size()); i++){ // percorre as arestas que ligam cada vértice

            pair<int, int> aresta = adj[pai[start]][i];

            if(start == aresta.first){// se for igual
                adj[pai[start]].erase(adj[pai[start]].begin()+i); // removo a aresta da lista de adj
                start = pai[start];
                break;
            }
        }
    }
}

int dijkstra(int n, int s, int t, int pai[]){
    // vetor de distâncias
    int dist[n];

    //vetor de visitados serve para caso o vértice já tenha sido
    // expandido (visitado), não expandir mais
    bool visitados[n];

    // fila de prioridades de pair (distancia, vértice)
    priority_queue < pair<int, int>,vector<pair<int, int> >, greater<pair<int, int> > > heap;

    // inicia o vetor de distâncias, visitados e de pais
    for(int i = 0; i < n; i++){
        dist[i] = INF;
        visitados[i] = false;
        pai[i] = NIL;
    }

    // distância da origem para origem é 0 
    dist[s] = 0;

    //Origem é seu próprio Pai
    pai[s] = NIL;

    // insere na fila
    heap.push(make_pair(dist[s], s));

    // loop do algoritmo
    while(!heap.empty()){

        pair<int, int> p = heap.top(); // extrai o pair do topo
        int u = p.second; // obtém o vértice do pair
        heap.pop(); // remove da fila

        // verifica se o vértice não foi VISITADO
        if(visitados[u] == false){

            // marca como visitado
            visitados[u] = true;

            // percorre os vértices "v" adjacentes de "u"
            for(auto it = adj[u].begin(); it != adj[u].end(); it++){
                int v = it->first; // vértice adjacente
                int p = it->second; // custo da aresta

                // relaxamento (u, v)
                if(dist[v] > (dist[u] + p) and visitados[v] == false){    //Adicioneu o "and" na condição.             
                    // atualiza a distância de "v" e insere na fila
                    dist[v] = dist[u] + p;
                    heap.push(make_pair(dist[v], v));
                    pai[v] = u;
                    //cout << "pai de " << v << " : " << pai[v] << endl;
                }
            }
        }
    }
    if(dist[t] != INF){
        caminhos.push_back(t);
        registrarCaminho(t,s, pai);
    }
    return dist[t];
}

int main(){
    int n, m; // num de vértices e arestas
    int s, t; // origem e destino
    int u, v, p; //  pontos u e v da aresta com distância p

    cin >> n >> m;
     while(n != 0 and m != 0){
        cin >> s >> t;

        adj = new vector<pair<int, int> >[n];
        int pai[n];

        // leitura do grafo
        for(int i = 0; i < m; i++){
            cin >> u >> v >> p;
            adj[u].push_back(make_pair(v, p));
        }
        int menor_caminho  = dijkstra(n,s,t,pai);

        // inversão do caminho
        reverse(caminhos.begin(), caminhos.end());

        //int aux1, aux2;
        int caminho2 = menor_caminho;
        
        if(caminho2 == INF){
            cout << -1 << endl;
        }
        else{
            while(caminho2 == menor_caminho){
            for(int i = 0; i < int(caminhos.size()); i++){
                removerArestas(caminhos[i],caminhos[caminhos.size()], pai);
                break;
            }
            caminhos.clear();
            caminho2 = dijkstra(n,s,t,pai);
            }
       
            if(caminho2 != INF){ // verifica se foi achado um segundo caminho
                cout <<caminho2 << endl;
            } 
            else{
                cout << -1 << endl;
            }

        }

        caminhos.clear();

        cin >> n >> m;
    }
    return 0;
}