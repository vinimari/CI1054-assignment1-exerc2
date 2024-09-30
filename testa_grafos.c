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
  le_e_adiciona_vertices(G);
  le_e_adiciona_arestas(G);  
  imprime_grafo(G);
  destroi_grafo(G);
  return 0;
}
