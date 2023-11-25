#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

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

void getNum(char *str) {
    int length = 20;
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= '0' && c <= '9') && i < length) {
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

int getNumINT() {
    char str[20];
    getNum(str);
    if (strcmp(str, "ESCAPE") == 0) return -1;
    int num = atoi(str);
    return num;
}

char getYesNo() {
    char key, c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if (c == 'y' || c == 'n') c -= 32;
        if ((c == 'Y' || c == 'N') && i == 0) {
            printf("%c", c);
            key = c;
            i++;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            key = ' ';
            i--;
        }
        if (c == 3) exit(0);      // Ctrl + C
        if (c == 27) return 'E';  // Esc
        if (c == 13) i == 0 ? c = 0 : printf("\n");
    }
    return key;
}

void getAlphaNum(char *str) {
    int length = 100;
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ') && i < length) {
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

void getAllChar(char *str) {
    int length = 100;
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= 32 && c <= 126) && i < length) {
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

void getPass(char *str) {
    int length = 100;
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= 32 && c <= 126) && i < length) {
            printf("*");
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

void getFilter(char *str) {
    int length = 100;
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= 32 && c <= 126) && i < length) {
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
            if (i == 0) str[i] = '\0';
        }
    }
}

char getEnter() {
    char key, c;
    int i = 0;
    while (c != 13 && c != 27) {  // ASCII 13 = enter
        c = getch();
        if (c == 3) exit(0);  // Ctrl + C
    }
    return 'E';
}