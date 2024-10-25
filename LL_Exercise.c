#include <stdio.h>
#include <stdlib.h>

// Alexandre Ribeiro de Souza - 10417845

struct reg {
    int conteudo;
    struct reg *prox;
};
typedef struct reg celula;

// Função para criar uma nova célula
celula* cria_celula(int valor) {
    celula* nova = (celula*)malloc(sizeof(celula)); 
    if (nova == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    nova->conteudo = valor;
    nova->prox = NULL;
    return nova;
}

// Função para adicionar uma célula
celula* adiciona_celula(celula* inicio, int valor) {
    celula* nova = cria_celula(valor);
    if (inicio == NULL) {
        return nova;
    }
    celula* p = inicio;
    while (p->prox != NULL) {
        p = p->prox;
    }
    p->prox = nova;
    return inicio;
}

// Função para imprimir os valores da lista
void imprime_lista(celula* inicio) {
    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    celula* p = inicio;
    while (p != NULL) {
        printf("%d -> ", p->conteudo);
        p = p->prox;
    }
    printf("NULL\n");
}

// Função para liberar a lista e a memória alocada
void libera_lista(celula* inicio) {
    celula* p = inicio;
    while (p != NULL) {
        celula* temp = p;
        p = p->prox;
        free(temp); 
    }
}

// Função para remover um elemento pelo valor
celula* remove_elemento(celula* inicio, int valor) {
    if (inicio == NULL) {
        printf("A lista está vazia!\n");
        return NULL;
    }

    celula* atual = inicio;
    celula* anterior = NULL;

    while (atual != NULL && atual->conteudo != valor) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Elemento %d não encontrado na lista.\n", valor);
        return inicio;
    }

    if (anterior == NULL) {
        celula* nova_lista = inicio->prox;
        free(inicio);
        return nova_lista;
    }

    anterior->prox = atual->prox;
    free(atual);
    return inicio;
}

// Função para calcular o número máximo de elementos
unsigned long max_elementos(size_t memoria_disponivel) {
    return memoria_disponivel / sizeof(celula);
}

// Menu principal
int main() {
    celula* lista = NULL;
    int opcao, valor;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar valor à lista\n");
        printf("2. Imprimir lista\n");
        printf("3. Remover valor da lista\n");
        printf("4. Calcular memória por célula\n");
        printf("5. Estimar número máximo de elementos (1GB de memória)\n");
        printf("6. Liberar lista e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                lista = adiciona_celula(lista, valor);
                break;
            case 2:
                printf("Lista atual:\n");
                imprime_lista(lista);
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                lista = remove_elemento(lista, valor);
                break;
            case 4:
                printf("Memória gasta por célula: %lu bytes\n", sizeof(celula));
                break;
            case 5:
                printf("Número máximo de elementos com 1GB de memória: %lu\n", max_elementos(1024 * 1024 * 1024));
                break;
            case 6:
                libera_lista(lista);
                printf("Lista liberada e saindo do programa.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 6);

    return 0;
}
