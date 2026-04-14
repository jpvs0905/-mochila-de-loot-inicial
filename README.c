#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// --- DEFINIÇÃO DA STRUCT ---
// Agrupa diferentes tipos de dados em uma única unidade logística (o Item)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Variáveis Globais para controle do Inventário
Item mochila[MAX_ITENS];
int totalItens = 0;

// --- FUNÇÕES OBRIGATÓRIAS ---

// Lista todos os itens e limpa slots vazios visualmente
void listarItens() {
    printf("\n--- MOCHILA ATUAL (%d/%d) ---\n", totalItens, MAX_ITENS);
    if (totalItens == 0) {
        printf("A mochila esta vazia!\n");
    } else {
        for (int i = 0; i < totalItens; i++) {
            printf("%d. [%s] | Tipo: %s | Qtd: %d\n", i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }
    printf("----------------------------\n");
}

// Localiza um item pelo nome e retorna o índice (ou -1 se não encontrar)
int buscarItem(char *nomeBusca) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    printf("\nItem '%s' nao localizado na mochila.\n", nomeBusca);
    return -1;
}

// Adiciona um novo item ao final do vetor (Lista Sequencial)
void inserirItem() {
    if (totalItens < MAX_ITENS) {
        printf("\n--- CADASTRAR NOVO ITEM ---\n");
        printf("Nome: ");
        scanf(" %[^\n]s", mochila[totalItens].nome);
        printf("Tipo (Arma/Municao/Cura): ");
        scanf(" %[^\n]s", mochila[totalItens].tipo);
        printf("Quantidade: ");
        scanf("%d", &mochila[totalItens].quantidade);

        totalItens++;
        printf("Item adicionado com sucesso!\n");
        listarItens();
    } else {
        printf("\nErro: Mochila cheia! Remova algo antes de coletar mais loot.\n");
    }
}

// Remove um item e reorganiza o vetor para não deixar "buracos"
void removerItem() {
    char nomeRemover[30];
    printf("\nDigite o nome do item para remover: ");
    scanf(" %[^\n]s", nomeRemover);

    int indice = buscarItem(nomeRemover);
    if (indice != -1) {
        // Shifting: move os itens seguintes uma posição para trás
        for (int i = indice; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        totalItens--;
        printf("Item removido com sucesso!\n");
        listarItens();
    }
}

// --- FLUXO PRINCIPAL ---
int main() {
    int opcao;

    do {
        printf("\n=== SURVIVAL INVENTORY SYSTEM ===\n");
        printf("1. Inserir Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Buscar Item\n");
        printf("4. Listar Mochila\n");
        printf("0. Sair do Jogo\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: {
                char busca[30];
                printf("Nome do item para busca: ");
                scanf(" %[^\n]s", busca);
                buscarItem(busca);
                break;
            }
            case 4: listarItens(); break;
            case 0: printf("Saindo... Boa sorte no deserto!\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}