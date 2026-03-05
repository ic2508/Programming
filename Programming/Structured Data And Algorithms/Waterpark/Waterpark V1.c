#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Waterpark {
    char nume[30];
    struct Waterpark *next;
};

struct Waterpark* creare_nod(char nume[30]) {
    struct Waterpark* nod = (struct Waterpark*)malloc(sizeof(struct Waterpark));
    strcpy(nod->nume, nume);
    nod->next = NULL;
    return nod;
}

struct Waterpark* adaugare(struct Waterpark *head, char nume[30]) {
    struct Waterpark* nou = creare_nod(nume);
    if (head == NULL) {
        return nou;
    } else {
        struct Waterpark *curent = head;
        while (curent->next != NULL) {
            curent = curent->next;
        }
        curent->next = nou;
        return head;
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
            W1 = adaugare(W1, nume);
        } else if (nr == 2) {
            W2 = adaugare(W2, nume);
        } else if (nr == 3) {
            W3 = adaugare(W3, nume);
        }
    }

    afisare(W1, W2, W3);

    return 0;
}