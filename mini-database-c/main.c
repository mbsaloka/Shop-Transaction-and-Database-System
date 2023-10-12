#include <stdio.h>

#include "text_style.h"

FILE *inp, *outp;

void renderData() {
    inp = fopen("output.txt", "r");

    if (inp == NULL) {
        puts("File failed to open");
        return;
    }

    puts("\x1b[1mDATA MAHASISWA\x1b[0m");
    char nama[100], NRP[100], jurusan[100];

    // Header
    printf("\x1b[4m\x1b[1mNama\t| NRP\t| Jurusan\x1b[0m\n");

    while (fscanf(inp, "%s %s %s", nama, NRP, jurusan) == 3) {
        printf("%s\t| %s\t| %s\n", nama, NRP, jurusan);
    }

    fclose(inp);
}

void inputData() {
    char nama[100], NRP[100], jurusan[100];

    printf("\x1b[1mMASUKKAN DATA MAHASISWA\x1b[0m\n");
    printf("Nama: ");
    scanf("%s", &nama);
    printf("NRP: ");
    scanf("%s", &NRP);
    printf("Jurusan: ");
    scanf("%s", &jurusan);

    outp = fopen("output.txt", "a");
    fprintf(outp, "%s %s %s\n", nama, NRP, jurusan);
    fclose(outp);
}

int main(int argc, char const *argv[]) {
    int code;
    clearScreen();
    do {
        puts("\x1b[1mIngin melakukan apa?\x1b[0m");
        puts("(0) Akhiri Program");
        puts("(1) Tambah Data");
        puts("(2) Lihat Data");
        scanf("%d", &code);
        switch (code) {
        case 1:
            clearScreen();
            inputData();
            break;
        case 2:
            clearScreen();
            renderData();
            break;
        default:
            puts("Akhir dari program.");
        }
    } while (code != 0);

    return 0;
}
