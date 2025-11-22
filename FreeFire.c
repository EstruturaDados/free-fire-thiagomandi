#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura Item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Vetor para armazenar os itens e contador de itens cadastrados
Item listaDeItens[MAX_ITENS];
int contadorItens = 0;

// Protótipos das funções
void menu();
void cadastrarItem();
void listarItens();
void buscarItem();
void removerItem();
int encontrarIndicePorNome(const char* nome);

int main() {
    menu();
    return 0;
}

// Funções
//Menu principal
void menu() {
    int opcao;
    do {
        printf("\n--- Sistema de Cadastro de Itens ---\n");
        printf("1. Cadastrar novo item\n");
        printf("2. Listar todos os itens\n");
        printf("3. Buscar item por nome\n");
        printf("4. Remover item por nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        while (getchar() != '\n'); //Limpa o buffer

        switch (opcao) {
            case 1:
                cadastrarItem();
                break;
            case 2:
                listarItens();
                break;
            case 3:
                buscarItem();
                break;
            case 4:
                removerItem();
                break;
            case 0:
                printf("Saindo do sistema. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

//Cadastra item na lista, se houver espaço.
void cadastrarItem() {
    if (contadorItens >= MAX_ITENS) {
        printf("Erro: A lista esta cheia. Maximo de %d itens atingido.\n", MAX_ITENS);
        return;
    }
    Item novoItem;
    printf("\n--- Cadastro de Novo Item ---\n");
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0';

    printf("Digite o tipo do item: ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    // Limpar buffer apos scanf
    while (getchar() != '\n'); 
    // Adicionar o novo item ao vetor
    listaDeItens[contadorItens] = novoItem;
    contadorItens++;

    printf("Item cadastrado com sucesso!\n");
}

//Listar itens cadastrados.
void listarItens() {
    if (contadorItens == 0) {
        printf("\nNenhum item cadastrado.\n");
        return;
    }

    printf("\n--- Itens Cadastrados (%d/%d) ---\n", contadorItens, MAX_ITENS);
    for (int i = 0; i < contadorItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", listaDeItens[i].nome);
        printf("  Tipo: %s\n", listaDeItens[i].tipo);
        printf("  Quantidade: %d\n", listaDeItens[i].quantidade);
    }
}

//Buscar item pelo nome e exibir dados.
void buscarItem() {
    char nomeBusca[30];
    printf("\n--- Buscar Item por Nome ---\n");
    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int indice = encontrarIndicePorNome(nomeBusca);
    if (indice != -1) {
        printf("Item encontrado:\n");
        printf("  Nome: %s\n", listaDeItens[indice].nome);
        printf("  Tipo: %s\n", listaDeItens[indice].tipo);
        printf("  Quantidade: %d\n", listaDeItens[indice].quantidade);
    } else {
        printf("Item com nome '%s' não encontrado.\n", nomeBusca);
    }
}

//Remover item pelo nome e listar itens restantes.
void removerItem() {
    char nomeRemover[30];
    printf("\n--- Remover Item por Nome ---\n");
    printf("Digite o nome do item que deseja remover: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int indice = encontrarIndicePorNome(nomeRemover);

    if (indice != -1) {
        // Mover os elementos para a posição que está vazia
        for (int i = indice; i < contadorItens - 1; i++) {
            listaDeItens[i] = listaDeItens[i + 1];
        }
        contadorItens--;
        printf("Item '%s' removido com sucesso!\n", nomeRemover);
        // Exibir os itens após a remoção
        listarItens(); 
    } else {
        printf("Item com nome '%s' não encontrado.\n", nomeRemover);
    }
}

// Função para encontrar item pelo nome
int encontrarIndicePorNome(const char* nome) {
    for (int i = 0; i < contadorItens; i++) {
        if (strcmp(listaDeItens[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}