#include <iostream>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> ii; // pares de inteiros
typedef vector<int> vi; // vetor de inteiros
typedef vector<ii> vii; // vetor de pares de inteiros


// funcao que atualiza a fila de prioridades
void atualizaFila(int u, vector<vii> LA, priority_queue<ii> Q, vi explorado)
{
    explorado[u] = 1;
    for(unsigned j = 0; j < LA[u].size(); j++)
    {
        ii v = LA[u][j];
        if(!explorado[v.first])
          /* valor: peso; chave: id do vertice
           * o valor negativo se deve ao fato de
           * que a heap do C++ eh implementada como
           * uma heap-max, e para desempate, prioriza-se
           * aqui o id de menor indice
           */
          Q.push(ii(-v.second, -v.first)); 
    }
}

int prim(int n, priority_queue<ii> Q, vector<vii> LA, vi explorado)
{
    explorado.assign(n, 0);
    atualizaFila(0, LA, Q, explorado);
    
    // custo da AGM
    int resultado = 0;
 
    // peso de uma aresta em cada iteracao
    int w;
 
    while(!Q.empty())
    {
        ii u = Q.top(); // O(1)
        Q.pop(); // O(logn)

        int w = -u.first; // retirando o negativo cadastrado na heap
        int v = -u.second;
     
        if(explorado[v])
        {	
			cout << "W:" << w << endl;
            resultado += w;         
            atualizaFila(v, LA, Q, explorado); // O(logn)
        }
    }
 
	cout << "Resultado:" << resultado << endl;
    return resultado;
}

int main()
{
	// armazena a informacao se o vertice foi explorado ou nao
	vi explorado;

	// heap que armazena o vertices e suas prioridades a cada iteracao
	priority_queue<ii> Q;

	// lista de adjacencia
	vector<vii> LA;

	// numero de vertices
	int n;

	// numero de arestas
	int m;

    cin >> n >> m;
 
    for(int i = 0; i < n; i++)
    {
        vii lista;
        LA.push_back(lista);
    }
        
    int u, v, w; // extremos das arestas, e peso de cada aresta
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        int contador = 0, continua = 0;
        for(vector<vii>::iterator it = LA.begin(); it != LA.end() && continua < 2; ++it)
        {
          if(contador == u) 
          {
            ii par1(v, w);
            (*it).push_back(par1);    
            continua++;
          }
       
          else if(contador == v)
          {
            ii par2(u, w);
            (*it).push_back(par2);    
            continua++;
          }
          contador++;
      }
    }
 
    cout << "Custo da AGM: " << prim(n,Q, LA, explorado) << endl;
    return 0;
}
