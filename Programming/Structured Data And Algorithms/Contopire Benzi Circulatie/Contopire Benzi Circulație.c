#include <stdio.h>
#include <stdlib.h>

struct Autostrada {
    struct Autostrada *next;
    char **s;
    int nr;
};

struct Autostrada *creare_nod(int nr) {
    struct Autostrada *nou = (struct Autostrada*)malloc(sizeof(struct Autostrada));
    nou->s = (char**)calloc(nr,sizeof(char*));
    for(int i=0;i<nr;++i){
        nou->s[i] = (char*)calloc(128, sizeof(char));
        scanf("%s",nou->s[i]);
    }
    nou->nr=nr;
    nou->next=NULL;
    return nou;
}

struct Autostrada *adaugare(struct Autostrada *head, int nr) {
    struct Autostrada *nou = creare_nod(nr);
    if(head==NULL){
        return nou;
    }
    struct Autostrada *curent = head;
    while(curent->next!=NULL){
        curent=curent->next;
    }
    curent->next = nou;
    return head;
}

void afisare(struct Autostrada * head,int m, int n){
    struct Autostrada *curent,*banda1,*banda2;
    banda1=head;
    banda2=head->next;
    int cnt=0;
    if(m>=n){
    for(int i=0;i<n;++i){
        printf("%s\n",banda2->s[i]);
        printf("%s\n",banda1->s[cnt]);
        ++cnt;
    }
    while(cnt!=m){
        printf("%s\n",banda1->s[cnt]);
        ++cnt;
    }
    }
    else if(m<=n){
        for(int i=0;i<n;++i){
        printf("%s\n",banda2->s[i]);
        if(cnt<m){
        printf("%s\n",banda1->s[cnt]);
        ++cnt;
        }
        else if(cnt>=m){
            ++cnt;
        }
    }
    }
    
}


int main() {
    int m, n;
    struct Autostrada *A = NULL;
    scanf("%d %d", &m, &n);
    A = adaugare(A, m);
    A = adaugare(A, n);
    afisare(A,m,n);
    free(A);
    return 0;
}