#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da lista
typedef struct no {
  int id;
  int prioridade;
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
    printf("----------------------\n");
    printf("ID do Paciente: %d\n", atual->id);
    printf("Prioridade: %d\n", atual->prioridade);
    printf("----------------------\n");
    atual = atual->prox;
  }
}


// Função para inserir um paciente no final da lista
no* InsereFinal(no* P) {
  no* novo = (no*)malloc(sizeof(no));
  int Valor;
  if (novo == NULL) {
    printf("Erro ao alocar memória.\n");
    return P;
  }
  
  
  printf("Qual a Prioridade de Atendimento?\n");
  printf("----------------------\n");
  printf("1- Alto\n");
  printf("2- Medio\n");
  printf("3- Baixo\n");
  printf("----------------------\n");
  do{
     scanf("%d", &Valor);          
     switch (Valor){
     case 1: Valor = 1; break;
     case 2: Valor = 2; break;
     case 3: Valor = 3; break;
     default: printf("Valor invalido, Digite um valor Valido\n");
     Valor = NULL;
     
     };      
  }while(Valor == NULL);
  
  novo->id = proximoId++;
  novo -> prioridade =  Valor;  
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
  while (opcao) {
    printf("\nMenu:\n");
    printf("1. Adicionar paciente\n"); 
    printf("2. Exibir pacientes\n");
    printf("3. Lista de Atendimentos\n");
    printf("4. Sair\n");
    printf("Escolha uma opcaoo: ");
    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        lista = InsereFinal(lista);
        break;
      case 2:
        exibe(lista);
        break;
      case 3:
        //
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
