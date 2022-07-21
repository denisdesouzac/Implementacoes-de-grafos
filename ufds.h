//%%writefile ufds.h
#ifndef UFDS_H
#define UFDS_H

#include<iostream>
using namespace std;

#include "definicoes.h"

class UFDS
{
    public:
      // construtor com parametro: n eh o numero de conjuntos disjuntos
      UFDS(int n)
      {
          rank.assign(n, 0);
          p.assign(n, 0);
          for(int i = 1; i < n+1; i++)                                                   // Problema tava aqui
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
#endif
