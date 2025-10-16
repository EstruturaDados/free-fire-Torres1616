#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define TAM_NOME 30
#define TAM_TIPO 20

// Estrutura do componente da torre
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int prioridade;
} Componente;

// Variáveis globais para contagem
int comparacoes = 0;
int trocas = 0;

// Função para limpar buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para trocar dois componentes
void trocar(Componente* a, Componente* b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

// ========== ALGORITMOS DE ORDENAÇÃO ==========

// Bubble Sort - Ordena por nome
void bubbleSortNome(Componente componentes[], int tamanho) {
    comparacoes = 0;
    trocas = 0;
    
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - 1 - i; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                trocar(&componentes[j], &componentes[j + 1]);
            }
        }
    }
}

// Insertion Sort - Ordena por tipo
void insertionSortTipo(Componente componentes[], int tamanho) {
    comparacoes = 0;
    trocas = 0;
    
    for (int i = 1; i < tamanho; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
}

// Selection Sort - Ordena por prioridade
void selectionSortPrioridade(Componente componentes[], int tamanho) {
    comparacoes = 0;
    trocas = 0;
    
    for (int i = 0; i < tamanho - 1; i++) {
        int indiceMaior = i;
        
        for (int j = i + 1; j < tamanho; j++) {
            comparacoes++;
            if (componentes[j].prioridade > componentes[indiceMaior].prioridade) {
                indiceMaior = j;
            }
        }
        
        if (indiceMaior != i) {
            trocar(&componentes[i], &componentes[indiceMaior]);
        }
    }
}

// ========== BUSCA BINÁRIA ==========

// Busca binária por nome (requer vetor ordenado por nome)
int buscaBinariaPorNome(Componente componentes[], int tamanho, char nome[]) {
    comparacoes = 0;
    int inicio = 0, fim = tamanho - 1;
    
    while (inicio <= fim) {
        comparacoes++;
        int meio = (inicio + fim) / 2;
        int resultado = strcmp(componentes[meio].nome, nome);
        
        if (resultado == 0) {
            return meio; // Componente encontrado
        } else if (resultado < 0) {
            inicio = meio + 1; // Busca na direita
        } else {
            fim = meio - 1; // Busca na esquerda
        }
    }
    return -1; // Componente não encontrado
}

// ========== FUNÇÕES DE EXIBIÇÃO ==========

// Mostrar todos os componentes
void mostrarComponentes(Componente componentes[], int tamanho) {
    if (tamanho == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n=== COMPONENTES DA TORRE ===\n");
    printf("┌──────────────────────────────┬──────────────────┬────────────┐\n");
    printf("│ %-28s │ %-16s │ %-10s │\n", "NOME", "TIPO", "PRIORIDADE");
    printf("├──────────────────────────────┼──────────────────┼────────────┤\n");
    
    for (int i = 0; i < tamanho; i++) {
        printf("│ %-28s │ %-16s │ %-10d │\n", 
               componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("└──────────────────────────────┴──────────────────┴────────────┘\n");
}

// Mostrar estatísticas de desempenho
void mostrarEstatisticas(double tempo) {
    printf("\n=== ESTATÍSTICAS DE DESEMPENHO ===\n");
    printf("Comparações realizadas: %d\n", comparacoes);
    printf("Trocas realizadas: %d\n", trocas);
    printf("Tempo de execução: %.6f segundos\n", tempo);
}

// ========== FUNÇÕES DE ENTRADA ==========

// Cadastrar um componente
void cadastrarComponente(Componente componentes[], int* quantidade) {
    if (*quantidade >= MAX_COMPONENTES) {
        printf("\nLimite máximo de componentes atingido! (%d)\n", MAX_COMPONENTES);
        return;
    }
    
    printf("\n=== CADASTRAR COMPONENTE %d/%d ===\n", *quantidade + 1, MAX_COMPONENTES);
    
    printf("Nome do componente: ");
    limparBuffer();
    fgets(componentes[*quantidade].nome, TAM_NOME, stdin);
    componentes[*quantidade].nome[strcspn(componentes[*quantidade].nome, "\n")] = 0;
    
    printf("Tipo (controle/suporte/propulsao): ");
    fgets(componentes[*quantidade].tipo, TAM_TIPO, stdin);
    componentes[*quantidade].tipo[strcspn(componentes[*quantidade].tipo, "\n")] = 0;
    
    printf("Prioridade (1-10): ");
    scanf("%d", &componentes[*quantidade].prioridade);
    
    // Validar prioridade
    if (componentes[*quantidade].prioridade < 1) componentes[*quantidade].prioridade = 1;
    if (componentes[*quantidade].prioridade > 10) componentes[*quantidade].prioridade = 10;
    
    (*quantidade)++;
    printf("✅ Componente cadastrado com sucesso!\n");
}

// ========== FUNÇÃO PARA MEDIR TEMPO ==========

// Medir tempo de execução de um algoritmo
double medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int tamanho) {
    clock_t inicio, fim;
    
    // Fazer cópia do vetor para não alterar o original durante medição
    Componente copia[MAX_COMPONENTES];
    memcpy(copia, componentes, sizeof(Componente) * tamanho);
    
    inicio = clock();
    algoritmo(copia, tamanho);
    fim = clock();
    
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ========== MENUS PRINCIPAIS ==========

// Menu de ordenação
void menuOrdenacao(Componente componentes[], int quantidade) {
    int opcao;
    
    if (quantidade == 0) {
        printf("\n❌ Nenhum componente para ordenar! Cadastre componentes primeiro.\n");
        return;
    }
    
    do {
        printf("\n=== MENU DE ORDENAÇÃO ===\n");
        printf("1. Bubble Sort - Ordenar por NOME\n");
        printf("2. Insertion Sort - Ordenar por TIPO\n");
        printf("3. Selection Sort - Ordenar por PRIORIDADE\n");
        printf("4. Voltar ao menu principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        if (opcao >= 1 && opcao <= 3) {
            double tempo;
            
            switch(opcao) {
                case 1:
                    printf("\n🎯 Executando Bubble Sort por NOME...\n");
                    tempo = medirTempo(bubbleSortNome, componentes, quantidade);
                    bubbleSortNome(componentes, quantidade);
                    break;
                case 2:
                    printf("\n🎯 Executando Insertion Sort por TIPO...\n");
                    tempo = medirTempo(insertionSortTipo, componentes, quantidade);
                    insertionSortTipo(componentes, quantidade);
                    break;
                case 3:
                    printf("\n🎯 Executando Selection Sort por PRIORIDADE...\n");
                    tempo = medirTempo(selectionSortPrioridade, componentes, quantidade);
                    selectionSortPrioridade(componentes, quantidade);
                    break;
            }
            
            mostrarComponentes(componentes, quantidade);
            mostrarEstatisticas(tempo);
        }
        
    } while(opcao != 4);
}

// Menu de busca
void menuBusca(Componente componentes[], int quantidade) {
    if (quantidade == 0) {
        printf("\n❌ Nenhum componente para buscar! Cadastre componentes primeiro.\n");
        return;
    }
    
    char nome[TAM_NOME];
    printf("\n=== BUSCA BINÁRIA - COMPONENTE-CHAVE ===\n");
    printf("Nome do componente a buscar: ");
    limparBuffer();
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    // Verificar se o vetor está ordenado por nome
    int ordenado = 1;
    for (int i = 0; i < quantidade - 1; i++) {
        if (strcmp(componentes[i].nome, componentes[i + 1].nome) > 0) {
            ordenado = 0;
            break;
        }
    }
    
    if (!ordenado) {
        printf("❌ Vetor não está ordenado por nome! Use Bubble Sort primeiro.\n");
        return;
    }
    
    int posicao = buscaBinariaPorNome(componentes, quantidade, nome);
    
    if (posicao != -1) {
        printf("\n✅ COMPONENTE-CHAVE ENCONTRADO!\n");
        printf("Nome: %s\n", componentes[posicao].nome);
        printf("Tipo: %s\n", componentes[posicao].tipo);
        printf("Prioridade: %d\n", componentes[posicao].prioridade);
        printf("Comparações realizadas: %d\n", comparacoes);
        printf("\n🎉 TORRE DE RESGATE ATIVADA! Fuga em andamento...\n");
    } else {
        printf("\n❌ Componente '%s' não encontrado!\n", nome);
        printf("Comparações realizadas: %d\n", comparacoes);
        printf("❌ Torre de resgate não pode ser ativada.\n");
    }
}

// Menu principal
int main() {
    Componente componentes[MAX_COMPONENTES];
    int quantidade = 0;
    int opcao;
    
    printf("=== FREE FIRE - MONTAGEM DA TORRE DE RESGATE ===\n");
    printf("🎯 Nível Mestre: Algoritmos de Ordenação e Busca\n\n");
    
    do {
        printf("=== MENU PRINCIPAL ===\n");
        printf("1. Cadastrar componentes (%d/%d)\n", quantidade, MAX_COMPONENTES);
        printf("2. Ordenar componentes\n");
        printf("3. Buscar componente-chave (Busca Binária)\n");
        printf("4. Mostrar componentes\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarComponente(componentes, &quantidade);
                break;
            case 2:
                menuOrdenacao(componentes, quantidade);
                break;
            case 3:
                menuBusca(componentes, quantidade);
                break;
            case 4:
                mostrarComponentes(componentes, quantidade);
                break;
            case 5:
                printf("\n🎯 Missão concluída! Boa sorte na fuga!\n");
                break;
            default:
                printf("❌ Opção inválida!\n");
        }
        
    } while(opcao != 5);
    
    return 0;
}