#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 30

// Struct para representar cada item da mochila (versão vetor)
struct Item {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
};

// Struct para lista encadeada
struct No {
    struct Item item;
    struct No* proximo;
};

// Função para exibir o menu principal
void exibirMenuPrincipal() {
    printf("\n=== MOCHILA DA ILHA - FREE FIRE ===\n");
    printf("1. Usar Vetor Estatico\n");
    printf("2. Usar Lista Encadeada\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");
}

// Função para exibir o menu de operações
void exibirMenuOperacoes() {
    printf("\n=== MENU DE OPERACOES ===\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Voltar ao menu principal\n");
    printf("Escolha uma opcao: ");
}

// ========== IMPLEMENTAÇÃO COM VETOR ESTÁTICO ==========

// Adicionar item no vetor
int adicionarItemVetor(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens >= MAX_ITENS) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return 0;
    }
    
    printf("\n=== ADICIONAR ITEM (VETOR) ===\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[*quantidadeItens].nome);
    
    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[*quantidadeItens].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*quantidadeItens].quantidade);
    
    (*quantidadeItens)++;
    printf("Item adicionado com sucesso!\n");
    return 1;
}

// Remover item do vetor
int removerItemVetor(struct Item mochila[], int *quantidadeItens) {
    if (*quantidadeItens == 0) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return 0;
    }
    
    char nomeRemover[TAM_NOME];
    printf("\n=== REMOVER ITEM (VETOR) ===\n");
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nomeRemover);
    
    for (int i = 0; i < *quantidadeItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *quantidadeItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*quantidadeItens)--;
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            return 1;
        }
    }
    
    printf("Item '%s' nao encontrado!\n", nomeRemover);
    return 0;
}

// Listar itens do vetor
void listarItensVetor(struct Item mochila[], int quantidadeItens) {
    if (quantidadeItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }
    
    printf("\n=== ITENS NA MOCHILA (VETOR) ===\n");
    printf("--------------------------------------------\n");
    printf("NOME                    | TIPO       | QTD\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < quantidadeItens; i++) {
        printf("%-23s | %-10s | %-3d\n", 
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("--------------------------------------------\n");
}

// ========== IMPLEMENTAÇÃO COM LISTA ENCADEADA ==========

// Adicionar item no início da lista encadeada
void adicionarItemLista(struct No** inicio) {
    struct No* novo = (struct No*)malloc(sizeof(struct No));
    
    printf("\n=== ADICIONAR ITEM (LISTA) ===\n");
    printf("Nome do item: ");
    scanf(" %[^\n]", novo->item.nome);
    
    printf("Tipo do item: ");
    scanf(" %[^\n]", novo->item.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novo->item.quantidade);
    
    novo->proximo = *inicio;
    *inicio = novo;
    
    printf("Item adicionado com sucesso!\n");
}

// Remover item da lista encadeada
void removerItemLista(struct No** inicio) {
    if (*inicio == NULL) {
        printf("Mochila vazia! Nao ha itens para remover.\n");
        return;
    }
    
    char nomeRemover[TAM_NOME];
    printf("\n=== REMOVER ITEM (LISTA) ===\n");
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nomeRemover);
    
    struct No* atual = *inicio;
    struct No* anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->item.nome, nomeRemover) == 0) {
            if (anterior == NULL) {
                *inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    printf("Item '%s' nao encontrado!\n", nomeRemover);
}

// Listar itens da lista encadeada
void listarItensLista(struct No* inicio) {
    if (inicio == NULL) {
        printf("\nMochila vazia!\n");
        return;
    }
    
    printf("\n=== ITENS NA MOCHILA (LISTA) ===\n");
    printf("--------------------------------------------\n");
    printf("NOME                    | TIPO       | QTD\n");
    printf("--------------------------------------------\n");
    
    struct No* atual = inicio;
    while (atual != NULL) {
        printf("%-23s | %-10s | %-3d\n", 
               atual->item.nome, atual->item.tipo, atual->item.quantidade);
        atual = atual->proximo;
    }
    printf("--------------------------------------------\n");
}

// Liberar memória da lista encadeada
void liberarLista(struct No** inicio) {
    struct No* atual = *inicio;
    while (atual != NULL) {
        struct No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *inicio = NULL;
}

// ========== MENUS E CONTROLE PRINCIPAL ==========

// Menu para vetor estático
void menuVetor() {
    struct Item mochila[MAX_ITENS];
    int quantidadeItens = 0;
    int opcao;
    
    printf("\nMODO VETOR ESTATICO ATIVADO\n");
    printf("Capacidade: %d itens\n", MAX_ITENS);
    
    do {
        exibirMenuOperacoes();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                adicionarItemVetor(mochila, &quantidadeItens);
                break;
            case 2:
                removerItemVetor(mochila, &quantidadeItens);
                break;
            case 3:
                listarItensVetor(mochila, quantidadeItens);
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 4);
}

// Menu para lista encadeada
void menuLista() {
    struct No* inicio = NULL;
    int opcao;
    
    printf("\nMODO LISTA ENCADEADA ATIVADO\n");
    printf("Capacidade: Dinamica\n");
    
    do {
        exibirMenuOperacoes();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                adicionarItemLista(&inicio);
                break;
            case 2:
                removerItemLista(&inicio);
                break;
            case 3:
                listarItensLista(inicio);
                break;
            case 4:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 4);
    
    liberarLista(&inicio);
}

// Função principal
int main() {
    int opcao;
    
    printf("BEM-VINDO AO DESAFIO CODIGO DA ILHA - FREE FIRE!\n");
    printf("Sistema de Gerenciamento de Mochila Virtual\n");
    
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 3:
                printf("\nObrigado por usar a Mochila da Ilha!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 3);
    
    return 0;
}