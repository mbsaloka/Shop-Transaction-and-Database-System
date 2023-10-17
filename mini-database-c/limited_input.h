#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

char *getAlpha() {
    char *str = (char *)malloc(100);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ') {
            printf("%c", c);
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
    }
    str[i] = '\0';
    return str;
}

char *getNum() {
    char *str = (char *)malloc(100);
    char c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if (c >= '0' && c <= '9') {
            printf("%c", c);
            str[i++] = c;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }
    }
    str[i] = '\0';
    return str;
}

int getNumINT() {
    char *str = getNum();
    int num = atoi(str);
    free(str);
    return num;
}

char getYesNo() {
    char key, c;
    int i = 0;
    while (c != 13) {  // ASCII 13 = enter
        c = getch();
        if (c == 'Y' || c == 'N') {
            printf("%c", c);
            key = c;
            i++;
        } else if (c == 8 && i > 0) {  // ASCII 8 = backspace
            printf("%c %c", c, c);
            i--;
        }

        if (c == 13 && (key != 'Y' && key != 'N')) {
            c = ' ';
        }
    }
    return key;
}

// int main() {
//     char *nama;
//     char *noTelp;
//     printf("Masukkan nama : ");
//     nama = getAlpha();

//     printf("\nMasukkan no Telp : ");
//     noTelp = getNum();

//     printf("\nNAMA : %s\n", nama);
//     printf("NO TELP : %s\n", noTelp);

//     free(nama);
//     free(noTelp);
// }