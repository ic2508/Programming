#include <stdio.h>
#include <stdlib.h>

struct Calculator{
    struct Calculator *next;
    int nr;
};

struct Calculator *creare_nod(int nri){
    struct Calculator *nod = malloc(sizeof(struct Calculator));
    nod->nr=nri%10;
    nod->next=NULL;
    return nod;
}

struct Calculator *creare_nod_n(struct Calculator * head2){
    struct Calculator *nod = malloc(sizeof(struct Calculator));
    nod->nr=head2->nr;
    nod->next=NULL;
    return nod;
}

struct Calculator *adauga(struct Calculator * head,int nr){
    struct Calculator *curent;
    struct Calculator *nou=creare_nod(nr);
    if(head==NULL){
        return nou;
    }
    nou->next=head;
    return nou;
}

struct Calculator *adauga_final(struct Calculator *head1, struct Calculator *head2) {
    struct Calculator *curent1 = head1;
    struct Calculator *nou;
    while (curent1 != NULL) {
        nou = creare_nod_n(curent1);
        nou->next = head2;
        head2 = nou;
        curent1 = curent1->next;
    }
    return head2;
}

void afisare(struct Calculator * head1,struct Calculator * head2){
     struct Calculator *curent1,*curent2;
     curent1=head1;
     while(curent1!=NULL){
         printf("%d",curent1->nr);
         curent1=curent1->next;
     }
     printf("\n");
     curent2=head2;
     while(curent2!=NULL){
         printf("%d",curent2->nr);
         curent2=curent2->next;
     }
     printf("\n");
}

int adunare(struct Calculator * head1,struct Calculator * head2){
    int p=1, suma=0;
    struct Calculator *curent1,*curent2;
    curent1=head1;
    curent2=head2;
    while(curent1!=NULL){
        if(curent2!=NULL){
        suma=suma+(curent1->nr+curent2->nr)*p;
        curent1=curent1->next;
        curent2=curent2->next;
        }
        else{
        suma=suma+(curent1->nr+0)*p;
        curent1=curent1->next;
        }
        p=p*10;
    }
    return suma;
}

int scadere(struct Calculator *head1, struct Calculator *head2) {
    int p = 1, suma = 0;
    struct Calculator *curent1, *curent2;
    curent1 = head1;
    curent2 = head2;
    int borrow = 0;
    while (curent2 != NULL) {
        int digit1;
        if(curent1 != NULL)
        digit1 = curent1->nr;
        else
        digit1=0;
        int digit2 = curent2->nr - borrow;
        if (digit2 < digit1) {
            digit2 = digit2 + 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        suma = suma + (digit2 - digit1) * p;
        if (curent1 != NULL) 
        curent1 = curent1->next;
        curent2 = curent2->next;
        p = p * 10;
    }
    return suma;
}

int calcul_nr_mic(struct Calculator * head){
    struct Calculator *curent;
    int cnt=1;
    curent=head;
    while(curent->next!=NULL){
        if(curent->nr<curent->next->nr){
        ++cnt;
        curent=curent->next;
        }
        else return cnt;;
    }
    return cnt;
}

int calcul_nr_mare(struct Calculator * head){
    struct Calculator *curent;
    int cnt=1;
    curent=head;
    while(curent->next!=NULL){
        if(curent->nr>curent->next->nr){
        ++cnt;
        curent=curent->next;
        }
        else return cnt;
    }
    return cnt;
}

int main(){
    int test,nr1,nr2,cnt1=0,cnt2=0,nr1_c,nr2_c,nr1_c1,nr2_c1,val;
    int val1,val2;
    scanf("%d",&nr1);
    scanf("%d",&nr2);
    nr1_c=nr1;
    nr2_c=nr2;
    while(nr1_c!=0){
    nr1_c=nr1_c/10;
    ++cnt1;
    }
    //printf("%d\n",cnt1);
    while(nr2_c!=0){
    nr2_c=nr2_c/10;
    ++cnt2;
    }
    //printf("%d\n",cnt2);
    nr1_c1=nr1;
    nr2_c1=nr2;
    struct Calculator *C1 = 0;
    struct Calculator *C2 = 0;
    struct Calculator *C11 = 0;
    struct Calculator *C22 = 0;
    for(int i=0;i<cnt1;++i){
    C1 = adauga(C1,nr1);
    nr1=nr1/10;
    }
    for(int i=0;i<cnt2;++i){
    C2 = adauga(C2,nr2);
    nr2=nr2/10;
    }
    C11 = adauga_final(C1,C11);
    C22 = adauga_final(C2,C22);
    scanf("%d",&test);
    switch(test){
        case 1:
        afisare(C1,C2);
        break;
        case 2:
        val = adunare(C11,C22);
        printf("%d",val);
        break;
        case 3:
        val = scadere(C11,C22);
        printf("-%d",val);
        break;
        case 4:
        val1 = calcul_nr_mic(C1);
        val2 = calcul_nr_mare(C2);
        if(val1==val2)
        printf("da");
        else
        printf("nu");
        break;
    }
}