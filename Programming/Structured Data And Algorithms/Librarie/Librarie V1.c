#include <stdio.h>
#include <stdlib.h>

struct Nod {
    char *volum;
    struct Nod *next;
};

void adauga_in_teanc(struct Nod *stack, const char *volum) {
    struct Nod *nou = (struct Nod*)malloc(sizeof(struct Nod));
    nou->volum = (char*)malloc(128 * sizeof(char));
    int i = 0;
    while (volum[i] != '\0' && i < 128 - 1) {
        nou->volum[i] = volum[i];
        i++;
    }
    nou->volum[i] = '\0';
    nou->next = *stack;
    *stack = nou;
}

void scoate_din_teanc(struct Nod **stack, char **scanat) {
    if (*stack != NULL) {
        struct Nod *temp = *stack;
        *scanat = temp->volum;
        *stack = temp->next;
        free(temp);
    } else {
        *scanat = NULL;
    }
}

void elimina_newline(char *input) {
    int i = 0;
    while (input[i] != '\0') {
        i++;
    }
    if (i > 0 && input[i - 1] == '\n') {
        input[i - 1] = '\0';
    }
}

int main() {
    struct Nod *teanc = NULL;
    char input[MAX_NAME_LEN];
    char *scanat;
    int first = 1;
    int plusuri = 0, minusuri = 0;

    while (fgets(input, sizeof(input), stdin)) {
        elimina_newline(input);

        if (input[0] == '+') {
            adauga_in_teanc(&teanc, input + 2);
            plusuri++;
        } else if (input[0] == '-') {
            if (teanc == NULL){
                continue;
            }
            if (teanc != NULL) {
                scoate_din_teanc(&teanc, &scanat);
                if (scanat != NULL) {
                    if (!first) {
                        printf(",");
                    }
                    printf("%s", scanat);
                    first = 0;
                }
            }
            minusuri++;

            if (minusuri > plusuri) {
                break;
            }
        }
    }

    printf(",");
    return 0;
}
