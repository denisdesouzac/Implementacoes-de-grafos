/*
	Dênis de Souza Cordeiro - 202110235 - 14A
    Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
    Ronald de Souza Galdino - 202110679 - 14A
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

// cores dos vertices
#define BRANCO 0 // vertice nao descoberto
#define CINZA 1 // vertice descoberto
#define PRETO 2 // vertice fechado

int main()
{  
	int contador = 0; // Contador para as impressões dos casos teste

	while(true)
	{
		int n; // Arestas (cidades)
		int m; // Vertices (estradas)
		int l; // Ponto inicial
		int p; // Max de pedagios
		
		contador++;

		cin >> n >> m >> l >> p;

		if( (n and m and m and l and p) == 0){  // Terminar o programa com a entrada "0 0 0 0"
			return 0;
		}

		// alocando as estruturas auxiliares
		int* dist = new int[n+1]; // distancia de todos os vertices em relacao a origem s
		int* pai = new int[n+1]; // armazena o pai de cada vertice
		int* cor = new int[n+1]; // armazena a cor de cada vertice
		
		// iniciando as estruturas auxiliares
		for(int i = 1; i <= n; i++)
		{
			dist[i] = 0;
			pai[i] = -1;
			cor[i] = BRANCO;
		}

		vector<int>* lista_adj = new vector<int>[n+1];

		// leitura do grafo
		int u, v;
		for(int i = 0; i < m; i++)
		{
			cin >> u >> v; // lendo as arestas do grafo

			// evitando a leitura de vertices repetidos nas listas
			if(find(lista_adj[u].begin(), lista_adj[u].end(), v) != lista_adj[u].end())
			{
				continue;
			}

			// grafo nao-orientado
			lista_adj[u].push_back(v); //u -> v
			lista_adj[v].push_back(u); //v -> u
		}

		int s = l; // vertice origem é o l
		queue<int> fila; // fila de vertices a serem explorados na BFS
		fila.push(s);     // Empilha esse V "origem"
		cor[s] = CINZA;  // Marca ele como já mapeado

		cout << "Teste " << contador << endl;

		vector <int> opcoes; // Vector com as opcoes de viagem
		int distMax = 0; // Contador da distância max percorrida (Funciona para uma busca em largura, pois sempre vai buscar os vizinhos com mesma distância (primeiro os com Dist = 1, em seguida Dist = 2, ....))

		while(distMax <= p and !fila.empty() ) // Enquando a distância dos vizinhos ainda estiver dentro do estipulado em "p" e a Fila não estiver vazia
		{
			int u = fila.front(); // u será igual o primeiro da Fila 
			fila.pop(); // Tira esse primeiro da fila 
			cor[u]= PRETO; // Marca como já visitado 


			for(auto it = lista_adj[u].begin(); it != lista_adj[u].end(); it++) // Vai percorrer toda a L.Adj dessa origam
			{ 
				// se o vertice ainda nao foi descoberto (apenas os outros que estão brancos).
				if(cor[*it] == BRANCO)
				{
					cor[*it] = CINZA; // Vizinhos já mapeados são cinzas
					pai[*it] = u;   // Pai desses mapeados agora é o u
					dist[*it] = dist[u] + 1;  // Setta a distância deles
					fila.push(*it); // Enfileira esse vizinho
					distMax = dist[*it]; // Setta a distância máxima
					if(distMax <= p){
						opcoes.push_back(*it); // Coloca esse vizinho no VECTOR de opcoes de viagem (somente se sua distância estiver dentro do valor de "p")
					}
				}
			}
		}

		// Coloca em ordem crescente a saída, e imprime as opções de viagem
		sort(opcoes.begin(), opcoes.end());
		for(auto it = opcoes.begin(); it != opcoes.end(); it++){
			cout << *it << ' ';
		}

		cout << endl << endl;

		delete[] pai;
		delete[] cor;
		delete[] dist;
	}

return 0;
}