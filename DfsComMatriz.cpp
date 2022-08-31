#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

int** MA;   // Matriz de Adjacência
int* pai;   // Array de pais de cada vértice
int* cor;   // Array de cores de cada vértice
int nCiclos = 0;    // Contador para o número de ciclos encontrados
vector<vector<int>> ciclos(2); // Vector bidimensional para armazenar os ciclos

// Função para verificar quando há necessidade de redimensionar o Vector de Ciclos (adiciona 2 espaços por vez)
void checkResize(){ 
    if(nCiclos == 2){
        ciclos.resize(nCiclos+2);
    }
}

/* 
Função recursiva para registrar um ciclo encontrado (adiciona o vértice atual e vai "voltando" pelos pais até montar o ciclo, 
parando ao encontrar o vértice CINZA que declarou o encontro do ciclo. 
*/
void registarCiclo(int comecar, int parar){
    if(comecar >= parar){
        ciclos[nCiclos].push_back(comecar);
        registarCiclo(pai[comecar-1], parar);
    } 
}

/*
 Função da Busca em largura sendo realizada em uma Matiz, ela utiliza como referência um "start1" como sendo as LINHAS e um "start2" como COLUNAS,
 fazendo assim o caminhamento pela matriz e realizando uma BUSCA EM PROFUNDIDADE de maneira RECURSIVA.
 Ao encontrar com um número ">1" temos um ciclo composto de arestas paralelas.
 Ao encontrar com um vértice CINZA (já mapeado) temos um ciclo próprio e a função de registro é chamada.
*/
void dfs(int start1, int n){
    cout << start1 << " -> ";
    cor[start1-1] = CINZA;  // Marcando o vértice atual como CINZA

	for (int start2 = 1; start2 <= n; start2++) {
		// Caso para visitar o vizinho BRANCO
		if ( MA[start1-1][start2-1] >= 1 and (cor[start2-1] == BRANCO)){ 
            // Verificar se temos ciclos formados por arestas paralelas (caso haja, o ciclo é montado diretamente aqui)
            if( MA[start1-1][start2-1] > 1){
                ciclos[nCiclos].push_back(start2);
                ciclos[nCiclos].push_back(start1);
                ciclos[nCiclos].push_back(start2);
                nCiclos += (MA[start1-1][start2-1]/2); // Operação para ver QUANTOS ciclos são (considerando que podemos ter mais de 2 arestas paralelas)
                checkResize(); // Verificação de redimensionamento
            }
            pai[start2-1] = start1;
			dfs(start2, n);     // Chamada recursiva
		}
        // Caso onde temos um ciclo PRÓPRIO
        else if( MA[start1-1][start2-1] >= 1 and (pai[start1-1] != start2) and ( cor[start2-1] == CINZA) ){
            ciclos[nCiclos].push_back(start2);
            registarCiclo(start1, start2);  // Chamada da função para registar esse ciclo
            nCiclos = nCiclos+1;
            checkResize();  // Verificação de redimensionamento
        }
	}
    cor[start1-1] = PRETO;  // "Fechamento" do vértice
}

int main(){

    // Iniciação e Declaração das estruturas
    int n, m;
    cin >> n >> m;
    pai = new int[n];
    cor = new int[n];
    MA = new int*[n];   // Matriz de adj = Vetor de Vetores
    

    // Aloca os outros vetores e ajusa o estado inicial da matriz
    for(int i = 0; i < n; i++){
        MA[i] = new int[n];
        // Preenche a matriz com Zeros
        for(int j = 0; j < n; j++){
            MA[i][j] = 0;
        }
        pai[i] = -1;
        cor[i] = BRANCO;
    }

    // leitura do grafo
    int u, v;
    for(int i = 1; i <= m; i++){
        cin >> u >> v; // lendo as arestas do grafo
        
        // MA (insere a quantiade necessária de arestas)
        MA[u-1][v-1]++;
        MA[v-1][u-1]++;
    }
    
    //Print MatAdj
    for(int u = 0; u < n; u++){
        for(int v = 0; v < n; v++){
            cout << "**" << MA[u][v]  << "**" << " /pai: " << pai[u] << " cor: " << cor[u] << "/ ";
        }
        cout << endl;
    }

    //Print DFS
    cout << endl;
    dfs(1,n);
    cout << endl;
    cout << "nCIclos: " << nCiclos << endl;

    //Print MatAdj
    for(int u = 0; u < n; u++){
        for(int v = 0; v < n; v++){
            cout << "**" << MA[u][v]  << "**" << " /pai: " << pai[u] << " cor: " << cor[u] << "/ ";
        }
        cout << endl;
    }

    //Print Ciclos
    for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
            cout << " " << ciclos[u][v]  << " ";
        }
        cout << endl;
    }


    // Desalocação de memória
    delete[] pai;
    delete[] cor;

    for(int u = 0; u < n; u++){
        delete MA[u];
    }

    delete[] MA;

    return 0;
}