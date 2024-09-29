/*******************************************
 * Leitura e impressao de grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  grafo G = cria_grafo();
  le_e_adiciona_vertices(&G);
  le_e_adiciona_arestas(&G);  
  imprime_grafo(&G);
  destroi_grafo(&G);
  return 0;
}

le_e_adiciona_vertices(grafo *G) {
  int n;
  printf("Digite a quantidade de vertices: \n");
  scanf("%d", &n); // qtd vertices
  for (int i = 1; i <= n; ++i) {
    adiciona_vertice(i, &G);
  }
}

le_e_adiciona_arestas(grafo *G) {
  int id = 1;
  int u, v;
  printf("Digite os pares de arestas (para finalizar, digite 0 0) \n");
  scanf("%d %d", &u, &v);
  while (u && v) {
    adiciona_aresta(id, u, v, &G);
    ++id;
    scanf("%d %d", &u, &v);
  }
}
