#include <stdio.h>
#include <stdlib.h>

struct Coada {
    struct Coada *next;
    char *nume;
    int nr_prod;
    int nr_casa;
};

struct Case {
    struct Coada *clienti;
    int nr_prod;
};

struct Coada* creare_nod() {
    struct Coada *nod = (struct Coada*)malloc(sizeof(struct Coada));
    nod->nume = calloc(128, sizeof(char));
    scanf("%s", nod->nume);
    scanf("%d", &nod->nr_prod);
    nod->next = NULL;
    return nod;
}

struct Coada* adaugare(struct Coada *head) {
    struct Coada *curent = 0;
    struct Coada *nou = creare_nod();
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

void populare_case_n(struct Coada *head, struct Case *lista, int nr_case) {
    int case_id = 0;
    for (struct Coada *i = head; i != NULL; i = i->next) {
        struct Coada *nod = malloc(sizeof(struct Coada));
        nod->nume = i->nume;
        nod->nr_prod = i->nr_prod;
        nod->next = NULL;

        // Adăugăm clientul la casa corespunzătoare
        if (lista[case_id].clienti == NULL) {
            lista[case_id].clienti = nod;
        } else {
            struct Coada *curent = lista[case_id].clienti;
            while (curent->next != NULL) {
                curent = curent->next;
            }
            curent->next = nod;
        }

        lista[case_id].nr_prod += nod->nr_prod;
        case_id = (case_id + 1) % nr_case;
    }
}

void afisare_clienti_iesiti(struct Case *lista, int nr_case) {
    int clienti_ramasi = 1;
    
    // Creăm o coadă de clienți ce vor să iasă din magazin
    struct Coada *iesiti = NULL;
    
    while (clienti_ramasi) {
        clienti_ramasi = 0;
        struct Coada *client_de_iesit = NULL;
        int case_id_min = -1;
        int min_timp = 1000000; // un număr mare pentru a găsi cel mai mic timp

        // Căutăm casa cu cel mai mic timp total
        for (int i = 0; i < nr_case; ++i) {
            if (lista[i].clienti != NULL && lista[i].nr_prod < min_timp) {
                min_timp = lista[i].nr_prod;
                case_id_min = i;
            }
        }

        if (case_id_min != -1) {
            client_de_iesit = lista[case_id_min].clienti;
            printf("%s %d\n", client_de_iesit->nume, client_de_iesit->nr_prod);

            // Actualizăm casa
            lista[case_id_min].nr_prod -= client_de_iesit->nr_prod;
            lista[case_id_min].clienti = client_de_iesit->next;
            free(client_de_iesit);

            // Verificăm dacă mai sunt clienți la această casă
            if (lista[case_id_min].clienti != NULL) {
                clienti_ramasi = 1;
            }
        }
    }
}

void afisare(struct Coada *head) {
    struct Coada *curent = head;
    while (curent != NULL) {
        printf("%s ", curent->nume);
        printf("%d\n", curent->nr_prod);
        curent = curent->next;
    }
}

void afisare_clienti_case(struct Case *lista, int nr_case) {
    for (int i = 0; i < nr_case; ++i) {
        struct Coada *curent = lista[i].clienti;
        while (curent != NULL) {
            printf("%s %d\n", curent->nume, curent->nr_prod);
            curent = curent->next;
        }
    }
}

int main() {
    int nr_case, nr_clienti, test;
    scanf("%d", &nr_case);
    scanf("%d", &nr_clienti);
    struct Coada *C = 0;
    struct Case *P = (struct Case*)malloc(nr_case * sizeof(struct Case));
    
    for (int i = 0; i < nr_case; ++i) {
        P[i].clienti = NULL;
        P[i].nr_prod = 0;
    }

    for (int i = 0; i < nr_clienti; ++i) {
        C = adaugare(C);
    }

    scanf("%d", &test);
    switch (test) {
        case 1:
            afisare(C);
            break;
        case 2:
            populare_case_n(C, P, nr_case);
            afisare_clienti_case(P, nr_case);
            break;
        case 3:
            populare_case_n(C, P, nr_case);
            afisare_clienti_iesiti(P, nr_case);
            break;
    }

    return 0;
}
