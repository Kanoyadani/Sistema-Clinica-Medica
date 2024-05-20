#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da lista
typedef struct no {
  int id;
  struct no* prox;
} no;

// Contador global para os IDs dos pacientes
int proximoId = 1;

// Função para exibir a lista de pacientes
void exibe(no* P) {
  no* atual = P;
  if (atual == NULL) {
    printf("Sem pacientes.\n");
    return;
  }

  printf("Lista de pacientes:\n");
  while (atual != NULL) {
    printf("ID: %d\n", atual->id);
    atual = atual->prox;
  }
}

// Função para inserir um paciente no início da lista
no* insereInicio(no* P) {
  no* novo = (no*)malloc(sizeof(no));
  if (novo == NULL) {
    printf("Erro ao alocar memória.\n");
    return P;
  }

  // Atribui o próximo ID ao novo paciente
  novo->id = proximoId++;
  novo->prox = P;

  // Atualiza o início da lista
  P = novo;

  return P;
}

// Função para inserir um paciente no final da lista
no* InsereFinal(no* P) {
  no* novo = (no*)malloc(sizeof(no));
  if (novo == NULL) {
    printf("Erro ao alocar memória.\n");
    return P;
  }

  novo->id = proximoId++;
  novo->prox = NULL;

  if (P == NULL) {
    // Se a lista está vazia, inicializa a lista com o novo nó
    P = novo;
  } else {
    // Encontra o último nó da lista
    no* ultimo = P;
    while (ultimo->prox != NULL) {
      ultimo = ultimo->prox;
    }

    // Conecta o novo nó ao final da lista
    ultimo->prox = novo;
  }

  return P;
}

int main() {
  // Inicialização da lista
  no* lista = NULL;

  int opcao;
  while (1) {
    printf("\nMenu:\n");
    printf("1. Adicionar paciente no início\n");
    printf("2. Adicionar paciente no final\n");
    printf("3. Exibir pacientes\n");
    printf("4. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        lista = insereInicio(lista);
        break;
      case 2:
        lista = InsereFinal(lista);
        break;
      case 3:
        exibe(lista);
        break;
      case 4: {
        // Liberar a memória alocada antes de sair
        no* atual = lista;
        while (atual != NULL) {
          no* temp = atual;
          atual = atual->prox;
          free(temp);
        }
        return 0;
      }
      default:
        printf("Opção inválida!\n");
    }
  }

  return 0;
}

