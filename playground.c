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

// #include <stdio.h>

// int main() {
//     char ID[100], namaBarang[100];
//     int harga, stok;

//     printf("TAMBAHKAN BARANG BARU\n");
//     printf("ID: ");
//     scanf("%s", &ID);
//     printf("Nama Barang: ");
//     scanf("%s", &namaBarang);
//     printf("Harga: ");
//     scanf("%d", &harga);
//     printf("Stok: ");
//     scanf("%d", &stok);
// }

#include <stdio.h>
#include <string.h>

// Definisikan struktur data untuk menyimpan informasi pelanggan
struct Customer {
    int ID;
    char Nama[100];
    char NoTelp[20];
    char Alamat[100];
    char TanggalDaftar[11];
    char WaktuDaftar[9];
};

// Fungsi untuk mengecek apakah nomor telepon sudah ada dalam database
int isPhoneNumberExist(struct Customer customers[], int numCustomers, char noTelp[]) {
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(customers[i].NoTelp, noTelp) == 0) {
            return 1;  // Nomor telepon sudah ada dalam database
        }
    }
    return 0;  // Nomor telepon belum ada dalam database
}

int main() {
    struct Customer customers[100];  // Maksimal 100 pelanggan
    int numCustomers = 2;            // Jumlah pelanggan awal

    // Mengisi data awal
    customers[0].ID = 1;
    strcpy(customers[0].Nama, "Muh Buyung Saloka");
    strcpy(customers[0].NoTelp, "082141977680");
    strcpy(customers[0].Alamat, "Jl. Ababil No. 5");
    strcpy(customers[0].TanggalDaftar, "14/10/2023");
    strcpy(customers[0].WaktuDaftar, "21:03:23");

    customers[1].ID = 2;
    strcpy(customers[1].Nama, "Nazwarahma Hannum");
    strcpy(customers[1].NoTelp, "08121652240");
    strcpy(customers[1].Alamat, "Jl. Soekarno Hatta 40");
    strcpy(customers[1].TanggalDaftar, "14/10/2023");
    strcpy(customers[1].WaktuDaftar, "21:04:59");

    // Input data baru
    struct Customer newCustomer;
    printf("Masukkan Nama Pelanggan: ");
    scanf("%s", newCustomer.Nama);
    printf("Masukkan No Telp: ");
    scanf("%s", newCustomer.NoTelp);

    if (isPhoneNumberExist(customers, numCustomers, newCustomer.NoTelp)) {
        printf("Nomor telepon sudah ada dalam database.\n");
    } else {
        // Tambahkan data baru ke database
        numCustomers++;
        newCustomer.ID = numCustomers;
        printf("Masukkan Alamat: ");
        scanf("%s", newCustomer.Alamat);
        printf("Masukkan Tanggal Daftar: ");
        scanf("%s", newCustomer.TanggalDaftar);
        printf("Masukkan Waktu Daftar: ");
        scanf("%s", newCustomer.WaktuDaftar);

        customers[numCustomers - 1] = newCustomer;
        printf("Data pelanggan baru telah ditambahkan.\n");
    }

    // Tampilkan data pelanggan dalam database
    printf("\nData Pelanggan:\n");
    for (int i = 0; i < numCustomers; i++) {
        printf("ID: %d\n", customers[i].ID);
        printf("Nama: %s\n", customers[i].Nama);
        printf("No Telp: %s\n", customers[i].NoTelp);
        printf("Alamat: %s\n", customers[i].Alamat);
        printf("Tanggal Daftar: %s\n", customers[i].TanggalDaftar);
        printf("Waktu Daftar: %s\n", customers[i].WaktuDaftar);
        printf("\n");
    }

    return 0;
}
