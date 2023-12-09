#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "header.h"

typedef struct data {
    int dia;
    int mes;
    int ano;
}Data;

typedef struct fardo {
    char cultivar[20];
    char tipoDeFeno;
    int diametro;
}Fardo;

typedef struct producao {
    int codigo;
    Data dataProducao;
    Fardo tipoDeFardo;
    int qtDeFardos;
    float duracao;
}Producao;

typedef struct node {
    Producao producao;

    struct node* previous, * next;
}Node;

typedef struct list {
    Node* head, * tail;
}List;

void initList(List* l) {
    l->head = NULL;
    l->tail = NULL;
}

void printList(List* l) {
    Node* current = l->head;
    if (current == NULL) { printf("\n(!) Nenhuma producao registrada.\n"); return; }
    printf("LISTAGEM:\n");
    while (current != NULL) {
        printf("\tCodigo: %d\n", current->producao.codigo);
        printf("\tData: %d/%d/%d\n",
            current->producao.dataProducao.dia,
            current->producao.dataProducao.mes,
            current->producao.dataProducao.ano);
        printf("\tDuracao: %.2f\n", current->producao.duracao);
        printf("\tN de Fardos: %d\n", current->producao.qtDeFardos);
        printf("\tCultivar: %s\n", current->producao.tipoDeFardo.cultivar);
        printf("\tDiametro: %.2f\n", current->producao.tipoDeFardo.diametro);
        printf("\tTipo de Feno: %c\n", current->producao.tipoDeFardo.tipoDeFeno);
        printf("\t\t------\n");

        current = current->next;
    }
}

void addNode(List* l, Producao p) {
    Node* new = malloc(sizeof(Node));
    // printf("%d", p.codigo);
    // printf("--%x--", l);
    new->producao = p;
    // printf("%d", new->producao.codigo);
    new->previous = NULL;
    new->next = NULL;
    if (l->head == NULL) { // se a lista estiver vazia
        l->head = new;
        l->tail = new;
    }
    else {
        l->tail->next = new; // aponta o next do último para o novo
        l->tail = new; // agora o novo é o último
    }
}

void newProd(List* l) {
    Producao newProd;
    printf("Insira os dados da producao:\n");
    printf("\tCodigo:");
    scanf("%d", &newProd.codigo);
    if (l->head != NULL) { // verifica se o codigo ja existe
        Node* current = l->head;
        while (current != NULL)
        {
            if (current->producao.codigo == newProd.codigo) { break; }
            current = current->next;
        }
        if (current != NULL) { // se entrar aqui, quer dizer que encontrou
            printf("(!) Ja existe uma producao com esse codigo.\n");
            return;
        }
    }
    printf("\tDia:");
    scanf("%d", &newProd.dataProducao.dia);
    printf("\tMes:");
    scanf("%d", &newProd.dataProducao.mes);
    printf("\tAno:");
    scanf("%d", &newProd.dataProducao.ano);

    printf("\tDuracao:");
    scanf("%f", &newProd.duracao);
    printf("\tQuantidade de fardos:");
    scanf("%d", &newProd.qtDeFardos);

    printf("\tCultivar:");
    scanf("%s", &newProd.tipoDeFardo.cultivar);
    printf("\tDiametro do fardo:");
    scanf("%f", &newProd.tipoDeFardo.diametro);
    printf("\tTipo de feno:");
    scanf("\n%c", &newProd.tipoDeFardo.tipoDeFeno);

    addNode(l, newProd);
}

void consultar(List* l, int op) {
    if (op != 1 && op != 2) { return; }
    if (op == 1) { // consulta por data
        printf("CONSULTA POR DATA\n");
        Data toFind;

        printf("\tDia: ");
        scanf("%d", &toFind.dia);
        printf("\tMes: ");
        scanf("%d", &toFind.mes);
        printf("\tAno: ");
        scanf("%d", &toFind.ano);

        Node* current = l->head;
        while (current != NULL) {
            if (current->producao.dataProducao.dia == toFind.dia
                && current->producao.dataProducao.mes == toFind.mes
                && current->producao.dataProducao.ano == toFind.ano) { // cai aqui se tiver a mesma data
                printf("\n-> %d/%d/%d: %s - %c - %d\n", toFind.dia,
                    toFind.mes,
                    toFind.ano,
                    current->producao.tipoDeFardo.cultivar,
                    current->producao.tipoDeFardo.tipoDeFeno,
                    current->producao.qtDeFardos);
                break;
            }
            current = current->next;
        }
        if (current == NULL) { printf("(!) Nao ha producao nesse dia."); }

    }
}

Producao geraProd(int n) { // gera uma prod
    Producao p;
    p.codigo = n;

    p.dataProducao.ano = 2000 + n;
    p.dataProducao.mes = 1 + n;
    p.dataProducao.dia = 3 + n;

    p.duracao = 10 + (n * 5);
    p.qtDeFardos = n * 7;

    strcpy(p.tipoDeFardo.cultivar, "TesteFenoBagual");
    p.tipoDeFardo.diametro = 1.5 * (n + 1);
    p.tipoDeFardo.tipoDeFeno = 'A';

    return p;
}

int main() {
    List lista;
    initList(&lista);

    for (int i = 0; i < 5; i++) { // popula a lista
        Producao p = geraProd(i);
        addNode(&lista, p);
    }

    while (1)
    {
        printf("\nMENU PRINCIPAL - Escolha uma opcao\n");
        printf("\t1. Incluir producao\n");
        printf("\t2. Consultar\n");
        printf("\t3. Alterar\n");
        printf("\t4. Excluir\n");
        printf("\t5. Listar todos\n");
        printf("\t6. Sair\n>");

        int op;
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            newProd(&lista);
            break;
        case 2:
            printf("Pesquisa por:\n 1. Data\n 2. Cultivar\n>");
            scanf("%d", &op);
            consultar(&lista, op);
            break;
        case 5:
            printList(&lista);
            break;
        case 6:
            return 0;
        default:
            printf("(!) Opcao invalida\n");
            break;
        }
    }
}