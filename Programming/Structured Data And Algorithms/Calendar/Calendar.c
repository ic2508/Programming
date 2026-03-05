#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Calendar {
    char *titlu;
    int data;
    struct Calendar *next;
};

struct Calendar *creare_nod() {
    struct Calendar *nod = (struct Calendar *)malloc(sizeof(struct Calendar));
    if (nod == NULL) {
        return NULL;
    }
    nod->titlu = (char *)malloc(256 * sizeof(char));
    scanf("%255s", nod->titlu);
    scanf("%d", &(nod->data));
    nod->next = NULL;
    return nod;
}

struct Calendar *adaugare_sfarsit(struct Calendar *head) {
    struct Calendar *nou, *curent;
    
    if (head == NULL) {
        return creare_nod();
    }

    curent = head;
    while (curent->next != NULL) {
        curent = curent->next;
    }

    nou = creare_nod();
    curent->next = nou;
    return head;
}

void afisare(struct Calendar *head) {
    struct Calendar *curent = head;
    while (curent != NULL) {
        printf("%s ", curent->titlu);
        printf("%d\n", curent->data);
        curent = curent->next;
    }
}

void cautare_1(struct Calendar *head, char *titlu_c){
    struct Calendar *nou,*curent;
    curent=head;
    while(curent!=NULL){
        if(strcmp(curent->titlu,titlu_c)==0){
            printf("%d\n",curent->data);
        }
        curent=curent->next;
    }
}

void cautare_2(struct Calendar *head, int data_c){
    struct Calendar *nou,*curent;
    curent=head;
    while(curent!=NULL){
        if(curent->data==data_c){
            printf("%s\n",curent->titlu);
        }
        curent=curent->next;
    }
}

void ordonare(struct Calendar *head, int nr) {
    int *v = (int *)calloc(nr,sizeof(int));
    int cnt = 0;

    while(cnt<nr){
        struct Calendar *curent = head;
        struct Calendar *min_node = NULL;
        int ind = -1,j = 0;
        int min_data = 20220000;

        while(curent != NULL){
            if (v[j] == 0 && (curent->data < min_data || (curent->data == min_data && min_node == NULL))) {
                min_data = curent->data;
                min_node = curent;
                ind = j;
            }
            curent = curent->next;
            ++j;
        }

        if(min_node != NULL){
            printf("%s %d\n", min_node->titlu, min_node->data);
            v[ind] = 1;
            cnt++;
        }
    }
    free(v);
}

int cnt(struct Calendar *head){
    struct Calendar *curent;
    curent= head;
    int cnt1=0;
    while (curent != NULL) {
        ++cnt1;
        curent = curent->next;
    }
    return cnt1;
}

int main() {
    int c,data_c,nr;
    char *titlu_c = (char *)calloc(256,sizeof(char));
    struct Calendar *p = 0;
    do {
        scanf("%d", &c);
        switch (c) {
            case 1:
                p = adaugare_sfarsit(p);
                break;
            case 2:
            scanf("%s",titlu_c);
            cautare_1(p,titlu_c);
            break;
            case 3:
            scanf("%d",&data_c);
            cautare_2(p,data_c);
            break;
            case 4:
                afisare(p);
                break;
            case 5:
            nr=cnt(p);
            //printf("%d",nr);
            ordonare(p,nr);
            break;
            case 6:
                exit(0);
                break;
            default:
                exit(0);
                break;
        }
    } while (1);

return 0;
}