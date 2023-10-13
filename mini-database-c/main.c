#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "text_style.h"
#include "data_barang.h"
// #include "txt_manipulation.h"

int main(int argc, char const *argv[]) {
    int code;
    clearScreen();
    do {
        printBold("Ingin melakukan apa?\n");
        puts("(0) Akhiri Program");
        puts("(1) Tambah Barang");
        puts("(2) Lihat Barang");
        puts("(3) Tambah Membership");
        puts("(4) Lihat Membership");
        scanf("%d", &code);
        switch (code) {
        case 1:
            clearScreen();
            inputBarang();
            break;
        case 2:
            clearScreen();
            renderBarang();
            break;
        // case 3:
        //     clearScreen();
        //     inputMember();
        //     break;
        // case 4:
        //     clearScreen();
        //     renderMember();
        //     break;
        default:
            puts("Akhir dari program.");
        }
    } while (code != 0);

    return 0;
}
