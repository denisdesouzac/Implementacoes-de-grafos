/*
    Dênis de Souza Cordeiro - 202110235 - 14A
    Gabriel Fernando Zanda Gonçalves - 202110234 - 14A
    Ronald de Souza Galdino - 202110679 - 14A
*/
#include<iostream>
#include<vector>
#include<utility>
#include<functional>
using namespace std;

#define INF 1000000000

/*
 * Variaveis globais
 */

// matriz de adjacencia
int** MA;

// quantidade de vertices
int n;

// quantidade de arestas
int m;

// quantidade de pares origem-destino a ser calculado
int k;

int getMenor(int vetor[]){
    int menor = vetor[0];
    for(int i = 0; i < n - 1; i++){
        if(vetor[i] < menor){
            menor = vetor[i];
        }
    }
    return menor;
}

void preencherVertor(int vetor[], int tamanho){

    for(int i = 0; i < tamanho; i++){
        vetor[i] = 0;
    }
}

int floyd_warshall(){
    for(int k = 0; k < n; k++)
      for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
          MA[i][j] = min(MA[i][j], MA[i][k] + MA[k][j]);
}

void imprimirMA(){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << MA[i][j] << " ";
        }
    }
}

int main(){

    cin >> n >> m;
        
    MA = new int*[n];
    int u, v, w;
    
    for(int i = 0; i < n; i++){
        MA[i] = new int[n];
        for(int j = 0; j < n; j++)
            MA[i][j] = INF;
    }

    for(int i = 0; i < m; i++){
        cin >> u >> v >> w;
        MA[u][v] = MA[v][u] = w;
    }
    
    floyd_warshall();

    int resultados[n];
    preencherVertor(resultados, n);

    int maior;
    for(int i = 0; i < n; i++){
        maior = resultados[i];
        for(int j = 0; j < m; j++){
            if(i!= j){
                if(MA[i][j] > maior and MA[i][j] != 0){
                    maior = MA[i][j];
                }    
            }
        }
        resultados[i] = maior;
    }

    int resultado = getMenor(resultados);
    cout << resultado << endl;


    return 0;
}