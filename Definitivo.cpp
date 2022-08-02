/* 

Dênis de Souza Cordeiro - 202110235 - 14A
Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
Ronald Souza Galdino - 202110679 - 14A


Lógica de nosso programa: 
A ideia é basicamente que o 1° algoritmo de Kruskall "crie" (na verdade ele só manipula por referência) um VECTOR registrando as arestas
pertencentes à primeira AGM (rodando kruskall normalmente e anotando o Index referente à posição das arestas na Lista de arestas). Em seguida, é chamado o 2° algoritmo 
de kruskall, um pouco diferente do primeiro, ao invés de "criar" um VECTOR com as arestas que compoêm uma AGM, ele apenas recebe como parâmetro uma aresta por vez da 
primeira AGM (proveninente do Vector do 1° algoritmo de kruskall), e a considera como a ser "IGNORADA" agora na composição da segunda AGM (assim garantindo que teremos
uma segunda melhor opção de AGM), e como esse 2° algoritmo é rodado diversas vezes (até "ignorar" todas as arestas da primeira AGM), ele armazena num simples ARRAY a 
soma dos valores das arestas de cada segunda melhor AGM encontrada e depois extrai a menor delas, resultando na SEGUNDA MELHOR AGM para o grafo.

*/

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
        for(int i = 0; i < n; i++)                                                   
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
int kruskall(vector<pair<int, ii>> arestas, int n, int m, vector<int>& primeiraAgm)     // Inserçao de um VECTOR "primeiraAgm" para registrar o Index das arestas que compoõem a primeira AGM.
{
    primeiraAgm.clear();    // Realizar a limpeza a cada nova busca por uma primeira AGM (afinal, usamos uma passagem por referência e não queremos que o grafo anterior interfira no NOVO).

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
            primeiraAgm.push_back(i);               //Adiciona no VECTOR "primeiraAgm" o Index dessa aresta que será unida no Disjoint-Set (quer dizer que ela compõe a primeira AGM).
            resultado += e.first;
            numero_arestas++;
            if(numero_arestas == n-1)
                break;
        
            ufds.uniao(u, v);
        }
    }

    return resultado;
}

// Sobrecarga do algoritmo de Kruskall (esse é o segundo, que recebe uma aresta a ser "ignorada" por vez).
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
    for(int i = 0; i < m; i++)
    {
        e = arestas[i];
        u = e.second.first;
        v = e.second.second;
        if(!ufds.mesmoConjunto(u, v) and i != ignorar)      // "and" usado para garantir que não estamos considerando a aresta recebida como "ignorada", para procurarmos AG diferentes da primeira.
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

// Função que retorna o MENOR valor presente no array de segundas opções de AGM (array que armazena apenas o somatório do valor das arestas de cada opção para AGM).
// Variável "x" usada para assegurar os casos onde temos uma árvore como grafo.
int getMenor(int arr[], int n, int limite){
    int menor = arr[0];
    bool x = false;
    for(int i=0; i<n; i++){
        if(arr[i]<=menor and arr[i]>=limite){
            menor = arr[i];
            x = true;
        }
    }
    if(x == false){
        return limite;
    }
    return menor;
}

/*

Função que constitui o processo para encontrar a SEGUNDA MELHOR AGM ( declara o array com as segundas opções, faz novamente um ".sort()" na Lista de Arestas, chama diversas vezes o 2° algoritmo
de Kruskall (passando como parâmetro o Index da aresta a ser ignorada,proveniente do VECTOR da primeira AGM), e ainda estabelece como "limite" o valor do somatório das aresta a primeira AGM ( para 
caso tenhamos a ocorrência de um grafo onde temos PONTES presentes na primeira AGM, o que inviabiliza o "caminhamento" do algoritmo de Kruskall, resultando em uma 2° AGM < 1° AGM, o que é incoerente).

*/ 
int segundaMenorAgm(vector<pair<int, ii>> arestas2, int n, int m, vector<int> primeiraAgm){
    int segundaOpcoes[n-1];
    sort(arestas2.begin(), arestas2.end());

    for(unsigned i=0; i<primeiraAgm.size(); i++){
        segundaOpcoes[i] = kruskall(arestas2, n, m, primeiraAgm[i]);
    }

    int limite = 0;

    for(unsigned i = 0; i<primeiraAgm.size(); i++){
        limite = limite + arestas2[primeiraAgm[i]].first;
    }

    return getMenor(segundaOpcoes, n-1, limite);
}

// _____________________________________________________________________________________________________________________________

int main()
{
    // lista de arestas: compostos por uma tripla (peso, (u,v))
    vector<pair<int, ii>> arestas;
    //lista para guardar o index das arestas da primeira AGM formada
    vector<int> primeiraAgm;   // Tem APENAS as que formam a AGM
    
    int quantidadeDeTestes;
    cin >> quantidadeDeTestes;


        for(int contadorDeTestes = 0; contadorDeTestes < quantidadeDeTestes; contadorDeTestes++){

            int n, m; // numero de vertices e numero de arestas
            cin >> n >> m;

            int u, v, w; // extremos das arestas, e peso de cada aresta
            for(int i = 0; i < m; i++)
            {
                cin >> u >> v >> w;
                arestas.push_back(make_pair(w, ii(u, v)));
            }

            cout << kruskall(arestas, n, m, primeiraAgm) << " " << segundaMenorAgm(arestas, n, m, primeiraAgm)<< endl;

            primeiraAgm.clear();
            arestas.clear();                
        }
    return 0;
}