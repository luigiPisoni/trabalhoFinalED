#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void listaUm(Node* node) {
    printf("\tCodigo: %d\n", node->producao.codigo);
    printf("\tData: %d/%d/%d\n",
        node->producao.dataProducao.dia,
        node->producao.dataProducao.mes,
        node->producao.dataProducao.ano);
    printf("\tDuracao: %.2f\n", node->producao.duracao);
    printf("\tN de Fardos: %d\n", node->producao.qtDeFardos);
    printf("\tCultivar: %s\n", node->producao.tipoDeFardo.cultivar);
    printf("\tDiametro: %d\n", node->producao.tipoDeFardo.diametro);
    printf("\tTipo de Feno: %c\n", node->producao.tipoDeFardo.tipoDeFeno);
    printf("\t\t------\n");
}

void listaTodos(List* l) {
    Node* current = l->head;
    if (current == NULL) { printf("\n(!) Nenhuma producao registrada.\n"); return; }
    printf("LISTAGEM:\n");
    while (current != NULL) {
        listaUm(current);

        current = current->next;
    }
}

void consulta(List* l, int op) {
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
    else {
        Node* current = l->head;
        printf("CONSULTA POR CULTIVO");
        char cultivo[20];
        char cultivoLower[20];
        char currentLower[20];
        char cultivoCurrent[20];
        int somaA = 0, somaB = 0, somaC = 0, b = 0, c = 0;
        printf("\nCultivo para busca: ");
        scanf("%s", &cultivo);
        for (int i = 0; i < 20; i++)
        {
            cultivoLower[i] = tolower(cultivo[i]);
        }
        while (current != NULL)
        {
            for (int i = 0; i < 20; i++)
            {
                currentLower[i] = tolower(current->producao.tipoDeFardo.cultivar[i]);
            }
            int compare = strcmp(currentLower, cultivoLower);
            if (compare == 0) // cai aqui se o cultivo em lower case for igual ao cultivo cadastrado
            {
                strcpy(cultivoCurrent, current->producao.tipoDeFardo.cultivar);
                if (current->producao.tipoDeFardo.tipoDeFeno == 'A')
                {
                    somaA += current->producao.qtDeFardos;
                }
                else if (current->producao.tipoDeFardo.tipoDeFeno == 'B')
                {
                    somaB += current->producao.qtDeFardos;
                    b = 1;
                }
                else if (current->producao.tipoDeFardo.tipoDeFeno == 'C')
                {
                    somaC += current->producao.qtDeFardos;
                    c = 1;
                }
            }
            current = current->next;
        }
        if (somaA != 0)
        {
            printf("\n->%s: %c - %d\n", cultivoCurrent, 'A', somaA);
        }
        if (somaB != 0)
        {
            if (b == 1) printf("\n");
            printf("\n->%s: %c - %d\n", cultivoCurrent, 'B', somaB);
        }
        if (somaC != 0)
        {
            if (c == 1) printf("\n");
            printf("\n->%s: %c - %d\n", cultivoCurrent, 'C', somaC);
        }

        if (somaA == 0 && somaB == 0 && somaC == 0) printf("(!) Nao foi encontrado Cultivo: %s na lista.", cultivo);


    }

}

Node* consultaCodigo(List* l, int key) {
    Node* current = l->head;
    if (current == NULL) { return current; } //se a lista estiver vazia nem procura
    while (current != NULL) {
        if (current->producao.codigo == key) { break; }// vai sair do loop com o objeto encontrado
        current = current->next;
    }
    return current; // retorna NULL se não tiver encontrado ou o ponteiro do nodo
}

void addNode(List* l, Producao p) { // apenas adiciona um novo nodo na lista
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

void novoProd(List* l, Node* alterar) { // se receber o alterar vai modificar o produto do endereco alterar
    Producao newProd;
    printf("Insira os dados da producao:\n");
    if (alterar == NULL) {
        printf("\tCodigo:");
        scanf("%d", &newProd.codigo);
        Node* found = consultaCodigo(l, newProd.codigo);
        if (found != NULL) {
            printf("\n(!) Ja existe uma producao com esse codigo.\n");
            return;
        }
    }
    else {
        newProd.codigo = alterar->producao.codigo;
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
    scanf(" %[^\n]s", &newProd.tipoDeFardo.cultivar); // esse scanf esquisito le a linha toda
    printf("\tDiametro do fardo:");
    scanf("%d", &newProd.tipoDeFardo.diametro);
    printf("\tTipo de feno:");
    scanf(" %c", &newProd.tipoDeFardo.tipoDeFeno);

    if (alterar == NULL) {
        addNode(l, newProd);
        printf("\n\tInserido com sucesso.");
    }
    else {
        Node* edited = consultaCodigo(l, alterar->producao.codigo);
        edited->producao = newProd;
        printf("\n\tAlterado com sucesso.\n");
    }
}

void alteraProd(List* l, int key) { //vai reutilizar a funcao de newProd
    Node* found = consultaCodigo(l, key);
    if (found == NULL) {
        printf("\n(!) Codigo nao encontrado\n");
        return;
    }
    novoProd(l, found);
}

void excluiProd(List* l, int key) {
    Node* found = consultaCodigo(l, key);
    if (found == NULL) {
        printf("\n(!) Codigo nao encontrado\n");
        return;
    }

    if (found->previous == NULL) { // se for o primeiro
        found->next->previous == NULL;
        l->head = found->next;
        free(found);
    }
    else if (found->next == NULL) { // se for o ultimo
        found->previous->next == NULL;
        l->tail = found->previous;
        free(found);
    }
    else { // se tiver no meio
        found->next->previous = found->previous;
        found->previous->next = found->next;
        free(found);
    }

    printf("\nProducao excluida com sucesso\n");
}

Producao geraProd(int n) { // gera n prod pra teste
    Producao p;
    p.codigo = n;

    p.dataProducao.ano = 2000 + n;
    p.dataProducao.mes = 1 + n;
    p.dataProducao.dia = 3 + n;

    p.duracao = 10 + (n * 5);
    p.qtDeFardos = n * 7;

    strcpy(p.tipoDeFardo.cultivar, "TesteFenoBagual");
    p.tipoDeFardo.diametro = 3 * (n + 1);
    p.tipoDeFardo.tipoDeFeno = 'A';

    return p;
}

int main() {
    List lista;
    initList(&lista);

    for (int i = 0; i < 2; i++) { // popula a lista
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
        scanf(" %d", &op);
        switch (op)
        {
        case 1:
            novoProd(&lista, NULL);
            break;
        case 2:
            printf("Pesquisa por:\n 1. Data\n 2. Cultivar\n>");
            scanf("%d", &op);
            consulta(&lista, op);
            break;
        case 3:
            printf("Alterar - Codigo:");
            scanf("%d", &op);
            alteraProd(&lista, op);
            break;
        case 4:
            printf("Excluir - Codigo:");
            scanf("%d", &op);
            excluiProd(&lista, op);
            break;
        case 5:
            listaTodos(&lista);
            break;
        case 6:
            return 0;
        default:
            printf("(!) Opcao invalida\n");
            continue;
        }
    }
}