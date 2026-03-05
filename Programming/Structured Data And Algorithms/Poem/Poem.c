#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Poem {
    struct Poem *next;
    char **strofe;
};

struct Poem *creare_nod() {
    struct Poem *nod = malloc(sizeof(struct Poem));
    nod->strofe = (char **)calloc(4, sizeof(char *));
    for (int i = 0; i < 4; ++i) {
        nod->strofe[i] = (char *)calloc(100, sizeof(char));
    }
    
    for (int i = 0; i < 4; ++i) {
        //scanf("%[^\n]",nod->strofe[i]);
        //getchar();
        fgets(nod->strofe[i], 100, stdin);
        int len = strlen(nod->strofe[i]);
        if (len > 0 && nod->strofe[i][len - 1] == '\n') {
            nod->strofe[i][len - 1] = '\0';
        }
    }
    nod->next = NULL;
    return nod;
}

struct Poem *creare_nod_n(struct Poem *head) {
    struct Poem *nod = malloc(sizeof(struct Poem));
    nod->strofe = (char **)calloc(4, sizeof(char *));
    for (int i = 0; i < 4; ++i) {
        nod->strofe[i] = (char *)calloc(100, sizeof(char));
        strcpy(nod->strofe[i], head->strofe[i]);
    }
    nod->next = NULL;
    return nod;
}

struct Poem *adauga(struct Poem *head) {
    struct Poem *nou = creare_nod();
    if (head == NULL) {
        return nou;
    }
    struct Poem *curent = head;
    while (curent->next != NULL) {
        curent = curent->next;
    }
    curent->next = nou;
    return head;
}

struct Poem * populare(struct Poem *head){
    struct Poem *curent;
    struct Poem *reverse = 0;
    curent=head;
    while(curent!=NULL){
        struct Poem *nou = creare_nod_n(curent);
        nou->next=reverse;
        reverse=nou;
        curent=curent->next;
    }
    return reverse;
}

void afisare(struct Poem *head) {
    struct Poem *curent = head;
    while (curent != NULL) {
        for (int i = 0; i < 4; ++i) {
            printf("%s\n", curent->strofe[i]);
        }
        printf("\n");
        curent = curent->next;
    }
}

void rima(struct Poem *head){
    struct Poem *curent;
    curent = head;
    int l1 = strlen(curent->strofe[0]);
    int l2 = strlen(curent->strofe[1]);
    int l3 = strlen(curent->strofe[2]);
    int l4 = strlen(curent->strofe[3]);
    if(curent->strofe[0][l1-2] == curent->strofe[3][l4-2] &&
    curent->strofe[0][l1-1] == curent->strofe[3][l4-1]){
        if(curent->strofe[1][l2-2] == curent->strofe[2][l3-2] &&
    curent->strofe[1][l2-1] == curent->strofe[2][l3-1]){
        printf("%c%c-%c%c-%c%c-%c%c\n",curent->strofe[0][l1-2],
        curent->strofe[0][l1-1],curent->strofe[1][l2-2],curent->strofe[1][l2-1],
        curent->strofe[2][l3-2],curent->strofe[2][l3-1],curent->strofe[3][l4-2],
        curent->strofe[3][l4-1]);
    }else
    printf("nu\n");
    }
    else
    printf("nu\n");
}

void afisare_rima(struct Poem *head,int nr){
     struct Poem *curent,*curent1;
    curent1 = head;
    int i=0,cnt=1,max1=-32000;
    int j=0;
    char c1,c2,c1f,c2f;
    for(int k=0;k<4;++k){
    curent = head;
    int l = strlen(curent->strofe[j]);
    c1 = curent1->strofe[j][l-2];
    c2 = curent1->strofe[j][l-1];
    ++j;
    while(curent!=NULL){
        while(i!=3){
        ++i;
        int l = strlen(curent->strofe[i]);
        if(c1 == curent->strofe[i][l-2] && c2 == curent->strofe[i][l-1]){
            ++cnt;
        }
        }
        i=0;
        curent=curent->next;
    }
    if(cnt>max1){
    max1=cnt;
    c1f=c1;
    c2f=c2;
    }
    cnt=0;
    }
    printf("%c%c",c1f,c2f);
}


int main() {
    int nr, test;
    struct Poem *poem = NULL;
    struct Poem *reverse = NULL;
    scanf("%d", &nr);
    getchar();
    for (int i = 0; i < nr; ++i) {
        poem = adauga(poem);
    }
    scanf("%d", &test);
    getchar();

    switch(test){
        case 1:
        afisare(poem);
        break;
        case 2:
        rima(poem);
        break;
        case 3:
        reverse = populare(poem);
        afisare(reverse);
        break;
        case 4:
        afisare_rima(poem,nr);
        break;
    }
    return 0;
}
