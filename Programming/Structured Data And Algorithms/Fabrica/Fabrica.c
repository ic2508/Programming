#include <stdio.h>
#include <stdlib.h>

struct Fabrica {
    int val;
    struct Fabrica *next;
};

struct Fabrica *creare_nod(int val) {
    struct Fabrica *nou = (struct Fabrica *)malloc(sizeof(struct Fabrica));
    nou->val = val;
    nou->next = NULL;
    return nou;
}

struct Fabrica *adaugare(struct Fabrica *head, int val) {
    struct Fabrica *nou = creare_nod(val);
    if (head == NULL) {
        return nou;
    }
    struct Fabrica *curent = head;
    while (curent->next != NULL) {
        curent = curent->next;
    }
    curent->next = nou;
    return head;
}

void afisare(struct Fabrica *head) {
    struct Fabrica *curent = head;
    while (curent != NULL) {
        printf("%d ", curent->val);
        curent = curent->next;
    }
    printf("\n");
}

struct Fabrica *sterge(struct Fabrica *head) {
    if (head == NULL) 
    return NULL;
    struct Fabrica *temp = head;
    head = head->next;
    free(temp);
    return head;
}

int main() {
    int n;
    scanf("%d", &n);

    int camioane[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &camioane[i]);
    }

    char proces[128];
    scanf("%s", proces);

    struct Fabrica *nerecepționate = NULL;
    struct Fabrica *recepționate = NULL;
    struct Fabrica *procesate = NULL;
    struct Fabrica *livrate = NULL;

    for (int i = 0; i < n; i++) {
        nerecepționate = adaugare(nerecepționate, camioane[i]);
    }

    for (int i = 0; proces[i] != '\0'; i++) {
        if (proces[i] == 'r' && nerecepționate != NULL) {
            int camion = nerecepționate->val;
            recepționate = adaugare(recepționate, camion);
            nerecepționate = sterge(nerecepționate);
        } 
        else if (proces[i] == 'p' && recepționate != NULL) {
            int camion = recepționate->val;
            procesate = adaugare(procesate, camion);
            recepționate = sterge(recepționate);
        } 
        else if (proces[i] == 'l' && procesate != NULL) {
            int camion = procesate->val;
            livrate = adaugare(livrate, camion);
            procesate = sterge(procesate);
        }
    }

    afisare(nerecepționate);
    afisare(recepționate);
    afisare(procesate);
    afisare(livrate);

    return 0;
}
