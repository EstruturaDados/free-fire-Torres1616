#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 100
#define TAM_NOME 30
#define TAM_TIPO 20

// Contadores globais para comparar eficiencia das buscas
int comp_sequencial = 0;
int comp_binaria = 0;

// Estrutura do item da mochila
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Estrutura do no da lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ========== IMPLEMENTACAO COM VETOR ==========

// Variaveis globais para vetor
Item mochila_vetor[MAX_ITENS];
int qtd_vetor = 0;

// Insere item no final do vetor
void inserirItemVetor() {
    if (qtd_vetor >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }
    
    printf("\n--- ADICIONAR ITEM (VETOR) ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", mochila_vetor[qtd_vetor].nome);
    
    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila_vetor[qtd_vetor].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &mochila_vetor[qtd_vetor].quantidade);
    
    qtd_vetor++;
    printf("Item adicionado com sucesso!\n");
}

// Remove item do vetor por nome
void removerItemVetor() {
    if (qtd_vetor == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\n--- REMOVER ITEM (VETOR) ---\n");
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);
    
    // Busca sequencial pelo item
    for (int i = 0; i < qtd_vetor; i++) {
        if (strcmp(mochila_vetor[i].nome, nome) == 0) {
            // Remove deslocando todos os elementos para frente
            for (int j = i; j < qtd_vetor - 1; j++) {
                mochila_vetor[j] = mochila_vetor[j + 1];
            }
            qtd_vetor--;
            printf("Item '%s' removido com sucesso!\n", nome);
            return;
        }
    }
    
    printf("Item '%s' nao encontrado!\n", nome);
}

// Ordena vetor por nome usando Bubble Sort
void ordenarVetor() {
    if (qtd_vetor == 0) {
        printf("Mochila vazia! Nao ha itens para ordenar.\n");
        return;
    }
    
    // Algoritmo Bubble Sort
    for (int i = 0; i < qtd_vetor - 1; i++) {
        for (int j = 0; j < qtd_vetor - i - 1; j++) {
            // Compara nomes adjacentes
            if (strcmp(mochila_vetor[j].nome, mochila_vetor[j + 1].nome) > 0) {
                // Troca os itens de posicao
                Item temp = mochila_vetor[j];
                mochila_vetor[j] = mochila_vetor[j + 1];
                mochila_vetor[j + 1] = temp;
            }
        }
    }
    printf("Itens ordenados por nome!\n");
}

// Busca sequencial no vetor - funciona sem ordenacao
int buscarSequencialVetor(char nome[]) {
    comp_sequencial = 0; // Reseta contador
    
    for (int i = 0; i < qtd_vetor; i++) {
        comp_sequencial++;
        if (strcmp(mochila_vetor[i].nome, nome) == 0) {
            return i; // Retorna indice se encontrado
        }
    }
    return -1; // Retorna -1 se nao encontrado
}

// Busca binaria no vetor - requer vetor ordenado
int buscarBinariaVetor(char nome[]) {
    comp_binaria = 0; // Reseta contador
    int inicio = 0, fim = qtd_vetor - 1;
    
    while (inicio <= fim) {
        comp_binaria++;
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(mochila_vetor[meio].nome, nome);
        
        if (comparacao == 0) {
            return meio; // Elemento encontrado
        } else if (comparacao < 0) {
            inicio = meio + 1; // Busca na metade direita
        } else {
            fim = meio - 1; // Busca na metade esquerda
        }
    }
    return -1; // Elemento nao encontrado
}

// Lista todos os itens do vetor
void listarItensVetor() {
    if (qtd_vetor == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    
    printf("\n--- ITENS NA MOCHILA (VETOR) ---\n");
    printf("--------------------------------------------\n");
    printf("NOME                      | TIPO         | QTD\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < qtd_vetor; i++) {
        printf("%-25s | %-12s | %-3d\n", 
               mochila_vetor[i].nome, mochila_vetor[i].tipo, mochila_vetor[i].quantidade);
    }
    printf("--------------------------------------------\n");
    printf("Total de itens: %d/%d\n", qtd_vetor, MAX_ITENS);
}

// ========== IMPLEMENTACAO COM LISTA ENCADEADA ==========

// Ponteiro para inicio da lista
No* mochila_lista = NULL;

// Insere item no inicio da lista
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));
    
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }
    
    printf("\n--- ADICIONAR ITEM (LISTA) ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novo->dados.nome);
    
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->dados.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    
    // Insere no inicio - O(1)
    novo->proximo = mochila_lista;
    mochila_lista = novo;
    
    printf("Item adicionado com sucesso!\n");
}

// Remove item da lista por nome
void removerItemLista() {
    if (mochila_lista == NULL) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\n--- REMOVER ITEM (LISTA) ---\n");
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);
    
    No* atual = mochila_lista;
    No* anterior = NULL;
    
    // Percorre lista procurando item
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                // Remove primeiro item
                mochila_lista = atual->proximo;
            } else {
                // Remove item do meio/fim
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item '%s' removido com sucesso!\n", nome);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("Item '%s' nao encontrado!\n", nome);
}

// Busca sequencial na lista encadeada
No* buscarSequencialLista(char nome[]) {
    comp_sequencial = 0; // Reseta contador
    No* atual = mochila_lista;
    
    while (atual != NULL) {
        comp_sequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            return atual; // Retorna ponteiro para o no
        }
        atual = atual->proximo;
    }
    return NULL; // Retorna NULL se nao encontrado
}

// Lista todos os itens da lista encadeada
void listarItensLista() {
    if (mochila_lista == NULL) {
        printf("\nMochila vazia!\n");
        return;
    }
    
    printf("\n--- ITENS NA MOCHILA (LISTA) ---\n");
    printf("--------------------------------------------\n");
    printf("NOME                      | TIPO         | QTD\n");
    printf("--------------------------------------------\n");
    
    No* atual = mochila_lista;
    while (atual != NULL) {
        printf("%-25s | %-12s | %-3d\n", 
               atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("--------------------------------------------\n");
}

// Libera memoria da lista encadeada
void liberarLista() {
    No* atual = mochila_lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    mochila_lista = NULL;
}

// ========== MENUS E FUNCOES AUXILIARES ==========

// Menu para operacoes com vetor
void menuVetor() {
    int opcao;
    
    printf("\n=== MODO VETOR ESTATICO ===\n");
    printf("Capacidade maxima: %d itens\n", MAX_ITENS);
    
    do {
        printf("\n--- MENU VETOR ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Ordenar itens (para busca binaria)\n");
        printf("5. Busca sequencial por nome\n");
        printf("6. Busca binaria por nome\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                inserirItemVetor();
                break;
            case 2:
                removerItemVetor();
                break;
            case 3:
                listarItensVetor();
                break;
            case 4:
                ordenarVetor();
                break;
            case 5: {
                char nome[TAM_NOME];
                printf("Nome do item a buscar: ");
                scanf(" %[^\n]", nome);
                int pos = buscarSequencialVetor(nome);
                if (pos != -1) {
                    printf("Item encontrado na posicao %d\n", pos);
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                } else {
                    printf("Item nao encontrado\n");
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                }
                break;
            }
            case 6: {
                char nome[TAM_NOME];
                printf("Nome do item a buscar: ");
                scanf(" %[^\n]", nome);
                int pos = buscarBinariaVetor(nome);
                if (pos != -1) {
                    printf("Item encontrado na posicao %d\n", pos);
                    printf("Comparacoes realizadas: %d\n", comp_binaria);
                } else {
                    printf("Item nao encontrado\n");
                    printf("Comparacoes realizadas: %d\n", comp_binaria);
                }
                break;
            }
            case 7:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 7);
}

// Menu para operacoes com lista encadeada
void menuLista() {
    int opcao;
    
    printf("\n=== MODO LISTA ENCADEADA ===\n");
    printf("Capacidade: Dinamica (limitada pela memoria)\n");
    
    do {
        printf("\n--- MENU LISTA ---\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Busca sequencial por nome\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                inserirItemLista();
                break;
            case 2:
                removerItemLista();
                break;
            case 3:
                listarItensLista();
                break;
            case 4: {
                char nome[TAM_NOME];
                printf("Nome do item a buscar: ");
                scanf(" %[^\n]", nome);
                No* resultado = buscarSequencialLista(nome);
                if (resultado != NULL) {
                    printf("Item encontrado!\n");
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                } else {
                    printf("Item nao encontrado\n");
                    printf("Comparacoes realizadas: %d\n", comp_sequencial);
                }
                break;
            }
            case 5:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 5);
}

// Funcao principal
int main() {
    int opcao;
    
    printf("=== SISTEMA DE MOCHILA - FREE FIRE ===\n");
    printf("Desafio Nivel Aventureiro: Vetor vs Lista Encadeada\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Usar Vetor Estatico\n");
        printf("2. Usar Lista Encadeada\n");
        printf("3. Comparar desempenho das estruturas\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 3:
                printf("\n--- COMPARATIVO DE DESEMPENHO ---\n");
                printf("VETOR:\n");
                printf("- Acesso por indice: O(1)\n");
                printf("- Insercao/remocao no meio: O(n)\n");
                printf("- Busca sequencial: O(n)\n");
                printf("- Busca binaria: O(log n) - requer ordenacao\n");
                printf("- Memoria: Contigua e previsivel\n\n");
                printf("LISTA ENCADEADA:\n");
                printf("- Acesso por indice: O(n)\n");
                printf("- Insercao/remocao no inicio: O(1)\n");
                printf("- Busca sequencial: O(n)\n");
                printf("- Busca binaria: Nao aplicavel\n");
                printf("- Memoria: Dinamica e flexivel\n");
                break;
            case 4:
                liberarLista();
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 4);
    
    return 0;
}