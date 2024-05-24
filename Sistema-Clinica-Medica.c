
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

// Função para limpar o prompt
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Contador global para os IDs dos pacientes
int proximoId = 1;

// Função para exibir a lista de pacientes
void exibe(no* P) {
    no* atual = P;
    if (atual == NULL) {
        printf("Sem pacientes.\n");
        system("pause");
        return;
    }

    printf("Lista de pacientes:\n");
    while (atual != NULL) {
        printf("----------------------\n");
        printf("ID do Paciente: %d\n", atual->id);
        printf("Nome do Paciente: %s\n", atual->nome);
        printf("RG do Paciente: %s\n", atual->rg);
        printf("Prioridade: %d\n", atual->prioridade);
        printf("----------------------\n\n");
        atual = atual->prox;
    }
    system("pause");
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
        system("pause");
        return;
    }

    printf("Lista de Atendimentos:\n\n");
    while (atual != NULL) {
        printf("----------------------\n");
        printf("ID do Paciente: %d\n", atual->idp);
        printf("Prioridade: %d\n", atual->priori);
        printf("----------------------\n\n");
        atual = atual->proxi;
    }
    system("pause");
}

// Função para remover um paciente da lista de pacientes
no* removePaciente(no* lista, int id) {
    no* atual = lista;
    no* anterior = NULL;

    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return lista;  // Paciente não encontrado
    }

    if (anterior == NULL) {
        lista = atual->prox;  // Remove o primeiro nó
    } else {
        anterior->prox = atual->prox;  // Remove o nó do meio ou do fim
    }

    free(atual);
    return lista;
}

// Função para remover um atendimento da lista de sugestões
sug* removeSugestao(sug* lista, int id) {
    sug* atual = lista;
    sug* anterior = NULL;

    while (atual != NULL && atual->idp != id) {
        anterior = atual;
        atual = atual->proxi;
    }

    if (atual == NULL) {
        return lista;  // Atendimento não encontrado
    }

    if (anterior == NULL) {
        lista = atual->proxi;  // Remove o primeiro nó
    } else {
        anterior->proxi = atual->proxi;  // Remove o nó do meio ou do fim
    }

    free(atual);
    return lista;
}

// Função para inserir um paciente no final da lista e criar uma sugestão correspondente
no* Insere(no* P, sug** S) {
    no* novo = (no*)malloc(sizeof(no));
    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        system("pause");
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
    printf("----------------------\n\n");
    do {
        scanf("%d", &Valor);
        switch (Valor) {
            case 1: Valor = 1; break;
            case 2: Valor = 2; break;
            case 3: Valor = 3; break;
            default: 
                printf("Valor invalido, Digite um valor Valido\n");
                Valor = NULL;
        }
    } while (Valor == NULL);

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
        printf("Erro ao alocar memoria.\n");
        system("pause");
        return P;
    }

    novaSug->idp = novo->id;
    novaSug->priori = novo->prioridade;
    novaSug->proxi = NULL;

    *S = insertSugInOrder(*S, novaSug);
    system("pause");
    return P;
}

void atendimentoPrioritario(sug** listaSug, no** listaPac) {
    int count = 0;
    sug* atualSug = *listaSug;
    while (count < 3 && atualSug != NULL) {
        printf("Atendendo paciente com ID: %d\n", atualSug->idp);
        printf("Confirme o atendimento do paciente (1 para confirmado): ");
        int confirmado;
        scanf("%d", &confirmado);
        if (confirmado == 1) {
            *listaPac = removePaciente(*listaPac, atualSug->idp);
            *listaSug = removeSugestao(*listaSug, atualSug->idp);
            count++;
        } else {
            printf("Paciente nao atendido. Aguardando confirmacao.\n");
        }
        system("pause");
        limparTela();
        atualSug = *listaSug;
    }

    if (count == 0) {
        printf("Nenhum paciente atendido.\n");
    } else {
        printf("Atendimento dos 3 primeiros pacientes concluido.\n");
    }
    system("pause");
}


void atendimentoNormal(sug** listaSug, no** listaPac) {
    sug* atualSug = *listaSug;
    while (atualSug != NULL && atualSug->priori == 1) {
        atualSug = atualSug->proxi;
    }

    if (atualSug == NULL) {
        printf("Nenhum paciente com prioridade diferente de 1 para atendimento.\n");
        system("pause");
        return;
    }

    printf("Atendendo paciente com ID: %d\n", atualSug->idp);
    printf("Confirme o atendimento do paciente (1 para confirmado): ");
    int confirmado;
    scanf("%d", &confirmado);
    if (confirmado == 1) {
        *listaPac = removePaciente(*listaPac, atualSug->idp);
        *listaSug = removeSugestao(*listaSug, atualSug->idp);
        printf("Atendimento concluido.\n");
    } else {
        printf("Paciente nao atendido. Aguardando confirmacao.\n");
    }
    system("pause");
    limparTela();
}

void atendimento(sug** listaSug, no** listaPac) {
    if (*listaSug == NULL) {
        printf("Sem pacientes.\n\n");
        system("pause");
        return;
    }

    int opcao;
    while (1) {
        printf("\nSubmenu de Atendimento:\n");
        printf("1. Atendimento Prioritario\n");
        printf("2. Atendimento Normal\n");
        printf("3. Exibir Atendimentos\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: \n\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                atendimentoPrioritario(listaSug, listaPac);
                break;
            case 2:
                atendimentoNormal(listaSug, listaPac);
                break;
            case 3:
                printf("Exibir Atendimentos\n\n");
                exibeSug(*listaSug);
                limparTela();
                break;
            case 4: 
                return;
            default:
                printf("Opcao invalida!\n");
                system("pause");
        }
    }
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
                limparTela();
                break;
            case 2:
                exibe(lista);
                limparTela();
                break;
            case 3:
                atendimento(&listaSug, &lista);
                limparTela();
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
                system("pause");
        }
    }
}

int main() {
    atende();
    return 0;
}
