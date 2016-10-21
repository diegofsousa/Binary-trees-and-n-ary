#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct arv {
    char op;
    float valor;
    struct arv *esq, *dir;
};

typedef struct arv ArvBin;

ArvBin* raiz;
ArvBin* insereOp(char n, ArvBin* e, ArvBin* d);
ArvBin* insereValor(float n, ArvBin* e, ArvBin* d);
ArvBin* criar();
void imprimir_em_ordem(ArvBin* r);
void imprime_Expre(ArvBin* a);
float avalia(ArvBin *a);

int main(){
    ArvBin* raiz = criar();
    ArvBin* e1 = criar();
    ArvBin* e2 = criar();
    ArvBin* e3 = criar();
    ArvBin* e4 = criar();
    ArvBin* e5 = criar();
    ArvBin* e6 = criar();
    ArvBin* e7 = criar();
    ArvBin* e8 = criar();

    e1 = insereValor(6, NULL, NULL);
    e2 = insereValor(3, NULL, NULL);
    e3 = insereValor(4, NULL, NULL);
    e4 = insereValor(1, NULL, NULL);
    e5 = insereOp('-', e1, e2);
    e6 = insereOp('+', e3, e4);
    e7 = insereOp('*', e5, e6);
    e8 = insereValor(5, NULL, NULL);
    raiz = insereOp('+', e7, e8);

    imprimir_em_ordem(raiz);
    printf("\n");
    imprime_Expre(raiz);
    printf("\nValor: %f", avalia(raiz));

    return 0;
}

ArvBin* insereOp(char n, ArvBin* e, ArvBin* d){
    ArvBin* aux = (ArvBin*)malloc(sizeof(ArvBin));
    aux->op = n;
    aux->esq = e;
    aux->dir = d;
    return aux;
}

ArvBin* insereValor(float n, ArvBin* e, ArvBin* d){
    ArvBin* aux = (ArvBin*)malloc(sizeof(ArvBin));
    aux->valor = n;
    aux->esq = e;
    aux->dir = d;
    return aux;
}

ArvBin *criar(){
    return NULL;
}

void imprimir_em_ordem(ArvBin* r){
    if( r != NULL ){
        imprimir_em_ordem(r->esq);
        if(r->op)
            printf("%c", r->op);
        else
            printf("%.0f", r->valor);
        imprimir_em_ordem(r->dir);
    }
}

//letra a
void imprime_Expre(ArvBin* a){
    if(a != NULL){
        imprime_Expre(a->esq);
        imprime_Expre(a->dir);
        if(a->op)
            printf("%c", a->op);
        else
            printf("%.0f", a->valor);
    }
}

//letra b
float avalia(ArvBin *a){
    if(a == NULL)
        return 0;
    float esquerda = avalia(a->esq);
    float direita = avalia(a->dir);
    if(a->op == '+'){
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return a->esq->valor + a->dir->valor;
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq != NULL && a->dir->dir != NULL))
            return a->esq->valor + direita;
        if((a->esq->esq != NULL && a->esq->dir != NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return esquerda + a->dir->valor;
        return(esquerda + direita);
    }
    else if(a->op == '-'){
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return a->esq->valor - a->dir->valor;
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq != NULL && a->dir->dir != NULL))
            return a->esq->valor - direita;
        if((a->esq->esq != NULL && a->esq->dir != NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return esquerda - a->dir->valor;
        return(esquerda - direita);
    }
    else if(a->op == '*'){
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return a->esq->valor * a->dir->valor;
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq != NULL && a->dir->dir != NULL))
            return a->esq->valor * direita;
        if((a->esq->esq != NULL && a->esq->dir != NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return esquerda * a->dir->valor;
        return(esquerda * direita);
    }
    else if(a->op == '/'){
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return a->esq->valor / a->dir->valor;
        if((a->esq->esq == NULL && a->esq->dir == NULL) && (a->dir->esq != NULL && a->dir->dir != NULL))
            return a->esq->valor / direita;
        if((a->esq->esq != NULL && a->esq->dir != NULL) && (a->dir->esq == NULL && a->dir->dir == NULL))
            return esquerda / a->dir->valor;
        return(esquerda / direita);
    }
}
