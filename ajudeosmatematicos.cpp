#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

int** MA;// matriz de adj
int* pai;// vetor com o pai de cada vértice
int* cor;// vetor com a cor de cada vértice
int nCiclos;// num de ciclos do grafo
//bool possui_subgrafo; // booleano que indica se o grafo possui um subgrafo EW
vector<vector<int>> ciclos(100);// vector que armazena os ciclos contidos no grafo

//método para guardar os ciclos achados no vector
void registarCiclo(int comecar, int parar){
   // cout << "to aqui";
    if(comecar >= parar){
        ciclos[nCiclos].push_back(comecar);
        registarCiclo(pai[comecar-1], parar);
    } 

}

//Busca em profunfidade
void dfs(int start1, int n){
    //cout << start1 << " -> ";
    cor[start1-1] = CINZA;

    // For every node of the graph
	for (int start2 = 1; start2 <= n; start2++) {

		// If some node is adjacent to the current node
		// and it has not already been visited
		if ( MA[start1-1][start2-1] >= 1 and (cor[start2-1] == BRANCO)){ 
            // Verificar se temos ciclos formados por arestas paralelas
            if( MA[start1-1][start2-1] > 1){
            nCiclos += (MA[start1-1][start2-1]/2);
            //cout << "MA:" << MA[start1-1][start2-1] << endl;
           // cout << "START1:"<<start1<<" "<<"START2:"<< start2<<endl;
            ciclos[nCiclos-1].push_back(start1);
            ciclos[nCiclos-1].push_back(start2);
            ciclos[nCiclos-1].push_back(start1);
            }
            pai[start2-1] = start1;
			dfs(start2, n);
		}
        else if( MA[start1-1][start2-1] >= 1 and (pai[start1-1] != start2) and ( cor[start2-1] == CINZA) ){
            ciclos[nCiclos].push_back(start2);
            registarCiclo(start1, start2);
            nCiclos = nCiclos+1;
        }
	}
    //cout << endl << start1 << "foi fechado" << endl;
    cor[start1-1] = PRETO;
}

// verifica se dois ciclos quaisquer Ci e Cj, i,j=1,...,k, i != j, não possuem arestas em comum.
bool verifica_arestas(){
    for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
            for(int x = u+1; x < nCiclos; x++){
                for(int z = 0; z < ciclos[x].size(); z++){
                    if(u == x and v == z) {
                        cout << "achei arestas em comum.";
                        cout << u << " " << x << "  " << v << " " << z << endl;
                        return false;
                    }else  if(u == z and v == x) {
                        cout << "achei arestas em comum.";
                        cout << u << " " << z << "  " << v << " " << x << endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

//verifica se existe exatamente um vértice em comum entre dois ciclos adjacentes Ci e Cj, com 1 <= i,j <= k.
/*bool existe_1_vcomum(){
    
}

// verifica se ciclos que não-adjacentes não possuem vértices em comum.
bool n_vcomum(){

}

// verifica se um vértice aparece em um ciclo no máximo uma vez.
bool v_ap_1vez(){

}*/

void imprime_n(){
    cout << "0" << endl;
}

void imprime_s(){
    cout << "1" << endl;
}

int main(){

    // Iniciação e Declaração das estruturas
    int n, m;
    cin >> n >> m;
    pai = new int[n];
    cor = new int[n];
    MA = new int*[n];
   // possui_subgrafo = false;
    

    // Aloca os outros vetores e ajusta o estado inicial da matriz
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
   
    nCiclos = 0;
    //Print DFS
    //cout << endl;
    dfs(1,n);
    //cout << endl;
    cout << "nCIclos: " << nCiclos << endl;

    int x,y;
    cin>> x >> y;

    bool tem_x = false;
    bool tem_y = false;

    // verifica se x pertence a c1 e se y pertence a ck
    for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
             if (x == ciclos[u][v]){
                tem_x = true;
                for(int x = u; x < nCiclos; x++){
                    for(int z = 0; z < ciclos[x].size(); z++){
                        if (y == ciclos[x][z]){
                            tem_y = true;
                            z = ciclos[x].size();
                            x = nCiclos;
                            v = ciclos[u].size();
                            u = nCiclos;
                        }
                    }
                }
            }
        }
    }

    cout << tem_x << " " << tem_y << endl;

    if((!tem_x) or (!tem_y)){
       imprime_n();
    }else{
        if(verifica_arestas()) imprime_s();
        //else if(existe_1_vcomum()) imprime_s();
        //else if(n_vcomum()) imprime_s();
       // else if(v_ap_1vez()) imprime_s();
        else{
            imprime_n();
        }
    }

    //limpando o vector de ciclos
    ciclos.clear();
    // Desalocação de memória
    delete[] pai;
    delete[] cor;
    for(int u = 0; u < n; u++){
        delete MA[u];
    }
    delete[] MA;

    return 0;
}