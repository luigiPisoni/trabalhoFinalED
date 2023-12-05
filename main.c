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
    while (current != NULL) {
        printf("%d\n", current->producao.codigo);
        current = current->next;
    }
}

void addNode(List* l, Producao p) {
    Node* new = malloc(sizeof(Node));
    new->producao = p;

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

Producao geraProd(int n) { // funcao de teste
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

    for (int i = 0; i < 5; i++) {
        Producao p = geraProd(i);
        addNode(&lista, p);
    }
    printList(&lista);
}