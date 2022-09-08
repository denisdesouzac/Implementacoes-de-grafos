#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<algorithm>
using namespace std;

#define INF 10000000
#define NIL -1

vector<pair<int, int> > * adj;
vector<int> caminhos;
int pai[0];
//vector<pair<int, int>>* caminhos2;

//Função para registrar o caminho percorrido
void registrarCaminho(int start, int end){
    //cout << "start : " << start << "end : "<< end << endl;
    if(pai[start] != end){
        caminhos.push_back(pai[start]);
        //caminhos2[0].push_back(make_pair( pai[start], start));
        registrarCaminho(pai[start], end);
    }
    else{
        caminhos.push_back(end);
    }
}

// Função para realizar a remoção das arestas de acordo como fornecido
void removerArestas(int start, int end){
    while(pai[end] != NIL){//enquanto o pai da origem não for encontrado
        cout << "cheguei no while" << endl;
        for(unsigned i = 0; i < adj[pai[end]].size(); i++){ // percorre as arestas que ligam cada vértice
             cout << "cheguei no for" << endl;
            pair<int, int> aresta = adj[pai[end]][i];
            if(end == aresta.first){// se for igual
                 cout << "cheguei no if" << endl;
                 cout << "end e aresta" << end << " " << aresta.first << endl;
                adj[pai[end]].erase(adj[pai[end]].begin()+i); // removo a aresta da lista de adj
                end = pai[end];
                break;
            }
        }
    }
}

int dijkstra(int n, int s, int t){
    // vetor de distâncias
    int dist[n];

    //vetor de visitados serve para caso o vértice já tenha sido
    // expandido (visitado), não expandir mais
    bool visitados[n];

    // vetor de pais
    pai[n];

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
        //cout << t << s << endl;
        caminhos.push_back(t);
        registrarCaminho(t,s);
       // removerArestas(t,s,pai);
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
    int menor_caminho  = dijkstra(n,s,t);

    cout << "Menor Caminho (R) : " << menor_caminho << endl;

    cout << "Tamanho do Caminho : " << caminhos.size() << endl;

    // inversão do caminho
    reverse(caminhos.begin(), caminhos.end());

    // Print do Vector de Caminhos
    cout << "Caminho: ";
    for(int x : caminhos){
        cout << x << ' ';
    }

     cout << endl << "L.A antes: " << endl;

    for(int i = 0; i< n; i++){
        cout << "Vértice " << i << " : ";
        for(auto it = adj[i].begin(); it != adj[i].end(); it++){
            cout << "**" <<it->first << "** Peso: " << it->second << " / ";
        }
        cout << endl;
    }

    int caminho2 = menor_caminho;
    for(int i = 0; i < caminhos.size(); i++){
        if(caminho2 == menor_caminho and i < caminhos.size()-1){
            removerArestas(caminhos[i],caminhos[i+1]);
            caminho2 = dijkstra(n,s,t);
        }
    }

    cout << "Segundo menor caminho: ";
    if(caminho2 != INF){ // verifica se foi achado um segundo caminho
        cout << caminho2 << endl;
    } else{
        cout << -1 << endl;
    }
     cout << endl << "L.A depois: " << endl;

    for(int i = 0; i< n; i++){
        cout << "Vértice " << i << " : ";
        for(auto it = adj[i].begin(); it != adj[i].end(); it++){
            cout << "**" <<it->first << "** Peso: " << it->second << " / ";
        }
        cout << endl;
    }
    caminhos.clear();

    return 0;
}