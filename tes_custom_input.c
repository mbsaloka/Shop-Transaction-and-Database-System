#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void getAlpha(char *str) {
    int length = 100;
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') && i < length) {
            printf("%c", c);
            str[i++] = c;
            str[i] = '\0';
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            str[--i] = '\0';
        }
        if (c == 3) exit(0);  // Ctrl + C
        if (c == 27) {        // Esc
            strcpy(str, "ESCAPE");
            return;
        }
        if (c == 13) {
            i == 0 ? c = 0 : printf("\n");
        }
    }
}

int main() {
    char input[10];
    printf("INPUT : ");
    getAlpha(input);
    printf("HASIL : %s", input);
}