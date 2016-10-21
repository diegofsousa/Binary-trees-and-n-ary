#include <stdio.h>
#include <stdlib.h>

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO ArvBin;
ArvBin *raiz;
ArvBin* insere(int n, ArvBin* e, ArvBin* d);
ArvBin *criar();
int pares(ArvBin *a);
int folhas(ArvBin *a);
int um_filho(ArvBin *a);
int igual(ArvBin *a, ArvBin *b);

int main(){
    ArvBin* raiz = criar();
    ArvBin* e1 = criar();
    ArvBin* e2 = criar();
    ArvBin* e3 = criar();
    ArvBin* e4 = criar();
    ArvBin* d1 = criar();

    e1 = insere(15, NULL, NULL);
    e2 = insere(20, NULL, NULL);
    e3 = insere(30, e1, e2);
    e4 = insere(50, NULL, NULL);
    d1 = insere(40, e4, NULL);

    raiz = insere(10, e3, d1);
    ArvBin* r = criar();
    r = insere(10, e3, d1);
    printf("\nQuantidade de nos que guardam numeros pares: %d", pares(raiz));
    printf("\nQuantidade de folhas: %d", folhas(raiz));
    printf("\nQuantidade de folhas com apenas um filho: %d", um_filho(raiz));

    ArvBin *rai = criar();
    ArvBin *a1 = criar();
    ArvBin *a2 = criar();

    a1 = insere(1, NULL, NULL);
    a2 = insere(2, NULL, NULL);
    rai = insere(3, a1, a2);
    printf("\nQuantidade de nos que guardam numeros pares: %d", pares(rai));
    printf("\nQuantidade de folhas: %d", folhas(rai));
    printf("\nQuantidade de folhas com apenas um filho: %d", um_filho(rai));

    printf("\n\nArvores iguais? %d", igual(raiz, r));
    printf("\n\nArvores iguais? %d", igual(raiz, rai));

    return 0;

}

ArvBin* insere(int n, ArvBin* e, ArvBin* d){
    ArvBin* aux = (ArvBin*)malloc(sizeof(ArvBin));
    aux->info = n;
    aux->esq = e;
    aux->dir = d;
    return aux;
}


ArvBin *criar(){
    return NULL;
}

//primeira questão
int pares(ArvBin *a){
    if(a == NULL)
        return 0;
    int alt_esq = pares(a->esq);
    int alt_dir = pares(a->dir);
    int var = 0;
    if(a->info % 2 == 0)
        var = 1;
    return(alt_esq + alt_dir + var);
}

//segunda questão
int folhas(ArvBin *a){
    if(a == NULL)
        return 0;
    int alt_esq = folhas(a->esq);
    int alt_dir = folhas(a->dir);
    int var = 0;
    if(a->esq == NULL || a->dir == NULL)
        var = 1;
    return(alt_esq + alt_dir + var);
}

//terceira questão
int um_filho(ArvBin *a){
    if(a == NULL)
        return 0;
    int alt_esq = um_filho(a->esq);
    int alt_dir = um_filho(a->dir);
    int var = 0;
    if((a->esq == NULL && a->dir != NULL) || (a->esq != NULL && a->dir == NULL))
        var = 1;
    return(alt_esq + alt_dir + var);
}

//quarta questão
int igual(ArvBin *a, ArvBin *b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL || b == NULL)
        return 0;
    return ((a->info == b->info) && igual(a->esq, b->esq) && igual(a->dir, b->dir));
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(raiz);
}
