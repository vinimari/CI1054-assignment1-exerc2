/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  if (G == NULL) {
    printf("O grafo já está vazio!");
    return; 
  }

  lista arestas = G->arestas; 
  if (!vazio(arestas)) {
    printf("Removendo arestas... \n"); 
    for (no n = primeiro_no(arestas); n; n = proximo(n)) {
      aresta aresta_removida = desempilha(arestas); 
      printf("Aresta removida id: %d \n", aresta_removida->id);
    }
  }
  
  lista vertices = G->vertices;
  if (!vazio(vertices)) {
    printf("Removendo vertices... \n"); 
    for (no n = primeiro_no(vertices); n; n = proximo(n)) {
      vertice vertice_removido = desempilha(vertices);
      printf("Vertice removido id: %d \n", vertice_removido->id);
    }
  }

  free(G->arestas); 
  free(G->vertices); 
  free(G); 
}

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {
  vertice v = (vertice) malloc(sizeof(vertice)); 
  if (!v)
    exit(_ERRO_MALLOC_);
  v->id = id; 
  v->fronteira = NULL;
  empilha(v, G->vertices);
}

int get_id_vertice(obj c) {
  vertice v = c; 
  return v->id;
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  lista vertices = G->vertices; 
  if (vazio(vertices)) {
    printf("A lista de vertices esta vazia! \n"); 
    return;
  }

  printf("Removendo arestas incidentes... \n");
  vertice vertice_a_remover = busca_chave(id, vertices, get_id_vertice);
  if (!vertice_a_remover) {
    printf("Vertice com o id: %d não foi encontrado e não pode ser removido! \n", id); 
    return; 
  }

  lista arestas_incidentes = vertice_a_remover->fronteira;
  for (no n = primeiro_no(arestas_incidentes); n; n = proximo(n)) {
    aresta a = conteudo(n);
    aresta aresta_removida = desempilha(arestas_incidentes);
    printf("Aresta removida id: %d \n", aresta_removida->id); 
  }

  printf("Removendo vertice... \n"); 
  vertice vertice_removido = remove_chave(id, G->vertices, get_id_vertice);
  if (!vertice_removido) {
    printf("Vertice com o id: %d não foi encontrado e não pode ser removido! \n", id); 
    return; 
  }
  printf("Vertice com id: %d foi removido com sucesso! \n", id); 
}

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
  lista arestas = G->arestas; 
  vertice v_u = busca_chave(u_id, arestas, get_id_vertice);
  if (!v_u) {
    printf("Não foi possível encontrar o vertice com id: %d a aresta não foi criada! \n", u_id);
    return;
  }
  vertice v_v = busca_chave(v_id, arestas, get_id_vertice);
  if (!v_v) {
    printf("Não foi possível encontrar o vertice com id: %d a aresta não foi criada! \n", v_id);
    return; 
  }
  aresta a = (aresta) malloc(sizeof(aresta));
  if (!a) {
    exit(_ERRO_MALLOC_);
  }
  a->id = id; 
  a->u = u_id;
  a->v = v_id;
  empilha(a, v_u->fronteira); 
  empilha(a, v_v->fronteira);
  empilha(a, arestas); 
}

int get_id_aresta(obj c) {
  aresta a = c;
  return a->id;
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  lista arestas = G->arestas;
  if (vazio(arestas)) {
    printf("A lista de arestas esta vazia!"); 
    return;
  }
  printf("Removendo aresta... \n");
  aresta aresta_removida = remove_chave(id, G->arestas, get_id_aresta);
  if (!aresta_removida) {
    printf("Aresta com o id: %d não foi encontrada e não pode ser removida! \n", id); 
    return; 
  }
  printf("Aresta com id: %d foi removida com sucesso! \n", id); 
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:{%d,%d}", aresta_id(e), u_id, v_id);
}
