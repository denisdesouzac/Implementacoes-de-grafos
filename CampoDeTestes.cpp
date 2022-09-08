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
vector<pair<int, int>>* caminhos2;

//Função para registrar o caminho percorrido
void registrarCaminho(int start, int end, int pai[]){
    //cout << "start : " << start << "end : "<< end << endl;
    if(start != end){
        caminhos.push_back(start);
        caminhos.push_back(pai[start]);
        //caminhos2[0].push_back(make_pair( pai[start], start));
        registrarCaminho(pai[start], end, pai);
    }
}

// Função para realizar a remoção das arestas de acordo como fornecido
void removerArestas(int n){
    for(int i = 0; i < n; i++){
        for(auto it = adj[i].begin(); it != adj[i].end(); it++){
            cout << "**" <<it->first << "** Peso: " << it->second << " / ";
        }
        cout << endl;
    }

}

int dijkstra(int n, int s, int t){
    // vetor de distâncias
    int dist[n];

    //vetor de visitados serve para caso o vértice já tenha sido
    // expandido (visitado), não expandir mais
    bool visitados[n];

    // vetor de pais
    int pai[n];

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
    pai[s] = 0;

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
        //cout << t << s << endl;
        //caminhos.push_back(t);
        registrarCaminho(t,s, pai);
        //excluirCaminho();
    }
    return dist[t];
}

int main(){
    int n, m; // num de vértices e arestas
    int s, t; // origem e destino
    int u, v, p; //  pontos u e v da aresta com distância p

    cin >> n >> m;
    cin >> s >> t;

    adj = new vector<pair<int, int> >[n];
    //caminhos2 = new vector<pair<int, int> >[n];

    // leitura do grafo
    for(int i = 0; i < m; i++){
        cin >> u >> v >> p;
        adj[u].push_back(make_pair(v, p));
    }

    cout << "Menor Caminho (R) : " << dijkstra(n,s,t) << endl;

    cout << "Tamanho do Caminho : " << caminhos.size() << endl;

    // inversão do caminho
    reverse(caminhos.begin(), caminhos.end());

    // Print do Vector de Caminhos
    cout << "Caminho: ";
    for(int x : caminhos){
        cout << x << ' ';
    }

    /* // Print do Vector de Caminhos2
    cout << "Caminho: ";
    for(pair<int,int> x : caminhos2[0]){
        cout << x.first << ' ' << x.second << ' ';
    } */

    // Print da LA
    cout << endl << "L.A : " << endl;

    for(int i = 0; i< n; i++){
        cout << "Vértice " << i << " : ";
        for(auto it = adj[i].begin(); it != adj[i].end(); it++){
            cout << "**" <<it->first << "** Peso: " << it->second << " / ";
        }
        cout << endl;
    }

    /* //teste de como apagar da LA
    adj[1].erase(adj[1].begin()+1);

    // Print da LA
    cout << endl << "L.A : " << endl;

    for(int i = 0; i< n; i++){
        cout << "Vértice " << i << " : ";
        for(auto it = adj[i].begin(); it != adj[i].end(); it++){
            cout << "**" <<it->first << "** Peso: " << it->second << " / ";
        }
        cout << endl;
    } */



    /* // Print do vector de caminhos
    for(auto it = caminhos.begin(); it != caminhos.end(); it++){
        cout << *it << " ";
    } */

    //removerArestas();

    caminhos.clear();

    return 0;
}