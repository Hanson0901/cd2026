#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int times;
    char* character;
    struct Node* next;
}Node;

int main(){
    FILE* file = fopen("main.c","r");
    if(file == NULL){
        printf("Error opening file\n");
        return 1;
    }
    Node* head = NULL;
    char c;
    while((c = fgetc(file)) != EOF){
        Node* current = head;
        while(current != NULL){
            if(current->character[0] == c){
                current->times++;
                break;
            }
            current = current->next;
        }
        if(current == NULL){
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->times = 1;
            newNode->character = (char*)malloc(2*sizeof(char));
            newNode->character[0] = c;
            newNode->character[1] = '\0';
            newNode->next = head;
            head = newNode;
        }
    }

    printf("Character\tTimes\n");
    Node* current = head;
    while(current != NULL){
        if(current->character[0] == '\n'){
            printf("\\n\t\t%d\n", current->times);
        } else if(current->character[0] == '\t'){
            printf("TAB\t%d\n", current->times);
        } else if(current->character[0] == ' '){
            printf("space\t\t%d\n", current->times);
        } else {
            printf("%c\t\t%d\n", current->character[0], current->times);
        }
        current = current->next;
    }

    fclose(file);
    return 0;
}