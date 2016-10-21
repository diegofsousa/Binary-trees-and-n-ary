#include <stdlib.h>
#include <stdio.h>

struct no_arvBinB{
    int info;
    struct no_arvBinB *esq;
    struct no_arvBinB *dir;
};

typedef struct no_arvBinB ArvBinB;
ArvBinB *raiz;

ArvBinB *criar();
ArvBinB *busca(ArvBinB *raiz, int v);
ArvBinB *arvbb_busca(ArvBinB *raiz, int v);
void imprime_em_ordem(ArvBinB *r);
void abb_imprime(ArvBinB *raiz);
void desaloca(ArvBinB *r);
void arvbb_desaloca(ArvBinB *raiz);
ArvBinB *insere(ArvBinB *r, int v);
void arvbb_insere(ArvBinB* raiz, int v);
int nfolhas_maiores(ArvBinB *a, int x);
int soma_xy(ArvBinB* a, int x, int y);
int nivel(ArvBinB* a, int x);
void arvbb_retira(ArvBinB *a, int v);
ArvBinB *retira(ArvBinB *r, int v);

int main(){
    printf("Hello world");

    ArvBinB *raiz = insere(NULL, 4);
    arvbb_insere(raiz, 10);
    arvbb_insere(raiz, 2);
    arvbb_insere(raiz, 7);
    arvbb_insere(raiz, 18);
    arvbb_insere(raiz, 1);
    arvbb_insere(raiz, 3);
    arvbb_insere(raiz, 15);
    arvbb_insere(raiz, 20);

    abb_imprime(raiz);
    int valor = 90;
    printf("\nTemos %d valores maiores que %d", nfolhas_maiores(raiz, valor), valor);
    printf("\nSomatório: %d", soma_xy(raiz, 40, 45));
    printf("\nNível: %d", nivel(raiz, 40));
    arvbb_retira(raiz, 2);
    abb_imprime(raiz);

    return 0;
}

ArvBinB *criar(){
    return NULL;
}

ArvBinB *busca(ArvBinB *raiz, int v){
    if (raiz == NULL)
        return NULL;
    else if(raiz->info > v)
        return busca (raiz->esq, v);
    else if(raiz->info < v)
        return busca (raiz->dir, v);
    else return raiz;
}

ArvBinB *arvbb_busca(ArvBinB *raiz, int v){
    return busca(raiz, v);
}

void imprime_em_ordem(ArvBinB *r){
    if(r!=NULL){
        imprime_em_ordem(r->esq);
        printf("\n   >>> %d", r->info);
        imprime_em_ordem(r->dir);
    }
}

void abb_imprime(ArvBinB *raiz){
    return imprime_em_ordem(raiz);
}

void desaloca(ArvBinB *r){
    if(r!=NULL){
        desaloca(r->esq);
        desaloca(r->dir);
        free(r);
    }
}

void arvbb_desaloca(ArvBinB *raiz){
    desaloca(raiz);
}

ArvBinB *insere(ArvBinB *r, int v){
    if(r == NULL){
        r = (ArvBinB*)malloc(sizeof(ArvBinB));
        r->info = v;
        r->esq = r->dir = NULL;
    }
    else if(v < r->info)
        r->esq = insere(r->esq, v);
    else
        r->dir = insere(r->dir, v);
    return r;
}

void arvbb_insere(ArvBinB* raiz, int v){
    raiz = insere(raiz, v);
}

//sexta questão
int nfolhas_maiores(ArvBinB *a, int x){
    if(a == NULL)
        return 0;
    int esquerda = nfolhas_maiores(a->esq, x);
    int direita = nfolhas_maiores(a->dir, x);
    int var = 0;
    if(a->info > x)
        var = 1;
    else
        var = 0;
    return(esquerda + direita + var);
}

//sétima questão
int soma_xy(ArvBinB* a, int x, int y){
    if(a == NULL)
        return 0;
    int esquerda = soma_xy(a->esq, x, y);
    int direita = soma_xy(a->dir, x, y);
    int var = 0;
    if(a->info <= y && a->info >= x)
        var = a->info;
    return(esquerda + direita + var);
}

//oitava questão
int nivel(ArvBinB* a, int x){
    if(a == NULL)return 0;
    if(x < a->info)return nivel(a->esq, x) + 1;
    else if(x > a->info)return nivel(a->dir, x) + 1;
    else if(x == a->info)return 1;
}

void arvbb_retira(ArvBinB *raiz, int v){
    retira(raiz, v);
}

ArvBinB *retira(ArvBinB *r, int v){
    if(r == NULL)
        return NULL;
    else if(r->info > v)
        r->esq = retira(r->esq, v);
    else if(r->info < v)
        r->dir = retira(r->dir, v);
    else{
        if(r->esq == NULL && r->dir == NULL){
            free(r);
            r = NULL;
        }
        else if(r->esq == NULL){
            ArvBinB *t = r;
            r = r->dir;
            free(t);
        }
        else if(r->dir == NULL){
            ArvBinB *t = r;
            r = r->esq;
            free(t);
        }
        else{
            ArvBinB *f = r->esq;
            while(f->dir != NULL){
                f = f->dir;
            }
            r->info = f->info;
            f->info = v;
            r->esq = retira(r->esq, v);
        }
    }
    return r;
}
