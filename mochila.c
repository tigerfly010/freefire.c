#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções do vetor
void inserirItemVetor(Item mochila[], int *qtd);
void removerItemVetor(Item mochila[], int *qtd);
void listarItensVetor(Item mochila[], int qtd);
int buscarSequencialVetor(Item mochila[], int qtd, char nome[], int *comparacoes);
int buscarBinariaVetor(Item mochila[], int qtd, char nome[], int *comparacoes);
void ordenarVetor(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;
    char linha[10];

    do {
        printf("\n=== MOCHILA DE LOOT (VETOR) ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (sequencial)\n");
        printf("5 - Ordenar mochila e buscar item (binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        fgets(linha, sizeof(linha), stdin);
        opcao = atoi(linha);

        switch(opcao) {
            case 1:
                inserirItemVetor(mochila, &qtd);
                break;
            case 2:
                removerItemVetor(mochila, &qtd);
                break;
            case 3:
                listarItensVetor(mochila, qtd);
                break;
            case 4: {
                char nome[30];
                int comparacoes = 0;
                printf("\nDigite o nome do item para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int pos = buscarSequencialVetor(mochila, qtd, nome, &comparacoes);
                if (pos != -1) {
                    printf("Item encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                           mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                } else {
                    printf("Item nao encontrado!\n");
                }
                printf("Comparacoes realizadas: %d\n", comparacoes);
                break;
            }
            case 5: {
                char nome[30];
                int comparacoes = 0;
                ordenarVetor(mochila, qtd);
                printf("Mochila ordenada por nome!\n");
                printf("Digite o nome do item para buscar (binaria): ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                int pos = buscarBinariaVetor(mochila, qtd, nome, &comparacoes);
                if (pos != -1) {
                    printf("Item encontrado!\nNome: %s | Tipo: %s | Quantidade: %d\n",
                           mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                } else {
                    printf("Item nao encontrado!\n");
                }
                printf("Comparacoes realizadas: %d\n", comparacoes);
                break;
            }
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// Inserir item no vetor
void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    fgets(mochila[*qtd].nome, sizeof(mochila[*qtd].nome), stdin);
    mochila[*qtd].nome[strcspn(mochila[*qtd].nome, "\n")] = '\0';

    printf("Digite o tipo do item: ");
    fgets(mochila[*qtd].tipo, sizeof(mochila[*qtd].tipo), stdin);
    mochila[*qtd].tipo[strcspn(mochila[*qtd].tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    char linha[10];
    fgets(linha, sizeof(linha), stdin);
    mochila[*qtd].quantidade = atoi(linha);

    (*qtd)++;
    printf("Item adicionado com sucesso!\n");
}

// Remover item do vetor
void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    char nome[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("Item '%s' removido com sucesso!\n", nome);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }
}

// Listar itens do vetor
void listarItensVetor(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Busca sequencial
int buscarSequencialVetor(Item mochila[], int qtd, char nome[], int *comparacoes) {
    for (int i = 0; i < qtd; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Ordenação simples por nome (Bubble Sort)
void ordenarVetor(Item mochila[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

// Busca binária (vetor já ordenado)
int buscarBinariaVetor(Item mochila[], int qtd, char nome[], int *comparacoes) {
    int inicio = 0, fim = qtd - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}



