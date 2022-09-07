#include<iostream>
#include<utility>
using namespace std;

#define INF 1000000000 // Usando a sua definição de "infinito"

int** MA;   // Matriz de Adjacência

int miniDist(int distance[], bool Tset[]) // finding minimum distance
{
    int minimum=INF; // Mudei aqui
    int dist;
              
    for(int k=0;k<6;k++) 
    {
        if(Tset[k]==false && distance[k]<=minimum)      
        {
            minimum=distance[k];
            dist=k;
        }
    }
    return dist;
}

void DijkstraAlgo(int graph[6][6],int src) // adjacency matrix 
{
    int distance[6]; // // array to calculate the minimum distance for each node                             
    bool Tset[6];// boolean array to mark visited and unvisited for each node
    
    // Inicialmente todos os vértices NÃO foram visitados e tem DISTÂNCIA = INFINITO 
    for(int k = 0; k<6; k++)
    {
        distance[k] = INF; //Mudei aqui
        Tset[k] = false;    
    }
    
    distance[src] = 0;   // Source vertex distance is set 0               
    
    for(int k = 0; k<6; k++)                           
    {
        int m=miniDist(distance,Tset); 
        Tset[m]=true;
        for(int k = 0; k<6; k++)                  
        {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && graph[m][k] && distance[m]!=INF && distance[m]+graph[m][k]<distance[k])
                distance[k]=distance[m]+graph[m][k];
        }
    }
    cout<<"Vertex\t\tDistance from source vertex"<<endl;
    for(int k = 0; k<6; k++)                      
    { 
        char str=65+k; 
        cout<<str<<"\t\t\t"<<distance[k]<<endl;
    }
}

int main()
{
    int graph[6][6]={
        {0, 1, 2, 0, 0, 0},
        {1, 0, 0, 5, 1, 0},
        {2, 0, 0, 2, 3, 0},
        {0, 5, 2, 0, 2, 2},
        {0, 1, 3, 2, 0, 1},
        {0, 0, 0, 2, 1, 0}};
    DijkstraAlgo(graph,0);
    return 0;                           
}