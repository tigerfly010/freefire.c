#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Definição da struct Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;

    do {
        printf("\n=== MOCHILA DE LOOT ===\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    fgets(mochila[*qtd].nome, 30, stdin);
    mochila[*qtd].nome[strcspn(mochila[*qtd].nome, "\n")] = '\0'; // remove o \n

    printf("Digite o tipo do item: ");
    fgets(mochila[*qtd].tipo, 20, stdin);
    mochila[*qtd].tipo[strcspn(mochila[*qtd].tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);
    getchar(); // limpa o \n novamente

    (*qtd)++;
    printf("Item adicionado com sucesso!\n");
}

void removerItem(Item mochila[], int *qtd) {
    char nome[30];
    int encontrado = 0;

    if (*qtd == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    printf("\nDigite o nome do item que deseja remover: \n");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("\nItem '%s' removido com sucesso!\n", nome);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }
}

void listarItens(Item mochila[], int qtd) {
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

void buscarItem(Item mochila[], int qtd) {
    char nome[30];
    int encontrado = 0;

    printf("\nDigite o nome do item para buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }
}

