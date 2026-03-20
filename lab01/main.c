#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    char* token;  // token 字串
    struct Node* next;
} Node;

Node* head = NULL;

// 插入 token 到鏈結串列頭部
void insert_token(char* tok) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->token = (char*)malloc(strlen(tok) + 1);
    strcpy(newNode->token, tok);
    newNode->next = head;
    head = newNode;
}

// 檢查關鍵字
int is_keyword(char* str) {
    return strcmp(str, "if") == 0 || strcmp(str, "while") == 0;  // 可擴充
}

// 輸出鏈結串列
void print_tokens() {
    Node* current = head;
    printf("Tokens: ");
    while (current != NULL) {
        printf("\"%s\" ", current->token);
        current = current->next;
    }
    printf("\n");
}

int main() {
    FILE* file = fopen(__FILE__, "r");
    int c;
    char buffer[256] = {0};
    int idx = 0;

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", __FILE__);
        return 1;
    }

    while ((c = fgetc(file)) != EOF) {
        if (isspace((unsigned char)c)) {
            if (idx > 0) {
                buffer[idx] = '\0';
                insert_token(buffer);
                idx = 0;
            }
            continue;
        }
        if (ispunct((unsigned char)c) || isalpha((unsigned char)c) || isdigit((unsigned char)c)) {
            buffer[idx++] = (char)c;
            if (idx >= 255) {
                buffer[idx] = '\0';
                insert_token(buffer);
                idx = 0;
            }
        }
    }
    if (idx > 0) {
        buffer[idx] = '\0';
        insert_token(buffer);
    }

    print_tokens();
    fclose(file);

    // 釋放記憶體
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp->token);
        free(temp);
    }
    return 0;
}
