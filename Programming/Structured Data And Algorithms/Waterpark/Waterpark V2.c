#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Waterpark {
   struct Waterpark *next; 
   char nume[30];
   int nr;
};

struct Waterpark *creare_nod(char nume[30], int nr) {
    struct Waterpark *nod = malloc(sizeof(struct Waterpark));
    strcpy(nod->nume, nume);
    nod->nr = nr;
    nod->next = NULL;
    return nod;
}

struct Waterpark *adaugare(struct Waterpark *head, char nume[30], int nr) {
    struct Waterpark *nou = creare_nod(nume, nr);
    struct Waterpark *curent;
    if (head == NULL) {
        return nou;
    }
    curent = head;
    while (curent->next != NULL) {
        curent = curent->next;
    }
    curent->next = nou;
    return head;
}

struct Waterpark *adaugare_nou(struct Waterpark *head_nou, struct Waterpark *head, int val) {
    struct Waterpark *curent_nou, *curent;
    if (head_nou == NULL && head->nr == val)
        return head;
    else if(head_nou == NULL){
        curent = head;
        while (curent != NULL && curent->nr != val) {
            curent = curent->next;
        }
        if (curent != NULL && head_nou == NULL) {
            return curent;
        }
    }

    curent_nou = head_nou;
    curent = head;
    while (curent != NULL && curent->nr != val) {
        curent = curent->next;
    }
    if (curent != NULL) {
        while (curent_nou != NULL && curent_nou->next != NULL) {
            curent_nou = curent_nou->next;
        }
        if (curent_nou != NULL) {
            curent_nou->next = curent;
        }
    }
    return head;
}

void afisare(struct Waterpark *head1, struct Waterpark *head2, struct Waterpark *head3) {
    struct Waterpark *curent1, *curent2, *curent3;
    curent1 = head1;
    curent2 = head2;
    curent3 = head3;
    while (curent1 != NULL && curent2 != NULL && curent3 != NULL) {
        printf("%s %s %s\n", curent1->nume, curent2->nume, curent3->nume);
        curent1 = curent1->next;
        curent2 = curent2->next;
        curent3 = curent3->next;
    }
}

int main() {
    char nume[30];
    int nr, cnt1 = 0, cnt2 = 0, cnt3 = 0;
    struct Waterpark *W1 = 0;
    struct Waterpark *W2 = 0;
    struct Waterpark *W3 = 0;
    struct Waterpark *W = 0;

    while (scanf("%s %d", nume, &nr) != EOF) {
        W = adaugare(W, nume, nr);
        if (nr == 1)
            ++cnt1;
        else if (nr == 2)
            ++cnt2;
        else if (nr == 3)
            ++cnt3;
    }

    for (int i = 0; i < cnt1; ++i)
        W1 = adaugare_nou(W1, W, 1);
    for (int i = 0; i < cnt2; ++i)
        W2 = adaugare_nou(W2, W, 2);
    for (int i = 0; i < cnt3; ++i)
        W3 = adaugare_nou(W3, W, 3);

    afisare(W1, W2, W3);

    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Waterpark {
    char nume[30];
    struct Waterpark *next;
};

struct Waterpark* creare_nod(char nume[MAX_NAME_LENGTH]) {
    struct Waterpark* nod = (struct Waterpark*)malloc(sizeof(struct Waterpark));
    strcpy(nod->nume, nume);
    nod->next = NULL;
    return nod;
}

void adaugare(struct Waterpark **head, char nume[30]) {
    struct Waterpark* nou = creare_nod(nume);
    if (*head == NULL) {
        *head = nou;
    } else {
        struct Waterpark *curent = *head;
        while (curent->next != NULL) {
            curent = curent->next;
        }
        curent->next = nou;
    }
}

void afisare(struct Waterpark *W1, struct Waterpark *W2, struct Waterpark *W3) {
    while (W1 != NULL && W2 != NULL && W3 != NULL) {
        printf("%s %s %s\n", W1->nume, W2->nume, W3->nume);
        W1 = W1->next;
        W2 = W2->next;
        W3 = W3->next;
    }
}

int main() {
    char nume[30];
    int nr;
    struct Waterpark *W1 = NULL, *W2 = NULL, *W3 = NULL;

    while (scanf("%s %d", nume, &nr) != EOF) {
        if (nr == 1) {
            adaugare(&W1, nume);
        } else if (nr == 2) {
            adaugare(&W2, nume);
        } else if (nr == 3) {
            adaugare(&W3, nume);
        }
    }

    afisare(W1, W2, W3);

    return 0;
}
