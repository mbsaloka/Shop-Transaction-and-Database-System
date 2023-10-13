// #include <stdio.h>
// #include <unistd.h>

// int main() {
//     // for (int i = 0; i < 10; i++) {
//     //     printf("Baris ke-%d\r", i);
//     //     fflush(stdout); // Memastikan output segera ditampilkan
//     //     // Disarankan menggunakan fflush untuk memastikan output segera ditampilkan pada terminal.
//     // }

//     // printf("\n"); // Mengakhiri baris terakhir

//     // printf("Hello");

//     // printf("\33[2K\r");
//     // printf("Bye");

//     int i = 3;
//     printf("\nText to keep\n");
//     printf("Text to erase****************************\n");
//     while(i >= 0) { // 3 second countdown
//         printf("\033[A\33[2KT\rT minus %d seconds...\n", i);
//         i--;
//         sleep(1);
//     }

//     return 0;
// }

/*
\33[2K erases the entire line your cursor is currently on

\033[A moves your cursor up one line, but in the same column i.e. not to the start of the line

\r brings your cursor to the beginning of the line (r is for carriage return N.B. carriage returns do not include a newline so cursor remains on the same line) but does not erase anything
*/

// #include <curses.h>

// int main() {
//     initscr();             // Inisialisasi layar "curses"
//     keypad(stdscr, TRUE);  // Aktifkan pemrosesan tombol fungsi

//     int ch;
//     while ((ch = getch()) != 'q') {  // Loop hingga tombol 'q' ditekan
//         if (ch == KEY_UP) {
//             printw("Panah Atas\n");
//         } else if (ch == KEY_DOWN) {
//             printw("Panah Bawah\n");
//         }
//         refresh();  // Perbarui layar
//     }

//     endwin();  // Akhiri mode "curses"
//     return 0;
// }

#include <stdio.h>

int main() {
    char ID[100], namaBarang[100];
    int harga, stok;

    printf("TAMBAHKAN BARANG BARU\n");
    printf("ID: ");
    scanf("%s", &ID);
    printf("Nama Barang: ");
    scanf("%s", &namaBarang);
    printf("Harga: ");
    scanf("%d", &harga);
    printf("Stok: ");
    scanf("%d", &stok);
}