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
int kruskall(vector<pair<int, ii>> arestas, int n, int m, vector<int>& primeiraAgm)
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
            primeiraAgm.push_back(i); //Adiciona na primeira AGM
            resultado += e.first;
            numero_arestas++;
            if(numero_arestas == n-1)
              break;
         
            ufds.uniao(u, v);
        }
    }

    cout << "Primeira agm: " << endl;
    for(unsigned i=0; i<primeiraAgm.size();i++){
        cout << arestas[primeiraAgm[i]].second.first << "-" << arestas[primeiraAgm[i]].second.second << "->" << primeiraAgm[i] << " ";
    }
    cout << endl;

    return resultado;
}

// Sobrecarga da função
int kruskall(vector<pair<int, ii>> arestas, int n, int m, int ignorar)
{
    // ordenacao em O(mlogm), de acordo com https://www.cplusplus.com/reference/algorithm/sort/?kw=sort
    sort(arestas.begin(), arestas.end());
 
    // custo da AGM
    int resultado = 0;
 
    UFDS ufds(n); // codigo equivalente ao MAKE-SET(v) do pseudocodigo
 
    int u, v;
    pair<int, ii> e;
 
    int numero_arestas = 0;
    cout <<" ( ";
    for(int i = 0; i < m; i++)
    {
        e = arestas[i];
        u = e.second.first;
        v = e.second.second;
        if(!ufds.mesmoConjunto(u, v) and i != ignorar)
        {
            cout << arestas[i].first << " + ";
            resultado += e.first;
            numero_arestas++;
            if(numero_arestas == n-1)
              break;
         
            ufds.uniao(u, v);
        }
    }
    cout << " ) ";

    return resultado;
}

int getMenor(int arr[], int n){
    int menor = arr[0];
    for(int i=0; i<n; i++){
        if(arr[i]<menor){
            menor = arr[i];
        }
    }
    return menor;
}

int segundaMenorAgm(vector<pair<int, ii>> arestas2, int n, int m, vector<int> primeiraAgm){
    int segundaOpcoes[n-1];
    sort(arestas2.begin(), arestas2.end());

    cout << "Ignorando arestas: ";
    for(unsigned i=0; i<primeiraAgm.size(); i++){
        cout << arestas2[primeiraAgm[i]].second.first << "-" << arestas2[primeiraAgm[i]].second.second << "->" << primeiraAgm[i] << " ";
        segundaOpcoes[i] = kruskall(arestas2, n, m-1, primeiraAgm[i]);
    }

    cout << endl;

    cout << "Segundas opcoes: " << endl;
    for(int i=0; i<n-1;i++){
        cout << segundaOpcoes[i] << " ";
    }
    cout << endl;

    return getMenor(segundaOpcoes, n-1);
}

int main()
{
    // lista de arestas: compostos por uma tripla (peso, (u,v))
    vector<pair<int, ii>> arestas;  // Tem TODAS as arestas
    //lista para guardar o index das arestas da primeira AGM formada
    vector<int> primeiraAgm;   // Tem APENAS as que formar a AGM
    //Uma variável que indica o index da aresta que será ignorada
    //int ignorar = -1;
 
    int n, m; // numero de vertices e numero de arestas
    cin >> n >> m;
 
    int u, v, w; // extremos das arestas, e peso de cada aresta
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        arestas.push_back(make_pair(w, ii(u, v)));
    }

    // vector<pair<int, ii>> arestas2 = arestas;
 
    cout << "Custo da primeira AGM: " << kruskall(arestas, n, m, primeiraAgm) << endl;
    cout << "Custo da segunda AGM: " << segundaMenorAgm(arestas, n, m, primeiraAgm) << endl;
    return 0;
}
