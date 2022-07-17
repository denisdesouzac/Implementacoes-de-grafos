#include "definicoes.h"
#include "ufds.h"

#include<iostream>
#include<algorithm>
using namespace std;

/* retorna o custo da AGM
 * Parametros:
 *  arestas: lista da arestas
 *  n: quantidade de vertices
 *  m: quantidade de arestas
 */
int kruskall(vector<pair<int, ii>>& arestas, int n, int m)
{
    // ordenacao em O(mlogm), de acordo com https://www.cplusplus.com/reference/algorithm/sort/?kw=sort
    sort(arestas.begin(), arestas.end());
 
    // custo da AGM
    int resultado = 0;
 
    UFDS ufds(n); // codigo equivalente ao MAKE-SET(v) do pseudocodigo
 
    int u, v;
    pair<int, ii> e;
 
    int numero_arestas = 0;
    for(int i = 0; i < m; i++)
    {
        e = arestas[i];
        u = e.second.first;
        v = e.second.second;
        if(!ufds.mesmoConjunto(u, v))
        {
            resultado += e.first;
            numero_arestas++;
            if(numero_arestas == n-1)
              break;
         
            ufds.uniao(u, v);
        }
    }
 
    return resultado;
}

int main()
{
    // lista de arestas: compostos por uma tripla (peso, (u,v))
    vector<pair<int, ii>> arestas;
    
    int quantidadeDeTestes;
    cin >> quantidadeDeTestes;

    for(int contadorDeTestes = 0; contadorDeTestes < quantidadeDeTestes; contadorDeTestes++){

        int quantPontosPrincipais, quantLigacoes; // numero de vertices e numero de arestas
        cin >> quantPontosPrincipais >> quantLigacoes;
        
        int u, v, w; // extremos das arestas, e peso de cada aresta
        for(int i = 0; i < quantLigacoes; i++)
        {
            cin >> u >> v >> w;
            arestas.push_back(make_pair(w, ii(u, v)));
        }

        int geradoraMinima = kruskall(arestas, quantPontosPrincipais, quantLigacoes);
    
        cout << geradoraMinima << endl;
    }

    return 0;
}