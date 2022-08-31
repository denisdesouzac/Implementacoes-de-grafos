#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

int** MA;
int* pai;
int* cor;
int nCiclos = 0;
vector<vector<int>> ciclos(10);

void registarCiclo(int comecar, int parar){
    cout << "to aqui";
    if(comecar >= parar){
        ciclos[nCiclos].push_back(comecar);
        registarCiclo(pai[comecar-1], parar);
    } 

}

void dfs(int start1, int n){
    cout << start1 << " -> ";
    cor[start1-1] = CINZA;

    // For every node of the graph
	for (int start2 = 1; start2 <= n; start2++) {

		// If some node is adjacent to the current node
		// and it has not already been visited
		if ( MA[start1-1][start2-1] >= 1 and (cor[start2-1] == BRANCO)){ 
            // Verificar se temos ciclos formados por arestas paralelas
            if( MA[start1-1][start2-1] > 1){
            nCiclos += (MA[start1-1][start2-1]/2);
            }
            pai[start2-1] = start1;
			dfs(start2, n);
		}
        else if( MA[start1-1][start2-1] >= 1 and (pai[start1-1] != start2) and ( cor[start2-1] == CINZA) ){
            //cout << endl <<"Achei um ciclo" << endl;
            //ciclos[0][nCiclos].push_back(start2);
            //registarCiclo(start1, start2);
            ciclos[nCiclos].push_back(start2);
            registarCiclo(start1, start2);
            nCiclos = nCiclos+1;
        }
	}
    //cout << endl << start1 << "foi fechado" << endl;
    cor[start1-1] = PRETO;
}

int main(){

    // Iniciação e Declaração das estruturas
    int n, m;
    cin >> n >> m;
    pai = new int[n];
    cor = new int[n];
    MA = new int*[n];   // Matriz de adj = Vetor de Vetores
    //ciclos = new vector<vector<int>>[n]; 
    

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
        
        // MA
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


    // cout << "Vetor pai: " << pai[0] << pai[1] << pai[2] << endl;
    // cout << "Vetor cor: " << cor[0] << cor[1] << cor[2] << endl;


    // Desalocação de memória
    delete[] pai;
    delete[] cor;

    for(int u = 0; u < n; u++){
        delete MA[u];
    }

    delete[] MA;

    return 0;
}