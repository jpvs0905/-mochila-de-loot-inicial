#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0;
int comparacoes = 0;

// --- FUNÇÕES AUXILIARES ---

void ordenarMochila() {
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
}

// --- OPÇÕES DO MENU ---

void adicionarItem() {
    if (totalItens < MAX_ITENS) {
        printf("\n-- Adicionar Novo Item (Loot) --\n");
        printf("Nome do item: ");
        scanf(" %[^\n]s", mochila[totalItens].nome);
        printf("Tipo do item: ");
        scanf(" %[^\n]s", mochila[totalItens].tipo);
        printf("Quantidade: ");
        scanf("%d", &mochila[totalItens].quantidade);
        
        printf("\nItem '%s' adicionado com sucesso!\n", mochila[totalItens].nome);
        totalItens++;
    } else {
        printf("\nErro: Mochila cheia! Remova algo para abrir espaço.\n");
    }
}

void removerItem() {
    char nomeRemover[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]s", nomeRemover);

    int indice = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        for (int i = indice; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("Item '%s' removido com sucesso!\n", nomeRemover);
    } else {
        printf("Item nao encontrado.\n");
    }
}

void listarItens() {
    printf("\n%-15s | %-12s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("--------------------------------------------\n");
    if (totalItens == 0) {
        printf("A mochila esta vazia!\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("%-15s | %-12s | %-10d\n", 
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
}

void buscarItem() {
    char alvo[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %[^\n]s", alvo);

    // Conforme o desafio: Ordenar para permitir Busca Binária
    ordenarMochila();
    
    int esq = 0, dir = totalItens - 1, achou = -1;
    comparacoes = 0;

    while (esq <= dir) {
        comparacoes++;
        int meio = (esq + dir) / 2;
        int res = strcmp(mochila[meio].nome, alvo);

        if (res == 0) {
            achou = meio;
            break;
        } else if (res < 0) esq = meio + 1;
        else dir = meio - 1;
    }

    if (achou != -1) {
        printf("\nItem Encontrado!\n");
        printf("Nome: %s | Tipo: %s | Qtd: %d\n", 
               mochila[achou].nome, mochila[achou].tipo, mochila[achou].quantidade);
    } else {
        printf("\nItem '%s' nao encontrado na mochila.\n", alvo);
    }
    printf("Comparacoes realizadas (Busca Binaria): %d\n", comparacoes);
}

// --- FLUXO PRINCIPAL ---

int main() {
    int opcao;
    do {
        printf("\n============================================\n");
        printf("     MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf("============================================\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Item\n");
        printf("4. Buscar Item por Nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: buscarItem(); break;
            case 0: printf("Saindo... Boa sorte no deserto!\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}