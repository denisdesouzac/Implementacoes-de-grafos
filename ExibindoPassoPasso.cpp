#include<iostream>
#include<utility>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int, int> ii; // pares de inteiros
typedef vector<int> vi; // vetor de inteiros


class UFDS
{
    public:
      // construtor com parametro: n eh o numero de conjuntos disjuntos
      UFDS(int n)
      {
          rank.assign(n, 0);
          p.assign(n, 0);
          for(int i = 0; i < n; i++)                                                   // Problema tava aqui
            p[i] = i;
      }
 
      /* Dado um elemento do conjunto, busca-se seu pai no conjunto disjunto e o 
       * atualiza (se necessário) para o ancestral de maior nivel na arvore.
       *
       * Parametros
       * i: identificacao do elemento cujo o conjunto sera buscado.
       */
      int busca(int i)
      {
          if(p[i] == i)
              return i;
      
          p[i] = busca(p[i]);
          return p[i];
      }
 
      /* Dado dois elementos do conjunto, verifica-se se esses elementos possuem o
      * o mesmo pai na floresta disjunta.
      *
      * Parametros
      * i: um elemento qualquer.
      * j: um elemento qualquer.
      */
      bool mesmoConjunto(int i, int j)
      {
          return busca(i) == busca(j);
      }
 
      /* Dados dois elementos, une os seus respectivos conjuntos considerando o rank 
      * de maior valor (em caso de empate, o elemento de maio indice)
      *
      * Parametros
      * i: um elemento qualquer.
      * j: um elemento qualquer.
      */
      void uniao(int i, int j)
      {
          if(!mesmoConjunto(i, j))
          {
              int c1 = busca(i);
              int c2 = busca(j);
          
              if(rank[c1] > rank[c2])
                  p[c2] = c1;
          
              else
              {
                  p[c1] = c2;
                  if(rank[c1] == rank[c2])
                      rank[c2]++;
              }
          }
      }
 
      /* Imprime as informacoes de quais os elementos estao em cada conjunto.
      * Apresenta-se tambem o rank de cada elemento
      *
      * Parametros
      * p: vetor que armazena os pais de cada vertice no conjunto disjunto.
      * rank: vetor que armazena o rank de cada elemento do conjunto.
      * n: numero de elementos no conjunto
      */
      friend ostream &operator<<(ostream& saida, const UFDS& conjunto)
      {
          for(unsigned i = 0; i < conjunto.p.size(); i++)
            saida << i << ": p(" << conjunto.p[i] << "), rank(" << conjunto.rank[i] << ")";
          return saida;
      }
 
    private:
      // vetor que armazena os pais de cada vertice no conjunto disjunto
      vi p;
 
      // vetor que armazena o rank de cada elemento do conjunto
      vi rank;
};


/* retorna o custo da AGM
 * Parametros:
 *  arestas: lista da arestas
 *  n: quantidade de vertices
 *  m: quantidade de arestas
 */
int kruskall(vector<pair<int, ii>> arestas, int n, int m, vector<int>& primeiraAgm)
{
    primeiraAgm.clear();  // Tava esquecendo de começar de novo
    // ordenacao em O(mlogm), de acordo com https://www.cplusplus.com/reference/algorithm/sort/?kw=sort
    sort(arestas.begin(), arestas.end());
 
    // custo da AGM
    int resultado = 0;
 
    UFDS ufds(n+1); // codigo equivalente ao MAKE-SET(v) do pseudocodigo
 
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
 
    UFDS ufds(n+1); // codigo equivalente ao MAKE-SET(v) do pseudocodigo
 
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
        segundaOpcoes[i] = kruskall(arestas2, n, m, primeiraAgm[i]);
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

     int quantidadeDeTestes;
    cin >> quantidadeDeTestes;

     int n, m;
     int u, v, w;

    for(int contadorDeTestes = 0; contadorDeTestes < quantidadeDeTestes; contadorDeTestes++){
 
    // numero de vertices e numero de arestas
    cin >> n >> m;
 
     // extremos das arestas, e peso de cada aresta
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        arestas.push_back(make_pair(w, ii(u, v)));
    }

    // vector<pair<int, ii>> arestas2 = arestas;
 
    cout << "Custo da primeira AGM: " << kruskall(arestas, n, m, primeiraAgm) << endl;
    cout << "Custo da segunda AGM: " << segundaMenorAgm(arestas, n, m, primeiraAgm) << endl;
    }
    return 0;
}
