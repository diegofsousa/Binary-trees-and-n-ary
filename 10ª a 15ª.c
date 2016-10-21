#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arv_var ArvVar;
typedef struct arvv_no ArvVarNo;

struct arvv_no{
    int info;
    ArvVarNo *prim;
    ArvVarNo *prox;
};

struct arv_var{
    ArvVarNo *raiz;
};

typedef struct no_arvBin ArvBin;

struct no_arvBin{
    int info;
    ArvBin *esq;
    ArvBin *dir;
};

ArvVarNo *arvV_criaNo(int c);
void arvV_insere(ArvVarNo *a, ArvVarNo *sa);
ArvVar *arvV_cria(ArvVarNo *r);
void arvV_imprime(ArvVar *a);
void imprime(ArvVarNo *r);
ArvVarNo *arvV_busca(ArvVar *a, int c);
void arvV_libera(ArvVar *a);
int impares(ArvVar *a);
int conta_impar(ArvVarNo *r);
int quant_folhas(ArvVarNo *r);
int arvv_folhas(ArvVar* a);
int quant_uma_folha(ArvVarNo *r);
int um_filho_arvv (ArvVar* a);
int arvv_igual (ArvVar* a, ArvVar* b);
int verifica_igualdade(ArvVarNo* a, ArvVarNo* b);
ArvVar* arvv_pai(ArvVar* a, int no);
ArvVarNo *busca_pai(ArvVarNo *r, int no);
int percorre_lista(ArvVarNo *r, int no);
ArvBin* transformaBin(ArvVar* a);
void para_bin(ArvVarNo *var, ArvBin *bin);
ArvBin *criar();

int main (){
    ArvVarNo *a = arvV_criaNo(1);
    ArvVarNo *b = arvV_criaNo(2);
    ArvVarNo *c = arvV_criaNo(3);
    ArvVarNo *d = arvV_criaNo(4);
    ArvVarNo *e = arvV_criaNo(5);
    ArvVarNo *f = arvV_criaNo(6);
    ArvVarNo *g = arvV_criaNo(7);
    ArvVarNo *h = arvV_criaNo(8);
    ArvVarNo *i = arvV_criaNo(9);
    ArvVarNo *j = arvV_criaNo(10);

    arvV_insere(c,d);
    arvV_insere(b,e);
    arvV_insere(b,c);
    arvV_insere(i,j);
    arvV_insere(g,i);
    arvV_insere(g,h);
    arvV_insere(a,g);
    arvV_insere(a,f);
    arvV_insere(a,b);

    ArvVar *arvore =arvV_cria(a);
    arvV_imprime(arvore);
    printf("\nNumeros impares: %d", impares(arvore));
    printf("\nQuantidade de folhas na arvore: %d", arvv_folhas(arvore));
    printf("\nQuantidade de nós com apenas um filho: %d", um_filho_arvv(arvore));
    printf("\nArvores são iguais? %d", arvv_igual(arvore, arvore));
    printf("\nO pai desse no eh: %d", arvv_pai(arvore, 5));
    ArvBin *t = transformaBin(arvore);
    return 0;
}

ArvVarNo *arvV_criaNo(int c){
    ArvVarNo *a = (ArvVarNo*)malloc(sizeof(ArvVarNo*));
    a->info = c;
    a->prim = NULL;
    a->prox = NULL;
    return a;
}

ArvVar *arvV_cria(ArvVarNo *r){
    ArvVar *a = (ArvVar*)malloc(sizeof(ArvVar));
    a->raiz = r;
    return a;
}

void arvV_insere(ArvVarNo *a, ArvVarNo *sa){
    sa->prox = a->prim;
    a->prim = sa;
}

void arvV_imprime(ArvVar *a){
    if(a->raiz != NULL)
        imprime(a->raiz);
}

void imprime(ArvVarNo *r){
    printf("<%d", r->info);
    ArvVarNo *p = r->prim;
    while(p!=NULL){
        imprime(p);
        printf(">");
        p = p->prox;
    }
}

//décima questão
int impares(ArvVar *a){
    return conta_impar(a->raiz);
}

int conta_impar(ArvVarNo *r){
    if (r == NULL)return 0;int var = 0;
    if (r->info % 2 != 0)
        var = 1;
    return conta_impar(r->prox) + conta_impar(r->prim) + var;
}

//decima primeira questão
int arvv_folhas(ArvVar* a){
    return quant_folhas(a->raiz);
}

int quant_folhas(ArvVarNo *r){
    if (r == NULL)return 0;
    int var = 0;
    if (r->prim == NULL)
        var = 1;
    return quant_folhas(r->prox) + quant_folhas(r->prim) + var;
}

//décima segunda questão
int um_filho_arvv (ArvVar* a){
    return quant_uma_folha(a->raiz);
}

int quant_uma_folha(ArvVarNo *r){
    if(r == NULL)return 0;
    int var = 0;
    if(r->prim != NULL && r->prim->prox == NULL)
        var = 1;
    return quant_uma_folha(r->prox) + quant_uma_folha(r->prim) + var;
}

//decima terceira questão
int arvv_igual (ArvVar* a, ArvVar* b){
    return verifica_igualdade(a->raiz, b->raiz);
}

int verifica_igualdade(ArvVarNo* a, ArvVarNo* b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL || b == NULL)
        return 0;
    return ((a->info == b->info) && verifica_igualdade(a->prox, b->prox) && verifica_igualdade(a->prim, b->prim));
}

//décima quarta questão
ArvVar* arvv_pai(ArvVar* a, int no){
    if (a->raiz->info == no)
        return NULL;
    ArvVarNo *pai = busca_pai(a->raiz, no);
    return pai;
}

ArvVarNo *busca_pai(ArvVarNo *r, int no){
    if (r == NULL)
        return NULL;
    else if (percorre_lista(r->prim, no) == 1)
        return r->info;
}

int percorre_lista(ArvVarNo *r, int no){
    int peso = 0;
    ArvVarNo *aux = r;
    while(aux != NULL){
        if(aux->info == no)
            peso = 1;
        aux = aux->prox;
    }
    if(peso == 1)
        return peso;
    else{
        ArvVarNo *aux = r;
        while(aux != NULL){
            if (aux->prim != NULL)
                if (busca_pai(aux, no) != NULL)return;
            aux = aux->prox;
        }
    }
}


//décima quinta questão
ArvBin* transformaBin (ArvVar* a){
    ArvBin *raizb;
    para_bin(a->raiz, raizb);
    return raizb;
}


void para_bin(ArvVarNo *var, ArvBin *bin){
    if (var != NULL){
        ArvBin *no = (ArvBin*)malloc(sizeof(ArvBin));
        no->info = var->info;
        no->esq = NULL;
        no->dir = NULL;
        bin = no;
        para_bin(var->prim, bin->esq);
        para_bin(var->prox, bin->dir);
    }
}

