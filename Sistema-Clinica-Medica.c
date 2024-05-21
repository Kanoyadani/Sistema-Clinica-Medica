#include <stdio.h>
#include <stdlib.h>
//-------------------Segundo Menu-----------
typedef struct sug{
	int idp;
	int priori;
	struct sug* proxi;
}sug;


void atende(){
	
};




//-------------------Primereiro Menu-----------
// Definição da estrutura de um nó da lista
typedef struct no {
  int id;
  char nome;
  char rg;
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
no* Insere(no* P) {
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
    // Se a Pilha está vazia, inicializa a lista com o novo nó
    P = novo;
  } else {
    // Encontra o último nó da Pillha
    no* ultimo = P;
    while (ultimo->prox != NULL) {
      ultimo = ultimo->prox;
    }

    // Conecta o novo nó ao final da Pilha
    ultimo->prox = novo;
  }

  return P;
}


int main() {
  // Inicialização da Pilha
  no* lista = NULL;

  int opcao, menus;
  while (1) {
  	
  	printf("\nMenus:\n");
    printf("1. Paciente\n"); 
    printf("2. Atendimento\n");

    scanf("%d", &menus);
    
    if (menus == 1){
    	do{
    	printf("\Menu: Paciente:\n");
	    printf("1. Adicionar paciente\n"); 
	    printf("2. Exibir pacientes\n");
	    printf("3. Lista de Atendimentos\n");
	    printf("4. Voltar\n");
	    printf("5. Sair\n");
	    scanf("%d", &opcao);

    switch (opcao) {
      case 1:
        lista = Insere(lista);
        break;
      case 2:
        exibe(lista);
        break;
      case 3:
        //
        break;
      case 4:
        menus = 0;
        break;
      case 5: {
        no* atual = lista;
        while (atual != NULL) {
          no* temp = atual;
          atual = atual->prox;
          free(temp);
        }
        return 0;
      }
      default:
        printf("Opcao invilida!\n");
    }
    
	}while(menus == 1);
	
	}else if(menus == 2){
		do{
    	printf("\nMenu: Atendimento\n");
	    printf("1. Atender Paciente\n"); 
	    printf("2. Exibir Pacientes\n");
	    printf("3. Voltar\n");
	    printf("4. Sair\n");
	    scanf("%d", &opcao);
	    
	    switch (opcao) {
      case 1:
        lista = Insere(lista);
        break;
      case 2:
        exibe(lista);
        break;
      case 3:
        menus = 0;
        break;
      case 4: {
        no* atual = lista;
        while (atual != NULL) {
          no* temp = atual;
          atual = atual->prox;
          free(temp);
        }
        return 0;
      }
      default:
        printf("Opcao invilida!\n");
    }

    }while(menus == 2);
    
	}
  }
  return 0;
}
