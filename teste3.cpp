#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define INF 10000000
#define NIL -1

vector<pair<int, int> > * adj;
vector<int> caminhos;
vector<int> caminho2;

//Função para registrar o caminho percorrido
void registrarCaminho(int start, int end, int pai[]){
    //cout << "start : " << start << "end : "<< end << endl;
    if(pai[start] != end){
        //caminhos.push_back(pai[start]);
        caminhos.insert(caminhos.begin(), pai[start]);
        registrarCaminho(pai[start], end, pai);
    }
    else{
        caminhos.insert(caminhos.begin(), end);
    }
}

//Função para registrar o caminho percorrido
void registrarOutroCaminho(int start, int end, int pai[]){
    //cout << "start : " << start << "end : "<< end << endl;
    if(pai[start] != end){
        //caminhos.push_back(pai[start]);
        caminho2.insert(caminho2.begin(), pai[start]);
        registrarOutroCaminho(pai[start], end, pai);
    }
    else{
        caminho2.insert(caminho2.begin(), end);
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
        caminhos.push_back(t);
        registrarCaminho(t,s, pai);
    }
    return dist[t];
}

int dijkstra(int n, int s, int t, int verticeDeSaida, int verticeDeChegada){
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
        caminho2.push_back(t);
        registrarOutroCaminho(t,s, pai);
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

    // leitura do grafo
    for(int i = 0; i < m; i++){
        cin >> u >> v >> p;
        adj[u].push_back(make_pair(v, p));
    }

    cout << "Menor Caminho (R) : " << dijkstra(n,s,t) << endl;

    cout << "Tamanho do Caminho : " << caminhos.size() << endl;

    cout << "Caminho: ";
    for(int x : caminhos){
        cout << x << ' ';
    }
    cout << endl;

    // leitura do grafo
    for(int i = 0; i < caminho2.size() - 1; i++){
            dijkstra(n,s,t, i, i + 1);
    }

    cout << "Caminho2: ";
    for(int x : caminho2){
        cout << x << ' ';
    }    


    return 0;
}