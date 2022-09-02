# include <iostream>
#include <vector>
using namespace std;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

int** MA;   // Matriz de Adjacência
int* pai;   // Array de pais de cada vértice
int* cor;   // Array de cores de cada vértice
vector<int> caminho;

void registrarCaminho(int x){
    if( pai[x-1] != -1){
        caminho.push_back(pai[x-1]);
        if( MA[x-1][pai[x-1]-1] > 1 ){
            MA[x-1][pai[x-1]-1]--;
            MA[pai[x-1]-1][x-1]--;
        }
        else{
            MA[x-1][pai[x-1]-1] = 0;
            MA[pai[x-1]-1][x-1] = 0;
        }

        registrarCaminho(pai[x-1]);
    }
}

/*
 Função da Busca em largura sendo realizada em uma Matiz, ela utiliza como referência um "start1" como sendo as LINHAS e um "start2" como COLUNAS,
 fazendo assim o caminhamento pela matriz e realizando uma BUSCA EM PROFUNDIDADE de maneira RECURSIVA.
 Ao encontrar com um número ">1" temos um ciclo composto de arestas paralelas.
 Ao encontrar com um vértice CINZA (já mapeado) temos um ciclo próprio e a função de registro é chamada.
*/
int dfs(int x, int n, int y, bool &result){
    if(result == true){
        return 0;
    }
    cor[x-1] = CINZA;  // Marcando o vértice atual como CINZA

	for (int start2 = 1; start2 <= n; start2++) {
		if( x == y and result == false){
            result = true;
            caminho.push_back(y);
            registrarCaminho(x);
        }
        // Caso para visitar o vizinho BRANCO
		else if ( MA[x-1][start2-1] >= 1 and (cor[start2-1] == BRANCO)){ 
            pai[start2-1] = x;
			dfs(start2, n, y, result);     // Chamada recursiva
		}
	}
    cor[x-1] = PRETO;  // "Fechamento" do vértice
    return 0;
}

//Função para remover o caminho da MA
void removerCaminho();

// Sobrecarga
int dfs(int x, int n, int y, int &result){
    if(result == 1){
        return 0;
    }
    cor[x-1] = CINZA;  // Marcando o vértice atual como CINZA

	for (int start2 = 1; start2 <= n; start2++) {
		if( x == y and result == 0){
            result = 1;
        }
        // Caso para visitar o vizinho BRANCO
		else if ( MA[x-1][start2-1] >= 1 and (cor[start2-1] == BRANCO)){ 
            pai[start2-1] = x;
			dfs(start2, n, y, result);     // Chamada recursiva
		}
	}
    cor[x-1] = PRETO;  // "Fechamento" do vértice
    return 0;
}


int main(){

    // Iniciação e Declaração das estruturas
    int n, m, x, y;
    cin >> n >> m;

    while(n != 0 and m != 0){

        pai = new int[n];
        cor = new int[n];
        MA = new int*[n];   // Matriz de adj = Vetor de Vetores

        bool result = false;
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

        cin >> x >> y;

        //Print DFS
        dfs(x,n, y, result);
        


        // Remover arestas de caminho da MA
        removerCaminho();

        // Dfs Again
        int result2 = 0;
        for(int i = 0; i < n; i++){
            pai[i] = -1;
            cor[i] = BRANCO;
        }
        dfs(x,n,y, result2);
        if(result2 == 1){
            cout << 1;
        }
        else{
            cout << 0;
        }
        
        delete[] pai;
        delete[] cor;

        for(int u = 0; u < n; u++){
            delete MA[u];
        }

        delete[] MA;

        cin >> n >> m;
    
    }

    return 0;
}