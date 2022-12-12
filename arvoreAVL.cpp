//by Matheus Uchoa

//implementação de arvore AVL com todas as suas funções basicas


#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

struct no{
    int chave;
    int altura;
    struct no *esq;
    struct no *dir;
};

typedef struct no *ArvAVL;

int altura(ArvAVL no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

ArvAVL rotacaoLL(ArvAVL no){
    ArvAVL no2;
    no2 = no->esq;
    no->esq = no2->dir;
    no2->dir = no;
    no->altura = max(altura(no->esq), altura(no->dir)) + 1;
    no2->altura = max(altura(no2->esq), no->altura) + 1;
    return no2;
}

ArvAVL rotacaoRR(ArvAVL no){
    ArvAVL no2;
    no2 = no->dir;
    no->dir = no2->esq;
    no2->esq = no;
    no->altura = max(altura(no->esq), altura(no->dir)) + 1;
    no2->altura = max(altura(no2->dir), no->altura) + 1;
    return no2;
}


ArvAVL rotacaoLR(ArvAVL no){
    no->esq = rotacaoRR(no->esq);
    return rotacaoLL(no);
}

ArvAVL rotacaoRL(ArvAVL no){
    no->dir = rotacaoLL(no->dir);
    return rotacaoRR(no);
}


ArvAVL insereAVL(ArvAVL no, int chave){
    if(no == NULL){
        no = (ArvAVL) malloc(sizeof(struct no));
        no->chave = chave;
        no->altura = 0;
        no->esq = no->dir = NULL;
    }else if(chave < no->chave){
        no->esq = insereAVL(no->esq, chave);
        if(altura(no->esq) - altura(no->dir) == 2){
            if(chave < no->esq->chave)
                no = rotacaoLL(no);
            else
                no = rotacaoLR(no);
        }
    }else if(chave > no->chave){
        no->dir = insereAVL(no->dir, chave);
        if(altura(no->dir) - altura(no->esq) == 2){
            if(chave > no->dir->chave)
                no = rotacaoRR(no);
            else
                no = rotacaoRL(no);
        }
    }
    no->altura = max(altura(no->esq), altura(no->dir)) + 1;
    return no;
}

ArvAVL criaArvoreAVL(){
    ArvAVL raiz = NULL;
    return raiz;
}

void preOrdem(ArvAVL no){
    if(no != NULL){
        cout << no->chave << " ";
        preOrdem(no->esq);
        preOrdem(no->dir);
    }
}

void emOrdem(ArvAVL no){
    if(no != NULL){
        emOrdem(no->esq);
        cout << no->chave << " ";
        emOrdem(no->dir);
    }
}

void posOrdem(ArvAVL no){
    if(no != NULL){
        posOrdem(no->esq);
        posOrdem(no->dir);
        cout << no->chave << " ";
    }
}

//deletar um no

ArvAVL deletaNo(ArvAVL raiz, int chave){
    if(raiz == NULL)
        return NULL;
    else if(chave < raiz->chave)
        raiz->esq = deletaNo(raiz->esq, chave);
    else if(chave > raiz->chave)
        raiz->dir = deletaNo(raiz->dir, chave);
    else{
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            raiz = NULL;
        }else if(raiz->esq == NULL){
            ArvAVL no = raiz;
            raiz = raiz->dir;
            free(no);
        }else if(raiz->dir == NULL){
            ArvAVL no = raiz;
            raiz = raiz->esq;
            free(no);
        }else{
            ArvAVL no = raiz->esq;
            while(no->dir != NULL)
                no = no->dir;
            raiz->chave = no->chave;
            no->chave = chave;
            raiz->esq = deletaNo(raiz->esq, chave);
        }
    }
    if(raiz == NULL)
        return raiz;
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    int balanceamento = altura(raiz->esq) - altura(raiz->dir);
    if(balanceamento > 1 && altura(raiz->esq->esq) >= altura(raiz->esq->dir))
        return rotacaoLL(raiz);
    if(balanceamento > 1 && altura(raiz->esq->dir) > altura(raiz->esq->esq)){
        return rotacaoLR(raiz);
    }
    if(balanceamento < -1 && altura(raiz->dir->dir) >= altura(raiz->dir->esq))
        return rotacaoRR(raiz);
    if(balanceamento < -1 && altura(raiz->dir->esq) > altura(raiz->dir->dir))
        return rotacaoRL(raiz);
    return raiz;
}

int main(){
    ArvAVL raiz = criaArvoreAVL();
    raiz = insereAVL(raiz, 10);
    raiz = insereAVL(raiz, 20);
    raiz = insereAVL(raiz, 30);
    raiz = insereAVL(raiz, 40);
    raiz = insereAVL(raiz, 50);
    raiz = insereAVL(raiz, 25);
    cout << "Pre-ordem: ";
    preOrdem(raiz);
    cout << endl;
    cout << "Em-ordem: ";
    emOrdem(raiz);
    cout << endl;
    cout << "Pos-ordem: ";
    posOrdem(raiz);
    cout << endl;
    raiz = deletaNo(raiz, 20);
    cout << "Pre-ordem: ";
    preOrdem(raiz);
    cout << endl;
    cout << "Em-ordem: ";
    emOrdem(raiz);
    cout << endl;
    cout << "Pos-ordem: ";
    posOrdem(raiz);
    cout << endl;
    return 0;
}