#include <stdio.h>

static void print_token(int ch) {
    if (ch == ' ') {
        printf("'_'");
    } else if (ch == '\n') {
        printf("'\\n'");
    } else if (ch == '\t') {
        printf("'\\t'");
    } else if (ch == '\\') {
        printf("'\\\\'");
    } else if (ch == '\'') {
        printf("'\\\''");
    } else {
        printf("'%c'", ch);
    }
}

int main(void) {
    FILE *file = fopen("main.c", "r");
    int ch;
    int first = 1;

    if (file == NULL) {
        printf("Error: cannot open main.c\n");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        if (!first) {
            printf(", ");
        }
        print_token(ch);
        first = 0;
    }

    printf("\n");
    fclose(file);
    return 0;
}