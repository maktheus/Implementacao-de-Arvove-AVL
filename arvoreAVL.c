//by Matheus Uchoa

//implementação de arvore AVL com todas as suas funções basicas

#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    int altura;
    struct no *esq;
    struct no *dir;
}no;

int altura(no *raiz){
    if(raiz == NULL)
        return -1;
    else
        return raiz->altura;
}

int max(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}

no *criaNo(int chave){
    no *novo = (no*)malloc(sizeof(no));
    novo->chave = chave;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

no *rotacaoEsquerda(no *raiz){
    no *aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;
    return aux;
}

no *rotacaoDireita(no *raiz){
    no *aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;
    return aux;
}

no *rotacaoDuplaEsquerda(no *raiz){
    raiz->dir = rotacaoDireita(raiz->dir);
    return rotacaoEsquerda(raiz);
}

no *rotacaoDuplaDireita(no *raiz){
    raiz->esq = rotacaoEsquerda(raiz->esq);
    return rotacaoDireita(raiz);
}

no *insere(no *raiz, int chave){
    if(raiz == NULL)
        return criaNo(chave);
    else{
        if(chave < raiz->chave)
            raiz->esq = insere(raiz->esq, chave);
        else
            raiz->dir = insere(raiz->dir, chave);
    }
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    if(altura(raiz->esq) - altura(raiz->dir) == 2){
        if(chave < raiz->esq->chave)
            raiz = rotacaoDireita(raiz);
        else
            raiz = rotacaoDuplaDireita(raiz);
    }
    else if(altura(raiz->dir) - altura(raiz->esq) == 2){
        if(chave > raiz->dir->chave)
            raiz = rotacaoEsquerda(raiz);
        else
            raiz = rotacaoDuplaEsquerda(raiz);
    }
    return raiz;
}

no *busca(no *raiz, int chave){
    if(raiz == NULL)
        return NULL;
    else{
        if(chave < raiz->chave)
            return busca(raiz->esq, chave);
        else if(chave > raiz->chave)
            return busca(raiz->dir, chave);
        else
            return raiz;
    }
}

no *removeNo(no *raiz, int chave){
    if(raiz == NULL)
        return NULL;
    else{
        if(chave < raiz->chave)
            raiz->esq = removeNo(raiz->esq, chave);
        else if(chave > raiz->chave)
            raiz->dir = removeNo(raiz->dir, chave);
        else{
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            }
            else if(raiz->esq == NULL){
                no *aux = raiz->dir;
                free(raiz);
                return aux;
            }
            else if(raiz->dir == NULL){
                no *aux = raiz->esq;
                free(raiz);
                return aux;
            }
            else{
                no *aux = raiz->esq;
                while(aux->dir != NULL)
                    aux = aux->dir;
                raiz->chave = aux->chave;
                raiz->esq = removeNo(raiz->esq, aux->chave);
            }
        }
    }
    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    if(altura(raiz->esq) - altura(raiz->dir) == 2){
        if(altura(raiz->esq->esq) - altura(raiz->esq->dir) >= 0)
            raiz = rotacaoDireita(raiz);
        else
            raiz = rotacaoDuplaDireita(raiz);
    }
    else if(altura(raiz->dir) - altura(raiz->esq) == 2){
        if(altura(raiz->dir->dir) - altura(raiz->dir->esq) >= 0)
            raiz = rotacaoEsquerda(raiz);
        else
            raiz = rotacaoDuplaEsquerda(raiz);
    }
    return raiz;
}

void preOrdem(no *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->chave);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}

void emOrdem(no *raiz){
    if(raiz != NULL){
        emOrdem(raiz->esq);
        printf("%d ", raiz->chave);
        emOrdem(raiz->dir);
    }
}

void posOrdem(no *raiz){
    if(raiz != NULL){
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->chave);
    }
}

int main(){
    no *raiz = NULL;
    int opcao, chave;
    do{
        printf("1 - Inserir elemento na arvore AVL (AVL)\n");
        printf("2 - Buscar elemento na arvore AVL (AVL)\n");
        printf("3 - Remover elemento da arvore AVL (AVL)\n");
        printf("4 - Imprimir arvore AVL (AVL)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                raiz = insere(raiz, chave);
                break;
            case 2:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                if(busca(raiz, chave) != NULL)
                    printf("Elemento encontrado!\n");
                else
                    printf("Elemento nao encontrado!\n");
                break;
            case 3:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                raiz = removeNo(raiz, chave);
                break;
            case 4:
                printf("Pre-ordem: ");
                preOrdem(raiz);
                printf("\n");
                printf("Em-ordem: ");
                emOrdem(raiz);
                printf("\n");
                printf("Pos-ordem: ");
                posOrdem(raiz);
                printf("\n");
                break;
        }
    }while(opcao != 0);
    return 0;
}