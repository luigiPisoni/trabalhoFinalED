typedef struct data Data;
typedef struct fardo Fardo;
typedef struct producao Producao;
typedef struct node Node;
typedef struct list List;

void initList(List*);
void listaUm(Node* node);
void listaTodos(List* l);
void consulta(List* l, int op);
Node* consultaCodigo(List* l, int key);
void addNode(List* l, Producao p);
void novoProd(List* l, Node* alterar);
void alteraProd(List* l, int key);
void excluiProd(List* l, int key);
Producao geraProd(int n);