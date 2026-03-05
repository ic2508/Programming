#include <stdio.h>
#include <stdlib.h>

struct Coada{
    struct Coada *next;
    char *nume;
    int nr_prod;
    int nr_casa;
};

struct Case{
    struct Coada *clienti;
    int nr_prod;
};

struct Coada * creare_nod(){
    struct Coada *nod = (struct Coada*)malloc(sizeof(struct Coada));
    nod->nume=calloc(128,sizeof(char));
    scanf("%s",nod->nume);
    scanf("%d",&nod->nr_prod);
    nod->next=NULL;
    return nod;
}

struct Coada *adaugare(struct Coada * head){
    struct Coada *curent=0;
    struct Coada *nou = creare_nod();
    if(head==NULL){
        return nou;
    }
    curent=head;
    while(curent->next!=NULL){
        curent=curent->next;
    }
    curent->next = nou;
    return head;
}

void populare_case(struct Coada *head, struct Case *lista, int nr_case) {
    for (int i = 0; i < nr_case; ++i) {
        lista[i].nr_prod = 0;
    }

    for (struct Coada *i = head; i != NULL; i = i->next) {
        int min_products = lista[0].nr_prod;
        int case_id = 0;

        for (int j = 1; j < nr_case; ++j) {
            if (lista[j].nr_prod < min_products) {
                min_products = lista[j].nr_prod;
                case_id = j;
            }
        }

        struct Coada *new_customer = malloc(sizeof(struct Coada));
        new_customer->nume = i->nume;
        new_customer->nr_prod = i->nr_prod;
        new_customer->nr_casa = case_id;
        new_customer->next = NULL;
        

        if (lista[case_id].clienti == NULL) {
            lista[case_id].clienti = new_customer;
        } else {
            struct Coada *current = lista[case_id].clienti;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_customer;
        }
        lista[case_id].nr_prod = lista[case_id].nr_prod + i->nr_prod;
    }
}

void populare_case_n(struct Coada *head, struct Case *lista, int nr_case){
    for (int i = 0; i < nr_case; ++i) {
        lista[i].nr_prod = 0;
    }
    int ind=1,case_id=0;
    for(struct Coada *i = head;i!=NULL;i=i->next){
        struct Coada *nod = malloc(sizeof(struct Coada));
        nod->nume = i->nume;
        nod->nr_prod = i->nr_prod;
        nod->nr_casa = ind;
        nod->next = NULL;
        lista[case_id]->nr_prod = lista[case_id]->nr_prod+nod->nr_prod;
        ++ind;
        if(lista[case_id].clienti == NULL) {
            lista[case_id].clienti = nod;
    }
    else {
        struct Coada *current = lista[case_id].clienti;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = nod;
    }
    ++case_id;
    if(case_id==4)
    case_id=0;
    if(ind==5)
    ind=1;
}
}

void afisare_clienti_iesiti(struct Coada *head, struct Case *lista, int nr_case){
     int case_id=0,case_id_v=1;
     struct Coada *current1 = lista[case_id].clienti;
     struct Coada *current2 = lista[case_id_v].clienti;
     for(struct Coada *i = head;i!=NULL;i=i->next){
         if(lista[case_id].nr_prod<lista[case_id_v].nr_prod){
             
         if(current1->nr_prod<current2->nr_prod){
             printf("%s ",current1->nume);
             printf("%d\n",current1->nr_prod);
             current1 = current1->next;
         }
         else if(current1->nr_prod>current2->nr_prod){
         ++case_id_v;
         }
     }
     }
}

void afisare(struct Coada * head){
    struct Coada *curent=head;
    while(curent!=NULL){
        printf("%s ",curent->nume);
        printf("%d\n",curent->nr_prod);
        curent=curent->next;
    }
}

void afisare_clienti_case(struct Case *lista, int nr_case)
{
    for(int i=0;i<nr_case;++i)
    {
        afisare((lista+i)->clienti);
    }
}

int main(){
    int nr_case,nr_clienti,test;
    scanf("%d",&nr_case);
    scanf("%d",&nr_clienti);
    struct Coada *C=0;
    struct Case *P = (struct Case*)malloc(nr_case*sizeof(struct Case));
    for(int i=0;i<nr_clienti;++i){
        C = adaugare(C);
    }
    scanf("%d",&test);
    switch(test){
        case 1:
        afisare(C);
        break;
        case 2:
        populare_case(C,P,nr_case);
        afisare_clienti_case(P,nr_case);
        break;
        case 3:
        populare_case_n(C,P,nr_case);
        afisare_clienti_iesiti(C,P,nr_case);
        break;
    }
    
}