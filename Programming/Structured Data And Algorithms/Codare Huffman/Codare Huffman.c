#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nod{
    int data;
    char c;
    struct nod * left;
    struct nod * right;
};

struct cod_huffman {
    char caracter;
    char cod[256];
};

struct nod * huffman_tree();
void afisare_frecvente(char *text);
void afisare_valori_utile(struct nod *root);
void afisare_coduri(struct nod *root);
void genereaza_coduri(struct nod *root, char *cod, int index, struct cod_huffman coduri[], int *k);
void codificare_text(char *text, char coduri[256][256]);
void calcul_economie(char *text, char coduri[256][256]);
void generare_coduri(struct nod *root, char *cod, int nivel, char coduri[256][256]);
void colecteaza_valori(struct nod *radacina, int *valori, int *index);
int compara(const void *a, const void *b);

int main() {
    char text[256];
    int optiune,k=0;
    fgets(text, 256, stdin);
    text[strcspn(text, "\n")] = 0;
    scanf("%d", &optiune);

    struct nod *huffman = huffman_tree();

    char coduri[256][256] = {0};
    char cod[256];

    int frecv[256] = {0};
    for (int i = 0; text[i]; i++) {
        frecv[(unsigned char)text[i]]++;
    }

    switch (optiune) {
        case 1:
            afisare_frecvente(text);
            break;
        case 2:
            afisare_valori_utile(huffman);
            break;
        case 3:
            afisare_coduri(huffman);
            break;
        case 4:
            generare_coduri(huffman, cod, 0, coduri);
            codificare_text(text, coduri);
            break;
        case 5:
            generare_coduri(huffman, cod, 0, coduri);
            calcul_economie(text, coduri);
            break;
    }
    return 0;
}

void generare_coduri(struct nod *root, char *cod, int nivel, char coduri[256][256]) {
    if (!root) 
    return;
    if (root->left == NULL && root->right == NULL) {
        cod[nivel] = '\0';
        strcpy(coduri[(unsigned char)root->c], cod);
        return;
    }
    cod[nivel] = '0';
    generare_coduri(root->left, cod, nivel + 1, coduri);
    cod[nivel] = '1';
    generare_coduri(root->right, cod, nivel + 1, coduri);
}

void calcul_economie(char *text, char coduri[256][256]) {
    int original_size = strlen(text) * 8;
    int compressed_size = 0;
    for (int i = 0; text[i]; i++) {
        compressed_size += strlen(coduri[(unsigned char)text[i]]);
    }
    printf("%d\n", original_size - compressed_size);
}

void codificare_text(char *text, char coduri[256][256]) {
    for (int i = 0; text[i]; i++) {
        printf("%s", coduri[(unsigned char)text[i]]);
    }
    printf("\n");
}

int compara(const void *a, const void *b) {
    struct cod_huffman *cod1 = (struct cod_huffman *)a;
    struct cod_huffman *cod2 = (struct cod_huffman *)b;

    int len1 = strlen(cod1->cod);
    int len2 = strlen(cod2->cod);

    if (len1 != len2) {
        return len2 - len1;
    }
    return strcmp(cod1->cod, cod2->cod);
}

void colecteaza_valori(struct nod *radacina, int *valori, int *index) {
    if (radacina == NULL) 
    return;
    valori[*index] = radacina->data;
    (*index)++;
    colecteaza_valori(radacina->left, valori, index);
    colecteaza_valori(radacina->right, valori, index);
}

void genereaza_coduri(struct nod *root, char *cod, int index, struct cod_huffman coduri[], int *k) {
    if (root==NULL) 
    return;
    if (root->left==NULL && root->right==NULL) {
        cod[index] = '\0';
        coduri[*k].caracter = root->c;
        strcpy(coduri[*k].cod, cod);
        (*k)++;
        return;
    }

    cod[index] = '0';
    genereaza_coduri(root->left, cod, index + 1, coduri, k);

    cod[index] = '1';
    genereaza_coduri(root->right, cod, index + 1, coduri, k);
}

void afisare_coduri(struct nod *root) {
    struct cod_huffman coduri[256];
    char cod[256];              
    int index = 0, k = 0;

    genereaza_coduri(root, cod, index, coduri, &k);

    qsort(coduri, k, sizeof(struct cod_huffman), compara);

    for (int i = 0; i < k; i++) {
        printf("%c:%s\n", coduri[i].caracter, coduri[i].cod);
    }
}

void afisare_frecvente(char *text) {
    int min1=256;
    int frecv[256] = {0};
    int fol[256] = {0};
    for (int i = 0; text[i]; i++) {
        frecv[(unsigned char)text[i]]++;
    }

for (int k = 0; k < 256; k++) {
    min1 = 256;
    for (int j = 0; j < 256; j++) {
        if (frecv[j] != 0 && frecv[j] < min1 && fol[j] == 0) {
            min1 = frecv[j];
        }
    }
    for (int i = 0; i < 256; i++) {
        if (frecv[i] == min1 && fol[i] == 0) {
            printf("%c:%d\n", (char)i, frecv[i]);
            fol[i] = 1;
        }
    }
}
}

struct nod * huffman_tree(){
    struct nod * nod_spatiu = malloc(sizeof(struct nod));
    struct nod * nod_c = malloc(sizeof(struct nod));
    struct nod * nod_e = malloc(sizeof(struct nod));
    struct nod * nod_s = malloc(sizeof(struct nod));
    struct nod * nod_l = malloc(sizeof(struct nod));
    struct nod * nod_t = malloc(sizeof(struct nod));
    struct nod * nod_u = malloc(sizeof(struct nod));
    struct nod * nod_a = malloc(sizeof(struct nod));
    struct nod * nod_38 = malloc(sizeof(struct nod));
    struct nod * nod_15 = malloc(sizeof(struct nod));
    struct nod * nod_23 = malloc(sizeof(struct nod));
    struct nod * nod_9 = malloc(sizeof(struct nod));
    struct nod * nod_11 = malloc(sizeof(struct nod));
    struct nod * nod_6 = malloc(sizeof(struct nod));
    struct nod * nod_3 = malloc(sizeof(struct nod));
    
    nod_38 -> data = 38;
    nod_38 -> c = '-';
    nod_38 -> left = nod_15;
    nod_38 -> right = nod_23;
    
    nod_15 -> data = 15;
    nod_15 -> c = '-';
    nod_15 -> left = nod_spatiu;
    nod_15 -> right = nod_9;
    
    nod_9 -> data = 9;
    nod_9 -> c = '-';
    nod_9 -> left = nod_c;
    nod_9 -> right = nod_e;
    
    nod_spatiu -> data = 6;
    nod_spatiu -> c = ' ';
    nod_spatiu -> left = NULL;
    nod_spatiu -> right = NULL;
 
    nod_c -> data = 4;
    nod_c -> c = 'c';
    nod_c -> left = NULL;
    nod_c -> right = NULL;
    
    nod_e -> data = 5;
    nod_e -> c = 'e';
    nod_e -> left = NULL;
    nod_e -> right = NULL;
    
    nod_23 -> data = 23;
    nod_23 -> c = '-';
    nod_23 -> left = nod_11;
    nod_23 -> right = nod_a;
    
    nod_11 -> data = 11;
    nod_11 -> c = '-';
    nod_11 -> left = nod_s;
    nod_11 -> right = nod_6;
    
    nod_a -> data = 12;
    nod_a -> c = 'a';
    nod_a -> left = NULL;
    nod_a -> right = NULL;
    
    nod_s -> data = 5;
    nod_s -> c = 's';
    nod_s -> left = NULL;
    nod_s -> right = NULL;
    
    nod_6 -> data = 6;
    nod_6 -> c = '-';
    nod_6 -> left = nod_3;
    nod_6 -> right = nod_u;
    
    nod_3 -> data = 3;
    nod_3 -> c = '-';
    nod_3 -> left = nod_l;
    nod_3 -> right = nod_t;
    
    nod_l -> data = 1;
    nod_l -> c = 'l';
    nod_l -> left = NULL;
    nod_l -> right = NULL;
    
    nod_u -> data = 3;
    nod_u -> c = 'u';
    nod_u -> left = NULL;
    nod_u -> right = NULL;
    
    nod_t -> data = 2;
    nod_t -> c = 't';
    nod_t -> left = NULL;
    nod_t -> right = NULL;
    
    return nod_38;
}