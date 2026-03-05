#include <stdio.h>
#include <stdlib.h>

struct Spital{
    struct Spital *next;
    char *s;
};

struct Grupuri{
    struct Spital *liste;
};

struct Spital *creare_nod(){
    struct Spital * nod = malloc(sizeof(struct Spital));
    nod->s = calloc(20,sizeof(char));
    scanf("%s",nod->s);
    nod->next=NULL;
    return nod;
}

struct Spital *adaugare(struct Spital *head){
    struct Spital * nou = creare_nod();
    struct Spital * curent;
    if(head==NULL){
        return nou;
    }
    curent = head;
    while(curent->next!=NULL){
        curent=curent->next;
    }
    curent->next=nou;
    return head;
}

void populare_grupuri(struct Spital *head,struct Grupuri *grup,int n){
    int ind=0,cnt=0;;
    struct Grupuri *curent;
    for(struct Spital *i = head;i!=NULL;i=i->next){
        struct Spital *nod = malloc(sizeof(struct Spital));
        nod->s = i->s;
        nod->next=NULL;
        if(grup[ind].liste==NULL)
        grup[ind].liste=nod;
        else{
            nod->next = grup[ind].liste;
            grup[ind].liste = nod;
        }
        ++cnt;
        if(cnt==3){
            ++ind;
            cnt=0;
        }
    }
}

void populare_grupuri_g(struct Spital *head,struct Grupuri *grup,int g){
    int ind=0,cnt=0;;
    struct Grupuri *curent;
    for(struct Spital *i = head;i!=NULL;i=i->next){
        struct Spital *nod = malloc(sizeof(struct Spital));
        nod->s = i->s;
        nod->next=NULL;
        if(grup[ind].liste==NULL)
        grup[ind].liste=nod;
        else{
            nod->next = grup[ind].liste;
            grup[ind].liste = nod;
        }
        ++cnt;
        if(cnt==g){
            ++ind;
            cnt=0;
        }
    }
}

void populare_grupuri_e(struct Spital *head,struct Grupuri *grup,int n){
    int ind=0,cnt=0,eli=1,numar=-2,cnt2=0;
    struct Grupuri *curent;
    for(struct Spital *i = head;i!=NULL;i=i->next){
        struct Spital *nod = malloc(sizeof(struct Spital));
        nod->s = i->s;
        nod->next=NULL;
        if(eli%7==0 && eli!=0){
            if(cnt==0)
            numar=2;
            else if(cnt==1)
            numar=1;
            else if(cnt==2)
            numar=0;
        }
        if(grup[ind].liste==NULL){
        ++cnt;
        if(cnt!=(numar+1))
        grup[ind].liste=nod;
        else numar=-2;
        }
        else{
            ++cnt;
            if(cnt!=(numar+1)){
            nod->next = grup[ind].liste;
            grup[ind].liste = nod;
            }
            else numar=-2;
        }
        ++eli;
        if(cnt==3){
            ++ind;
            cnt=0;
        }
    }
}

void afisare(struct Spital *head){
    struct Spital * curent;
    curent = head;
    while(curent!=NULL){
        printf("%s\n",curent->s);
        curent=curent->next;
    }
}

void afisare_grupuri(struct Grupuri *grup,int val){
    for(int i=0;i<val;++i){
        afisare(grup[i].liste);
    }
}



int main(){
    int n,test,val,g;
    scanf("%d",&n);
    struct Spital *spital = 0;
    struct Grupuri *grupuri;
    for(int i=0;i<n;++i){
        spital = adaugare(spital);
    }
    scanf("%d",&test);
    switch(test){
        case 1:
        afisare(spital);
        break;
        case 2:
        val = ((n/3)+(n%3));
        grupuri = malloc(val*sizeof(struct Grupuri));
        populare_grupuri(spital,grupuri,n);
        afisare_grupuri(grupuri,val);
        break;
        case 3:
        scanf("%d",&g);
        val = ((n/g)+(n%g));
        grupuri = malloc(val*sizeof(struct Grupuri));
        populare_grupuri_g(spital,grupuri,g);
        afisare_grupuri(grupuri,val);
        break;
        case 4:
        val = ((n/3)+(n%3));
        grupuri = malloc(val*sizeof(struct Grupuri));
        populare_grupuri_e(spital,grupuri,n);
        afisare_grupuri(grupuri,val);
        break;
        default:
        break;
    }
}