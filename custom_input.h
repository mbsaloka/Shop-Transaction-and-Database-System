#define MIN(a, b) (a < b ? a : b)

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
    int i = strlen(str);
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
    char str[50] = "\0";
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
    int i = strlen(str);
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
    str[0] = '\0';
    char c = getch();
    if (c == 13 || c == 27) {
        return;
    } else if (c == 3) {
        exit(0);
    } else {
        printf("%-50.s");
        CURSOR_LEFT(50);
        str[0] = c;
        str[1] = '\0';
        putchar(c);
        getAllChar(str);
        if (strcmp(str, "ESCAPE") == 0) {
            str[0] = '\0';
            return;
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
    return c;
}

int getTabStr(char *str, char *defaultStr) {
    char c = getch();
    if (c == 9 || c == 13) {
        strcpy(str, defaultStr);
        printf("%s\n", str);
    } else if (c == 27) {
        return -1;
    } else if (c == 3) {
        exit(0);
    } else {
        printf("%-100.s");
        CURSOR_LEFT(100);
        str[0] = c;
        str[1] = '\0';
        putchar(c);
        getAllChar(str);
        if (strcmp(str, "ESCAPE") == 0) return -1;
    }
    return 1;
}

int getTabNumStr(char *str, char *defaultStr) {
    char c;
    do {
        c = getch();
        if (c == 9 || c == 13) {
            strcpy(str, defaultStr);
            printf("%s\n", str);
            return 1;
        } else if (c == 27) {
            return -1;
        } else if (c == 3) {
            exit(0);
        }
    } while (c < '0' || c > '9');

    printf("%-100.s");
    CURSOR_LEFT(100);
    str[0] = c;
    str[1] = '\0';
    putchar(c);
    getNum(str);
    if (strcmp(str, "ESCAPE") == 0) return -1;

    return 1;
}

int getTabInt(int *num, int defaultNum) {
    char c, strNum[50] = "\0";
    do {
        c = getch();
        if (c == 9 || c == 13) {
            *num = defaultNum;
            printf("%d\n", *num);
            return 1;
        } else if (c == 27) {
            return -1;
        } else if (c == 3) {
            exit(0);
        }
    } while (c < '0' || c > '9');

    printf("%-100.s");
    CURSOR_LEFT(100);
    strNum[0] = c;
    strNum[1] = '\0';
    putchar(c);
    getNum(strNum);
    *num = atoi(strNum);
    if (strcmp(strNum, "ESCAPE") == 0) return -1;
    return 1;
}

void pause() {
    printf("%sTekan Enter untuk melanjutkan...\n", HIDE_CURSOR);
    getEnter();
    CLEAR_ROW(1);
    printf("%s", SHOW_CURSOR);
}