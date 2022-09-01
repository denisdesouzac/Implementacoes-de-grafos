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
vector<vector<int>> ciclos(2);  // Vector bidimensional para armazenar os ciclos
//vector<int> ondeTemosX;
//vector<int> ondeTemosY;


// Função para verificar quando há necessidade de redimensionar o Vector de Ciclos (adiciona 2 espaços por vez)
void checkResize(){ 
    if(nCiclos == ciclos.size()){
        ciclos.resize(ciclos.size()+2);
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

// Função que faz o registro do ciclo formado por arestas paralelas
void registarCicloParalelo(int start1, int start2){
    for( int i =0; i < (MA[start1-1][start2-1]/2); i++ ){
        ciclos[nCiclos].push_back(start1);
        ciclos[nCiclos].push_back(start2);
        nCiclos++;
        checkResize();  // Verificação de redimensionamento
    }
}

/*
 Função da Busca em largura sendo realizada em uma Matiz, ela utiliza como referência um "start1" como sendo as LINHAS e um "start2" como COLUNAS,
 fazendo assim o caminhamento pela matriz e realizando uma BUSCA EM PROFUNDIDADE de maneira RECURSIVA.
 Ao encontrar com um número ">1" temos um ciclo composto de arestas paralelas.
 Ao encontrar com um vértice CINZA (já mapeado) temos um ciclo próprio e a função de registro é chamada.
*/
void dfs(int start1, int n){
    cout << " * " << start1;
    cor[start1-1] = CINZA;  // Marcando o vértice atual como CINZA

	for (int start2 = 1; start2 <= n; start2++) {
		// Caso para visitar o vizinho BRANCO
		if ( MA[start1-1][start2-1] >= 1 and (cor[start2-1] == BRANCO)){ 
            // Verificar se temos ciclos formados por arestas paralelas (caso haja, o ciclo é montado diretamente aqui)
            if( MA[start1-1][start2-1] > 1){
                registarCicloParalelo(start1, start2); // Função para Registrar ciclos de arestas paralelas
                checkResize(); // Verificação de redimensionamento
            }
            pai[start2-1] = start1;
			dfs(start2, n);     // Chamada recursiva
		}
        // Caso onde temos um ciclo PRÓPRIO
        else if( MA[start1-1][start2-1] >= 1 and (pai[start1-1] != start2) and ( cor[start2-1] == CINZA) ){
            registarCiclo(start1, start2);  // Chamada da função para registar esse ciclo
            nCiclos = nCiclos+1;
            checkResize();  // Verificação de redimensionamento
        }
	}
    cor[start1-1] = PRETO;  // "Fechamento" do vértice
}

// verifica se dois ciclos quaisquer Ci e Cj, i,j=1,...,k, i != j, não possuem arestas em comum.
bool verifica_arestas(){
    int cont = 0;
    for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
            for(int x = u+1; x < nCiclos; x++){
                for(int z = 0; z < ciclos[x].size(); z++){
                    if(ciclos[u][v] == ciclos[x][z]) {
                        cout << "achei vértice comum(arestas): " << ciclos[u][v] << " E " << ciclos[x][z] << endl;
                        cont++;
                    }
                }
            }
        }
    }
    if(cont>1){
        cout << "Contador arestas: " << cont/float(2) << endl;
        return true;
    }else{
        return false;
    }
}

//verifica se existe exatamente um vértice em comum entre dois ciclos adjacentes Ci e Cj, com 1 <= i,j <= k.
bool existe_1_vcomum(){
    int cont = 0;
    for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
            for(int x = u+1; x < nCiclos; x++){
                for(int z = 0; z < ciclos[x].size(); z++){
                    if(ciclos[u][v] == ciclos[x][z]) {
                        cout << "achei vértice comum: " << ciclos[u][v] << " E " << ciclos[x][z] << endl;
                        cont++;
                    }
                }
            }
        }
    }
    if(cont == 1){
        return true;
    }else{
        cout << "Contador vertices comum em dois ciclos adj: " << cont << endl;
        return false;
    }
}

// verifica se ciclos que não-adjacentes não possuem vértices em comum.
bool n_vcomum(){
    int cont = 0;
    for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
            for(int x = u+1; x < nCiclos; x++){
                for(int z = 0; z < ciclos[x].size(); z++){
                    if(ciclos[u][v] == ciclos[x][z]) {
                        cout << "achei vértice comum(não adjacente): " << ciclos[u][v] << " E " << ciclos[x][z] << endl;
                        cont++;
                    }
                }
            }
        }
    }
    if(cont == 0){
        return false;
    }else{
        cout << "ciclos não adjacentes possuem vértice comum:  " << cont << endl;
        return true;
    }
}

// verifica se um vértice aparece em um ciclo no máximo uma vez.
bool v_ap_1vez(){
    int elem;
     for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
            elem = ciclos[u][v];
            for(int x = 0; x < ciclos[u].size(); x++){
                if(x != v){
                    if(ciclos[u][x] == elem) return false;
                }
            }
        }
     }
     return true;
}

void imprime_n(){
    cout << "0" << endl;
}

void imprime_s(){
    cout << "1" << endl;
}


int main(){

    // Iniciação e Declaração das estruturas
    int n, m, x, y;
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

    //Print DFS
    cout << endl;
    dfs(1,n);
    cout << endl;
    cout << "nCIclos: " << nCiclos << endl;

    //Print Ciclos
    for(int u = 0; u < nCiclos; u++){
        for(int v = 0; v < ciclos[u].size(); v++){
            cout << " " << ciclos[u][v]  << " ";
        }
        cout << endl;
    }
    
    // Entrada de X e Y
    cin >> x >> y;

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

    cout << "tem x: "<< tem_x << " " << "Tem y: " << tem_y << endl;

    if((!tem_x) or (!tem_y)){
       imprime_n();
     }else{
        if(!verifica_arestas()) {
            cout << "Caiu aq: verifica_arestas()" << endl;
            imprime_s();
        }
        else if(existe_1_vcomum()){
             cout << "Caiu aq: existe_1_vcomum()" << endl;
            imprime_s();
        } 
        else if(n_vcomum()) {
             cout << "Caiu aq: n_vcomum()" << endl;
            imprime_s();
        }
        else if(v_ap_1vez()){
            cout << "Caiu aq: v_ap_1vez()" << endl;
            imprime_s();
        }
        else{
            imprime_n();
        }
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