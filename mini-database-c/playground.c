// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <conio.h>
// #include <time.h>
// #include <unistd.h>

// struct Cart {
//     int ID, price, stock;
//     char name[100];
// };

// int main() {
//     struct Cart item[100];
//     for (int i = 0; i < 100; i++) {
//         item[i].ID = i;
//     }

//     for (int i = 0; i < 100; i++) {
//         printf("%d\n", item[i].ID);
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <conio.h>
// #include <signal.h>
// #include <stdlib.h>

// void sigint_handler(int signo) {
//     printf("Ctrl+C ditekan, menangani sinyal SIGINT.\n");
//     // Tindakan yang sesuai untuk menangani sinyal SIGINT.
//     exit(1);  // Misalnya, keluar dari program.
// }

// int main() {
//     signal(SIGINT, sigint_handler);

//     printf("Program sedang berjalan. Tekan Ctrl+C untuk menghentikan.\n");

//     while (1) {
//         int input = getch();
//         printf("Anda menekan: %c\n", input);
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <conio.h>

// int main() {
//     printf("Program sedang berjalan. Tekan Ctrl+C untuk menghentikan.\n");

//     while (1) {
//         if (_kbhit()) {
//             int input = _getch();
//             if (input == 3) {  // ASCII value for Ctrl+C
//                 printf("Ctrl+C ditekan. Keluar dari program.\n");
//                 break;
//             } else {
//                 printf("Anda menekan: %c\n", input);
//             }
//         }
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <conio.h>
// #include <stdlib.h>

// int main() {
//     printf("Program sedang berjalan. Tekan Ctrl+C untuk menghentikan.\n");
//     int input, prev;
//     input = getch();
//     while (1) {
//         if (input == 3) {  // ASCII value for Ctrl+C
//             printf("Ctrl+C ditekan. Keluar dari program.\n");
//             exit(0);
//         }

//         if ((prev == '\0' || prev == 224) && input == 'P') {
//             printf("PANAH BAWAH\n");
//         }
//         if ((prev == '\0' || prev == 224) && input == 'H') {
//             printf("PANAH ATAS\n");
//         }
//         if ((prev == '\0' || prev == 224) && input == 'K') {
//             printf("PANAH KIRI\n");
//         }
//         if ((prev == '\0' || prev == 224) && input == 'M') {
//             printf("PANAH KANAN\n");
//         }

//         if (prev != '\0' && prev != 224 && input != '\0' && input != 224) {
//             printf("Anda menekan: %d %c\n", input, input);
//         }

//         prev = input;
//         input = getch();
//     }
//     return 0;
// }

// #include <stdio.h>
// #include <conio.h>
// #include <signal.h>

// int ctrlCPressed = 0;

// // Fungsi penanganan sinyal SIGINT
// void sigint_handler(int signo) {
//     printf("Ctrl+C ditekan, menangani sinyal SIGINT. Program berhenti.\n");
//     ctrlCPressed = 1;
// }

// int main() {
//     signal(SIGINT, sigint_handler);

//     printf("Program sedang berjalan. Tekan Ctrl+C untuk menghentikan.\n");

//     while (!ctrlCPressed) {
//         if (_kbhit()) {
//             int input = _getch();
//             if (input == 3) {  // ASCII value for Ctrl+C
//                 printf("Ctrl+C ditekan. Keluar dari program.\n");
//                 break;
//             } else {
//                 printf("Anda menekan: %c\n", input);
//             }
//         }
//     }
//     printf("ADAD");
//     return 0;
// }

// #include <stdio.h>
// #include <string.h>

// void modifyStringArray(char *strings[], int length) {
//     for (int i = 0; i < length; i++) {
//         // strcat(strings[i], " (modified)");
//         printf("%s\n", strings[i]);
//     }
// }

// int main() {
//     char *strings[] = {
//         "String pertama",
//         "String kedua",
//         "String ketiga"};

//     int length = sizeof(strings) / sizeof(strings[0]);

//     // printf("Sebelum pemanggilan fungsi:\n");
//     // for (int i = 0; i < length; i++) {
//     //     printf("String %d: %s\n", i, strings[i]);
//     // }

//     modifyStringArray(strings, length);

//     // printf("\nSetelah pemanggilan fungsi:\n");
//     // for (int i = 0; i < length; i++) {
//     //     printf("String %d: %s\n", i, strings[i]);
//     // }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "text_style.h"

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
            clearScreen();
            strcpy(str, "ESCAPE");
            break;
        }
    }
    str[i] = '\0';
    return str;
}

int main() {
    char *nama;
    nama = getAlpha();
    printf("%s\n", nama);
    printf("HALO1\n");
    free(nama);  // Membebaskan memori yang dialokasikan dalam getAlpha
    printf("HALO2\n");
}
