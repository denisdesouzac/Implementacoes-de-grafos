/*
Dênis de Souza Cordeiro - 202110235 - 14A
Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
Ronald Souza Galdino - 202110679 - 14A
*/

// A ideia geral do algoritmo que normalmente é inserida aqui foi descrita no relatório :)

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define INF 10000000
#define NIL -1

vector<pair<int, int>>* adj;    // Lista de adjacência 
vector<int> caminhos;           // Vector usado para salvar os caminhos

/*
Função para registrar o caminho percorrido, faz isso através de uma recursão que vai "voltando" pela lista de pais
start = vértice incial 
end = vértice atual (onde estamos)
*/
void registrarCaminho(int start, int end, int pai[]){
    if(pai[start] != end){
        caminhos.push_back(pai[start]);
        registrarCaminho(pai[start], end, pai);
    }
    else{
        caminhos.push_back(end);
    }
}

// Função para realizar a remoção das arestas
// Recebe a ultima posição do vetor de caminhos e um vetor de pais
// Exclui o caminho até chegar ao pai da origem, ou seja quando pai[start] == -1 (vai voltando)
void removerArestas(int start, int pai[]){
    while(pai[start] != NIL){   //enquanto o pai da origem não for encontrado

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

// Função do algoritmo de Dijkstra 
/*
n = numero de vertices
s = vertice inicial
t = destino da busca ()
pai[] = vetor de pais
*/
int dijkstra(int n, int s, int t, int pai[]){

    // distância de cada vértice
    int dist[n];

    //vetor de vértices visitados
    bool visitados[n];

    //fila de prioridades (distancia, vértice)
    priority_queue < pair<int, int>,vector<pair<int, int> >, greater<pair<int, int> > > heap;

    // inicia o vetor de distâncias, visitados e de pais
    for(int i = 0; i < n; i++){
        dist[i] = INF;
        visitados[i] = false;
        pai[i] = NIL;
    }

    // distância da origem para origem é 0 
    dist[s] = 0;

    //Origem não tem pai
    pai[s] = NIL;

    //insere na fila de prioridades
    heap.push(make_pair(dist[s], s));

    //  enquanto a fila não for vazia
    while(!heap.empty()){

        pair<int, int> p = heap.top(); // pega do topo
        int u = p.second; // pega o vértice
        heap.pop(); // remove o vérticeda fila

        // verifica foi visitado
        if(visitados[u] == false){

            // marca como visitado
            visitados[u] = true;

            // percorre os vértices da lista de adj
            for(auto it = adj[u].begin(); it != adj[u].end(); it++){
                int v = it->first; // vértice adj
                int p = it->second; // custo 

                // relaxamento (u, v)
                if(dist[v] > (dist[u] + p) and visitados[v] == false){    //Adicioneu o "and" na condição.             
                    // atualiza a distância de "v" e insere na fila
                    dist[v] = dist[u] + p;
                    heap.push(make_pair(dist[v], v));
                    pai[v] = u; // atualiza o pai
                }
            }
        }
    }
    if(dist[t] != INF){     // verifica se a distância de t != INF, quer dizer que ele foi relaxado (temos caminho mais curto pra ele)
        caminhos.push_back(t);          // Insere inicialmente o vértice final
        registrarCaminho(t,s, pai);     // Chama a função para registrar esse MENOR CAMINHO
    }
    return dist[t]; // Retorna a distância do caminho mais curto
}

int main(){
    int n, m; // num de vértices e arestas
    int s, t; // origem e destino
    int u, v, p; //  pontos u e v da aresta com distância p

    cin >> n >> m;
    
    while(n != 0 and m != 0){

        cin >> s >> t;

        adj = new vector<pair<int, int> >[n];   // Instancia a Lista de Adjacência
        int pai[n];                             // Vetor com os respectivos pais de cada vértice

        // leitura do grafo
        for(int i = 0; i < m; i++){
            cin >> u >> v >> p;
            adj[u].push_back(make_pair(v, p));
        }

        int menor_caminho  = dijkstra(n,s,t,pai);   // Chama a função de Dijkstra

        // inversão do caminho (necessária para a remoção)
        reverse(caminhos.begin(), caminhos.end());

        //int aux1, aux2;
        int caminho2 = menor_caminho;
        
        if(caminho2 == INF){    // Se não temos menor caminho -> -1, pois sequer teremos caminho bom
            cout << -1 << endl;
        }
        else{
            while(caminho2 == menor_caminho){       // Enquanto esse menor caminho for igual, procura o "CAMINHO BOM"
                removerArestas(caminhos[0], pai);   // Função para remover esse caminho ( aqui é a chave )
                caminhos.clear();                   // Limpa o vector de caminhos, para nova busca (afinal, vamos achar novo caminho)
                caminho2 = dijkstra(n,s,t,pai);     // Chama a busca por um novo caminho
            }
        
            if(caminho2 != INF){ // verifica se foi achado um CAMINHO BOM
                cout <<caminho2 << endl;
            } 
            else{
                cout << -1 << endl;
            }
        }
        caminhos.clear();   // Limpa o vector de caminhos
        cin >> n >> m;
    }
    return 0;
}