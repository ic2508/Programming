#include <stdio.h>
#include <stdlib.h>

struct Joc_Carti {
    char *name;
    int card;
    struct Joc_Carti *next;  
};

struct Joc_Carti* create_node() {
    struct Joc_Carti *node = (struct Joc_Carti*)malloc(sizeof(struct Joc_Carti));
    node->name = (char *)calloc(256, sizeof(char));
    scanf("%255s", node->name);
    node->next = NULL;
    return node;
}

struct Joc_Carti* add_Joc_Carti(struct Joc_Carti *head) {
    struct Joc_Carti *new_Joc_Carti = create_node();
    
    if (head == NULL) {
        return new_Joc_Carti;
    }

    struct Joc_Carti *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_Joc_Carti;
    return head;
}

void input_cards(struct Joc_Carti *head) {
    struct Joc_Carti *current = head;
    while (current != NULL) {
        scanf("%d", &current->card);
        current = current->next;
    }
}

struct Joc_Carti* remove_Joc_Carti(struct Joc_Carti *head, int index) {
    if (head == NULL) 
    return NULL;

    struct Joc_Carti *current = head;

    if(index == 0){ 
        head = current->next;
        free(current->name);
        free(current);
        return head;
    }

    int cnt = 0;
    struct Joc_Carti *prev = NULL;
    while (current != NULL && cnt < index) {
        prev = current;
        current = current->next;
        cnt++;
    }

    if (current == NULL) 
    return head;

    prev->next = current->next;
    free(current->name);
    free(current);
    return head;
}

void display_Joc_Cartis(struct Joc_Carti *head) {
    struct Joc_Carti *current = head;
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

struct Joc_Carti* eliminate_Joc_Carti(struct Joc_Carti *head) {
    if (head == NULL) 
    return NULL;

    struct Joc_Carti *current = head;
    struct Joc_Carti *min_Joc_Carti = head;
    int min_value = head->card;
    int min_index = 0, index = 0;

    while (current != NULL) {
        if (current->card < min_value) {
            min_value = current->card;
            min_Joc_Carti = current;
            min_index = index;
        }
        current = current->next;
        index++;
    }

    head = remove_Joc_Carti(head, min_index);
    return head;
}

int main(){
    int n;
    scanf("%d", &n);
    struct Joc_Carti *Joc_Cartis = NULL;

    for (int i = 0; i < n; ++i) {
        Joc_Cartis = add_Joc_Carti(Joc_Cartis);
    }
    display_Joc_Cartis(Joc_Cartis);
    while(Joc_Cartis != NULL){
        input_cards(Joc_Cartis);  
        Joc_Cartis = eliminate_Joc_Carti(Joc_Cartis);
        display_Joc_Cartis(Joc_Cartis);
    }
    return 0;
}
