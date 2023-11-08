#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

char *getAlpha() {
    int length = 100;
    char *str = (char *)malloc(length + 1);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') && i < length) {
            printf("%c", c);
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
        if (c == 3) exit(0);  // Ctrl + C
        if (c == 27) {        // Esc
            free(str);
            clearScreen();
            return "ESCAPE";
        }
        if (c == 13) {
            i == 0 ? c = 0 : printf("\n");
        }
    }
    str[i] = '\0';
    return str;
}

char *getNum() {
    int length = 20;
    char *str = (char *)malloc(length + 1);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= '0' && c <= '9') && i < length) {
            printf("%c", c);
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
        if (c == 3) exit(0);  // Ctrl + C
        if (c == 27) {        // Esc
            free(str);
            clearScreen();
            return "ESCAPE";
        }
        if (c == 13) {
            i == 0 ? c = 0 : printf("\n");
        }
    }
    str[i] = '\0';
    return str;
}

int getNumINT() {
    char *str = getNum();
    if (strcmp(str, "ESCAPE") == 0) {
        return -1;
    }
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
        if (c == 13) {
            i == 0 ? c = 0 : printf("\n");
        }
    }
    return key;
}

char *getAlphaNum() {
    int length = 100;
    char *str = (char *)malloc(length + 1);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ') && i < length) {
            printf("%c", c);
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
        if (c == 3) exit(0);  // Ctrl + C
        if (c == 27) {        // Esc
            free(str);
            clearScreen();
            return "ESCAPE";
        }
        if (c == 13) {
            i == 0 ? c = 0 : printf("\n");
        }
    }
    str[i] = '\0';
    return str;
}

char *getAllChar() {
    int length = 100;
    char *str = (char *)malloc(length + 1);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= 32 && c <= 126) && i < length) {
            printf("%c", c);
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
        if (c == 3) exit(0);  // Ctrl + C
        if (c == 27) {        // Esc
            free(str);
            clearScreen();
            return "ESCAPE";
        }
        if (c == 13) {
            i == 0 ? c = 0 : printf("\n");
        }
    }
    str[i] = '\0';
    return str;
}

char *getPass() {
    int length = 100;
    char *str = (char *)malloc(length + 1);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= 32 && c <= 126) && i < length) {
            // printf("%c", c);
            printf("*");
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
        if (c == 3) exit(0);  // Ctrl + C
        if (c == 27) {        // Esc
            free(str);
            clearScreen();
            return "ESCAPE";
        }
        if (c == 13) {
            i == 0 ? c = 0 : printf("\n");
        }
    }
    str[i] = '\0';
    return str;
}

char *getFilter() {
    int length = 100;
    char *str = (char *)malloc(length + 1);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= 32 && c <= 126) && i < length) {
            printf("%c", c);
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
        if (c == 3) exit(0);  // Ctrl + C
        if (c == 27) {        // Esc
            free(str);
            clearScreen();
            return "ESCAPE";
        }
        if (c == 13) {
            if (i == 0) {
                strcpy(str, "");
                return str;
            } else {
                printf("\n");
            }
        }
    }
    str[i] = '\0';
    return str;
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