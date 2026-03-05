#include <stdio.h>
#include <stdlib.h>

struct Cuvant{
    char c;
    struct Cuvant *next;
};

struct Cuvant *creare_nod(){
    struct Cuvant *nod = (struct Cuvant*)calloc(sizeof(struct Cuvant));
}

struct Cuvant *adaugare(struct Cuvant *head,char c){
    struct Cuvant *nou = creare_nod();
    struct Cuvant *curent;
    if(head==NULL)
    return nou;
    curent=head;
    while(curent->next!=NULL){
        curent=curent->next;
    }
    curent=creare_nod();
    return head;
}

int main(){
    struct Cuvant *C=0;
    char c = 'a';
    while(c!=NULL){
        C=adaugare(C,c)
    }
}








V1:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 1000

struct Node {
    char letter;
    struct Node* next;
};

bool is_vowel(char c) {
    char vowels[] = "aeiouäöüAEIOUÄÖÜ";
    return strchr(vowels, c) != NULL;
}

void add_node(struct Node** head, char letter) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->letter = letter;
    new_node->next = *head;
    *head = new_node;
}

void free_list(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void get_reverse_string_from_list(struct Node* head, char* result) {
    int index = 0;
    while (head != NULL) {
        result[index++] = head->letter;
        head = head->next;
    }
    result[index] = '\0';
}

int main() {
    char word[MAX_NAME_LENGTH];
    struct Node* vowels = NULL;
    struct Node* consonants = NULL;

    printf("Introduceti un cuvant in limba germana: ");
    scanf("%s", word);

    // Separating vowels and consonants
    for (int i = 0; i < strlen(word); i++) {
        if (is_vowel(word[i])) {
            add_node(&vowels, word[i]);
        } else {
            add_node(&consonants, word[i]);
        }
    }

    char vowel_str[MAX_NAME_LENGTH];
    char consonant_str[MAX_NAME_LENGTH];
    get_reverse_string_from_list(vowels, vowel_str);
    get_reverse_string_from_list(consonants, consonant_str);

    char result[MAX_NAME_LENGTH];
    int result_index = 0;
    int vowel_count = strlen(vowel_str);
    int consonant_count = strlen(consonant_str);

    for (int i = 0; i < vowel_count || i < consonant_count; i++) {
        if (i < vowel_count) {
            result[result_index++] = vowel_str[i];
        }
        if (i < consonant_count) {
            result[result_index++] = consonant_str[i];
        }
    }

    result[result_index] = '\0';
    printf("Cuvantul reordonat: %s\n", result);

    free_list(vowels);
    free_list(consonants);

    return 0;
}


V2:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 1000

struct Node {
    char letter;
    struct Node* next;
};

bool is_vowel(char c) {
    char vowels[] = "aeiouäöüAEIOUÄÖÜ";
    return strchr(vowels, c) != NULL;
}

void add_node(struct Node** head, char letter) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->letter = letter;
    new_node->next = *head;
    *head = new_node;
}

void free_list(struct Node* head) {
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void get_reverse_string_from_list(struct Node* head, char* result) {
    int index = 0;
    while (head != NULL) {
        result[index++] = head->letter;
        head = head->next;
    }
    result[index] = '\0';
}

int main() {
    char word[MAX_NAME_LENGTH];
    struct Node* vowels = NULL;
    struct Node* consonants = NULL;
    
    scanf("%s", word);

    for (int i = 0; i < strlen(word); i++) {
        if (is_vowel(word[i])) {
            add_node(&vowels, word[i]);
        } else {
            add_node(&consonants, word[i]);
        }
    }

    char vowel_str[1000];
    char consonant_str[1000];
    get_reverse_string_from_list(vowels, vowel_str);
    get_reverse_string_from_list(consonants, consonant_str);

    char result[1000];
    int result_index = 0;
    int vowel_count = strlen(vowel_str);
    int consonant_count = strlen(consonant_str);

    for (int i = 0; i < vowel_count || i < consonant_count; i++) {
        if (i < vowel_count) {
            result[result_index++] = vowel_str[i];
        }
        if (i < consonant_count) {
            result[result_index++] = consonant_str[i];
        }
    }

    result[result_index] = '\0';
    printf("%s\n", result);

    free_list(vowels);
    free_list(consonants);

    return 0;
}
