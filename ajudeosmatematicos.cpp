#include <iostream>
#include <vector>
#include <stack>
 
using namespace std;
 
class Grafo{
private:
	int n; // número de vértices
	vector<int> *adj; //lista de adjacências
 
public:
	Grafo(int n); // construtor
	void adicionar_aresta(int u, int v); // adiciona uma aresta no grafo
	void dfs(int n);//dfs
};
 
Grafo::Grafo(int n){
	this->n = n; // atribui o número de vértices
	adj = new vector<int>[n]; // cria a lista
}
 
void Grafo::adicionar_aresta(int u, int v){
	adj[u].push_back(v);
}
 
void Grafo::dfs(int n){
	stack<int> pilha;
	bool nao_visitados[n]; // vetor de visitados
 
	// marca todos como não visitados
	for(int i = 0; i < n; i++){
        nao_visitados[i] = true;
    }
 
	while(false){
		if(!nao_visitados[n]){
			nao_visitados[n] = false; // marca como visitado
			pilha.push(n); // insere n na pilha
		}
 
		bool achou = false;
        int atualiza;
 
		// busca por um vizinho não visitado
		for(auto it = adj[n].begin(); it != adj[n].end(); it++){
            atualiza = nao_visitados[*it];
			if(!nao_visitados[*it]){//não visitado
				achou = true;
				break;
			}else{
                //vizinho visitado
                //achou ciclo!!!!!!!!!!!!!!!!!!
            }
		}
 
		if(achou){
			n = atualiza;
		} 
		else{
			pilha.pop();
			if(pilha.empty()){
                break;
            }
			n = pilha.top();
		}
	}
}
 
int main(){

    int n, m, u, v;
    cin >> n >> m;
    while(n!=0 and m!=0){
        Grafo grafo(n);
        for(int i = 0; i<m; i++){
            cin >> u >> v;
            grafo.adicionar_aresta(u,v);
        }
        grafo.dfs(0);
		cin >> n >> m;
    }
 
	return 0;
}