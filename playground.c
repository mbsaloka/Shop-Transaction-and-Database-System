#include <stdio.h>
#include <unistd.h>

int main() {
    // for (int i = 0; i < 10; i++) {
    //     printf("Baris ke-%d\r", i);
    //     fflush(stdout); // Memastikan output segera ditampilkan
    //     // Disarankan menggunakan fflush untuk memastikan output segera ditampilkan pada terminal.
    // }

    // printf("\n"); // Mengakhiri baris terakhir


    // printf("Hello");
    
    // printf("\33[2K\r");
    // printf("Bye");

    int i = 3;
    printf("\nText to keep\n");
    printf("Text to erase****************************\n");
    while(i >= 0) { // 3 second countdown
        printf("\033[A\33[2KT\rT minus %d seconds...\n", i);
        i--;
        sleep(1);
    }

    return 0;
}


/*
\33[2K erases the entire line your cursor is currently on

\033[A moves your cursor up one line, but in the same column i.e. not to the start of the line

\r brings your cursor to the beginning of the line (r is for carriage return N.B. carriage returns do not include a newline so cursor remains on the same line) but does not erase anything
*/