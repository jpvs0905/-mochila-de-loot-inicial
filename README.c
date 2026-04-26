#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// 1. Definição da Estrutura conforme requisito
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis Globais para o sistema
Componente mochila[MAX_COMP];
int totalItens = 0;
int ordenadoPorNome = 0; // Flag de segurança para Busca Binária

// Protótipos das funções obrigatórias
void bubbleSortNome(int *comps);
void insertionSortTipo(int *comps);
void selectionSortPrioridade(int *comps);
int buscaBinaria(char alvo[]);
void mostrarComponentes();

// --- ALGORITMOS DE ORDENAÇÃO ---

void bubbleSortNome(int *comps) {
    *comps = 0;
    for (int i = 0; i < totalItens - 1; i++) {
        for (int j = 0; j < totalItens - i - 1; j++) {
            (*comps)++;
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Componente temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
}

void insertionSortTipo(int *comps) {
    *comps = 0;
    for (int i = 1; i < totalItens; i++) {
        Componente chave = mochila[i];
        int j = i - 1;
        while (j >= 0 && strcmp(mochila[j].tipo, chave.tipo) > 0) {
            (*comps)++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        if (j >= 0) (*comps)++; 
        mochila[j + 1] = chave;
    }
}

void selectionSortPrioridade(int *comps) {
    *comps = 0;
    for (int i = 0; i < totalItens - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < totalItens; j++) {
            (*comps)++;
            if (mochila[j].prioridade < mochila[minIdx].prioridade) {
                minIdx = j;
            }
        }
        Componente temp = mochila[minIdx];
        mochila[minIdx] = mochila[i];
        mochila[i] = temp;
    }
}

// --- OPÇÕES DO MENU ---

void adicionarComponente() {
    if (totalItens < MAX_COMP) {
        printf("\n-- Cadastro de Componente --\n");
        printf("Nome: "); scanf(" %[^\n]s", mochila[totalItens].nome);
        printf("Tipo: "); scanf(" %[^\n]s", mochila[totalItens].tipo);
        printf("Prioridade (1-10): "); scanf("%d", &mochila[totalItens].prioridade);
        totalItens++;
        ordenadoPorNome = 0; // Se adicionou novo item, a ordem mudou
        printf(">> Componente integrado!\n");
    } else printf(">> Erro: Mochila cheia!\n");
}

void retirarComponente() {
    char alvo[30];
    printf("\nDigite o nome do componente para retirar: ");
    scanf(" %[^\n]s", alvo);
    int encontrado = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, alvo) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado != -1) {
        for (int i = encontrado; i < totalItens - 1; i++) mochila[i] = mochila[i+1];
        totalItens--;
        printf(">> Componente removido com sucesso.\n");
    } else printf(">> Componente nao encontrado.\n");
}

void organizarMochila() {
    int escolha, comps = 0;
    clock_t t_inicio, t_fim;
    printf("\nEscolha o algoritmo de organizacao:\n");
    printf("1. Por Nome (Bubble Sort)\n2. Por Tipo (Insertion Sort)\n3. Por Prioridade (Selection Sort)\nOpcao: ");
    scanf("%d", &escolha);

    t_inicio = clock();
    if (escolha == 1) { bubbleSortNome(&comps); ordenadoPorNome = 1; }
    else if (escolha == 2) { insertionSortTipo(&comps); ordenadoPorNome = 0; }
    else if (escolha == 3) { selectionSortPrioridade(&comps); ordenadoPorNome = 0; }
    t_fim = clock();

    printf("\n[DESEMPENHO] Comparacoes: %d | Tempo: %f segundos\n", comps, (double)(t_fim - t_inicio) / CLOCKS_PER_SEC);
}

void buscaPorNome() {
    if (!ordenadoPorNome) {
        printf("\n[ERRO] A busca binaria exige ordenacao por NOME (Opcao 4 -> 1).\n");
        return;
    }
    char alvo[30];
    printf("\nComponente para buscar: ");
    scanf(" %[^\n]s", alvo);
    
    int esq = 0, dir = totalItens - 1, compsBusca = 0;
    while (esq <= dir) {
        compsBusca++;
        int meio = (esq + dir) / 2;
        int res = strcmp(mochila[meio].nome, alvo);
        if (res == 0) {
            printf(">> ENCONTRADO na posicao %d! Comparações: %d\n", meio + 1, compsBusca);
            return;
        }
        if (res < 0) esq = meio + 1; else dir = meio - 1;
    }
    printf(">> Componente-chave nao localizado.\n");
}

void listar() {
    printf("\n%-20s | %-15s | %s\n", "COMPONENTE", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < totalItens; i++)
        printf("%-20s | %-15s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].prioridade);
}

// --- FLUXO PRINCIPAL ---

int main() {
    int opcao;
    do {
        printf("\n========================================\n");
        printf("       SISTEMA DE FUGA - NIVEL FINAL    \n");
        printf("========================================\n");
        printf("1- Adicionar Componentes\n");
        printf("2- Retirar Componentes\n");
        printf("3- Listar Componentes\n");
        printf("4- Organizar Mochila\n");
        printf("5- Busca por Nome\n");
        printf("0- Ativar Torre de Fuga (Sair)\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarComponente(); break;
            case 2: retirarComponente(); break;
            case 3: listar(); break;
            case 4: organizarMochila(); break;
            case 5: buscaPorNome(); break;
            case 0: 
                if (totalItens > 0) printf("\nTORRE ATIVADA! Fugindo da ilha...\n");
                else printf("\nSaindo... Voce ficou na ilha sem componentes.\n");
                break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}