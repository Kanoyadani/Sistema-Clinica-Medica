#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de uma sugestão (segmento)
typedef struct sug {
    int idp;
    int priori;
    struct sug* proxi;
} sug;

// Estrutura de um nó da lista de pacientes
typedef struct no {
    int id;
    char nome[50];
    char rg[50];
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
        printf("Nome do Paciente: %s\n", atual->nome);
        printf("RG do Paciente: %s\n", atual->rg);
        printf("Prioridade: %d\n", atual->prioridade);
        printf("----------------------\n");
        atual = atual->prox;
    }
}

// Função para inserir um novo Atendimentos na lista de forma ordenada
sug* insertSugInOrder(sug* S, sug* nova) {
    if (S == NULL || S->priori > nova->priori) {
        nova->proxi = S;
        return nova;
    } else {
        sug* atual = S;
        while (atual->proxi != NULL && atual->proxi->priori <= nova->priori) {
            atual = atual->proxi;
        }
        nova->proxi = atual->proxi;
        atual->proxi = nova;
    }
    return S;
}

// Função para exibir a lista de Atendimentos
void exibeSug(sug* S) {
    sug* atual = S;
    if (atual == NULL) {
        printf("Sem Atendimentos.\n");
        return;
    }

    printf("Lista de Atendimentos:\n");
    while (atual != NULL) {
        printf("----------------------\n");
        printf("ID do Paciente: %d\n", atual->idp);
        printf("Prioridade: %d\n", atual->priori);
        printf("----------------------\n");
        atual = atual->proxi;
    }
}

// Função para inserir um paciente no final da lista e criar uma sugestão correspondente
no* Insere(no* P, sug** S) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo == NULL) {
        printf("Erro ao alocar memória.\n");
        return P;
    }

    printf("Nome do Paciente: \n");
    getchar(); // Limpar o buffer antes de ler a string
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0; // Remove o '\n' do final

    printf("RG do Paciente: \n");
    fgets(novo->rg, sizeof(novo->rg), stdin);
    novo->rg[strcspn(novo->rg, "\n")] = 0;

    int Valor;
    printf("Qual a Prioridade de Atendimento?\n");
    printf("----------------------\n");
    printf("1- Alto\n");
    printf("2- Medio\n");
    printf("3- Baixo\n");
    printf("----------------------\n");
    do {
        scanf("%d", &Valor);
        switch (Valor) {
         case 1: Valor = 1; break;
         case 2: Valor = 2; break;
         case 3: Valor = 3; break;
            default: 
                printf("Valor invalido, Digite um valor Valido\n");
                Valor = 0;
        }
    } while (Valor == 0);

    novo->id = proximoId++;
    novo->prioridade = Valor;
    novo->prox = NULL;

    if (P == NULL) {
        P = novo;
    } else {
        no* ultimo = P;
        while (ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo;
    }

    // Criar uma sugestão correspondente e inserir na lista de sugestões
    sug* novaSug = (sug*)malloc(sizeof(sug));
    if (novaSug == NULL) {
        printf("Erro ao alocar memória.\n");
        return P;
    }

    novaSug->idp = novo->id;
    novaSug->priori = novo->prioridade;
    novaSug->proxi = NULL;

    *S = insertSugInOrder(*S, novaSug);

    return P;
}

void atende() {
    // Inicialização da Fila de Pacientes
    no* lista = NULL;
    // Inicialização da Lista de Sugestões
    sug* listaSug = NULL;

    int opcao;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Adicionar Paciente\n"); 
        printf("2. Exibir Pacientes\n");
        printf("3. Lista de Atendimentos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                lista = Insere(lista, &listaSug);
                break;
            case 2:
                exibe(lista);
                break;
            case 3:
                 
                exibeSug(listaSug);
                break;
            case 4: {
                // Liberar memória dos pacientes
                no* atualP = lista;
                while (atualP != NULL) {
                    no* tempP = atualP;
                    atualP = atualP->prox;
                    free(tempP);
                }

                // Liberar memória das sugestões
                sug* atualS = listaSug;
                while (atualS != NULL) {
                    sug* tempS = atualS;
                    atualS = atualS->proxi;
                    free(tempS);
                }
                return;
            }
            default:
                printf("Opcao invalida!\n");
        }
    }
}

int main() {
    atende();
    return 0;
}
