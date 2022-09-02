/*
Dênis de Souza Cordeiro - 202110235 - 14A
Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
Ronald Souza Galdino - 202110679 - 14A
*/

/*
Ideia do algoritmo:
Nosso algoritmo consiste na realização de 2 BUSCAS EM PROFUNDIDADE consecutivas na intenção de encontrar o SUBGRAFO EW entre X e
Y apresentado na descrição do problema. Quando a PRIMEIRA busca é realizada, o caminho que foi percorrido no grafo é REMOVIDO
da MATRIZ DE ADJACÊNCIA (através do decremento dos índices) e uma SEGUNDA busca em profundidade é chamada, esta por sua vez
não REMOVE do grafo o caminho que foi percorrido (pois não é necessário, afinal só percorreremos a matriz 2 vezes e a descartamos)
ela apenas verifica se, mesmo com a remoção do caminho anterior, ainda temos como chegar de X à Y.

Essa implementação funciona pois a ideia é que como temos 2 formas diferentes de percorrer e encontrar um caminho de X até Y
significa que: temos CICLOS conectados por vértices comuns e/ou Temos CICLOS de arestas paralelas formando o CAMINHO entre X e Y.
Caso não seja possível fazer os 2 percorrimentos pelo GRAFO, significa que: Não temos CICLOS conectados por vértices comuns e/ou
CICLOS de arestas paralelas formando um caminho entre X e Y, JUSTAMENTE PORQUE se conseguimos ir de X a Y UMA vez e APAGAMOS
esse caminho gerado, MAS AINDA ASSIM conseguimos ir de X a Y NOVAMENTE, temos o SUBGRAFO EW descrito (com ligação de X a Y através
de ciclos conectados por vértices comuns).  
*/

# include <iostream>
#include <vector>
using namespace std;

#define BRANCO 0
#define CINZA 1
#define PRETO 2

int** MA;   // Matriz de Adjacência
int* pai;   // Array de pais de cada vértice
int* cor;   // Array de cores de cada vértice

/*
Função para realizar o "Registro" do caminho percorrido pela busca em profundidade (que nada mais é do que decrementar os índices da MA
de acordo com os vértices que foram caminhados), faz isso através de uma chamada recursiva que retorna pelos PAIS dos vértices até encontrar
o ponto inicial da busca.

x = ponto onde está o percorrimento da DFS (esatrá no final se encontrar)
stop = pai do vértice que foi dado como ponto inicial da busca (condição de parada)
*/
void registrarCaminho(int x, int stop){
    if( pai[x-1] != stop){
        if( MA[x-1][pai[x-1]-1] > 1 ){
            MA[x-1][pai[x-1]-1]--;
            MA[pai[x-1]-1][x-1]--;
        }
        else{
            MA[x-1][pai[x-1]-1] = 0;
            MA[pai[x-1]-1][x-1] = 0;
        }
        registrarCaminho(pai[x-1], stop);
    }
}

/*
 Função da Busca sendo realizada em uma Matiz de ADJACÊNCIA, ela utiliza como referência uma posição INICIAL X 
 e uma FINAL (alvo da busca) Y, fazendo assim o caminhamento pela matriz e realizando uma BUSCA EM PROFUNDIDADE de maneira RECURSIVA.

 x = ponto onde está o atual percorrimento da busca
 start2 = auxiliar para percorrimento da MA
 y = alvo da busca
 result = booleano para registrar o REAL retorno da função (se tivemos sucesso na busca ou não)
 stop = pai do vértice que deu início à busca (usado na função "registrarCaminho(x,stop)")

*/
int dfs(int x, int n, int y, bool &result, int stop){
    if(result == true){
        return 0;
    }
    cor[x-1] = CINZA;  // Marcando o vértice atual como CINZA

	for (int start2 = 1; start2 <= n; start2++) {
		if( x == y and result == false){
            result = true;
            registrarCaminho(x, stop);
        }
        // Caso para visitar o vizinho BRANCO
		else if ( MA[x-1][start2-1] >= 1 and (cor[start2-1] == BRANCO)){ 
            pai[start2-1] = x;
			dfs(start2, n, y, result, stop);     // Chamada recursiva
		}
	}
    cor[x-1] = PRETO;  // "Fechamento" do vértice
    return 0;
}

// Sobrecarga da BUSCA EM PROFUNDIDADE (agora não é mais necessário remover os vértices da MA, apenas verificar se conseguimos chegar à Y)
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

        bool result = false;
        int result2 = 0;
        pai = new int[n];   // Array de pais
        cor = new int[n];   // Array de cores
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

        //Primeira DFS (a que "remove" o caminho depois de percorrer a MA)
        dfs(x, n, y, result, pai[x-1]);

        // condicional para ignorar a segunda busca caso a primeira já tenha falhado (economiza tempo)
        if(result == true){
            // Reajuste necessário para um novo percorrimento de DFS
            for(int i = 0; i < n; i++){
                pai[i] = -1;
                cor[i] = BRANCO;
            }

            // Segunda DFS 
            dfs(x, n, y, result2);
            if(result2 == 1){
                cout << 1 << endl;
            }
            else{
                cout << 0 <<  endl;
            }
        }
        else{
            cout << 0 << endl; 
        }

        // Desalocando memória        
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