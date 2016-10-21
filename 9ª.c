#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct aluno Aluno;
struct aluno{
    char nome[81];
    float p1, p2, p3;
};

typedef struct arvBinB ArvBinB;
typedef struct no_arvBinB ArvBinB_No;

struct no_arvBinB {
    Aluno info;
    ArvBinB_No* esq;
    ArvBinB_No* dir;
};

struct arvBinB{
    ArvBinB_No * raiz;
};

ArvBinB *aa_cria();
ArvBinB_No *insere(ArvBinB_No *a, char *nome, float p1, float p2, float p3);
void aa_insere (ArvBinB* a, char* nome, float p1, float p2, float p3);
void abb_imprime(ArvBinB *a);
void imprime_em_ordem(ArvBinB_No *a);
float aa_media (ArvBinB* a, char* nome);
ArvBinB_No *busca_media(ArvBinB_No *a, char *nome);
void aa_retira(ArvBinB *a, char *nome);
ArvBinB_No *retira(ArvBinB_No *r, char *nome);
void aa_libera(ArvBinB *a);
void desaloca(ArvBinB_No *r);


int main(){
    ArvBinB *r = aa_cria();
    aa_insere(r, "diego", 8,9,10);
    aa_insere(r, "leticia", 8.4,4.5,10);
    aa_insere(r, "lohayne", 9.6,8.8,10);
    abb_imprime(r);
    printf("\n\nMedia: %f", aa_media(r, "diego"));
    aa_retira(r, "lohayne");
    abb_imprime(r);
    aa_libera(r);
    abb_imprime(r);
    return 0;
}

//letra a
ArvBinB *aa_cria(){
    ArvBinB *a = (ArvBinB*)malloc(sizeof(ArvBinB));
    a->raiz = NULL;
    return a;
}

//letra b
void aa_insere (ArvBinB* a, char* nome, float p1, float p2, float p3){
    a->raiz = insere(a->raiz, nome, p1, p2, p3);
}

ArvBinB_No *insere(ArvBinB_No *a, char *nome, float p1, float p2, float p3){
    if(a == NULL){
        a = (ArvBinB_No*)malloc(sizeof(ArvBinB_No));
        strcpy(a->info.nome, nome);
        a->info.p1 = p1;
        a->info.p2 = p2;
        a->info.p3 = p3;
        a->dir = a->esq = NULL;
    }
    else if((p1+p2+p3) < (a->info.p1+a->info.p2+a->info.p3))
        a->esq = insere(a->esq, nome, p1, p2, p3);
    else
        a->dir = insere(a->dir, nome, p1, p2, p3);
    return a;
}

void abb_imprime(ArvBinB *a){
    return imprime_em_ordem(a->raiz);
}

void imprime_em_ordem(ArvBinB_No *a){
    if(a != NULL){
        imprime_em_ordem(a->esq);
        printf("\n%s", a->info.nome);
        printf("\t%.1f\t%.1f\t%.1f", a->info.p1, a->info.p2, a->info.p3);
        imprime_em_ordem(a->dir);
    }
}

//letra c
float aa_media (ArvBinB* a, char* nome){
    ArvBinB_No *res = busca_media(a->raiz, nome);
    if(res != NULL)
        return(res->info.p1+res->info.p2+res->info.p3)/3;
    return 0;
}

ArvBinB_No *busca_media(ArvBinB_No *a, char *nome){
    if(a == NULL) return NULL;
    if(strcmp(a->info.nome, nome) == 0)
        return a;
    busca_media(a->esq, nome);
    busca_media(a->dir, nome);

}

//letra d
void aa_retira(ArvBinB *a, char *nome){
    retira(a->raiz, nome);
}

ArvBinB_No *retira(ArvBinB_No *r, char *nome){
    if(r == NULL)
        return NULL;
    r->esq = retira(r->esq, nome);
    r->dir = retira(r->dir, nome);

    if (strcmp(r->info.nome, nome) == 0){
        if(r->esq == NULL && r->dir == NULL){
            free(r);
            r = NULL;
        }
        else if(r->esq == NULL){
            ArvBinB_No *t = r;
            r = r->dir;
            free(t);
        }
        else if(r->dir == NULL){
            ArvBinB_No *t = r;
            r = r->esq;
            free(t);
        }
        else{
            ArvBinB_No *f = r->esq;
            while(f->dir != NULL){
                f = f->dir;
            }
            r->info = f->info;
            strcpy(f->info.nome, nome);
            r->esq = retira(r->esq, nome);
        }
    }
    return r;
}


//letra e
void aa_libera(ArvBinB *a){
    desaloca(a->raiz);
    a->raiz = NULL;
}

void desaloca(ArvBinB_No *r){
    if(r!=NULL){
        desaloca(r->esq);
        desaloca(r->dir);
        free(r);
    }
}
