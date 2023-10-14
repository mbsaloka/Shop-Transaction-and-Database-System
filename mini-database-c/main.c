#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "text_style.h"
#include "get_time.h"
#include "data_barang.h"
#include "data_member.h"
// #include "txt_manipulation.h"

int main(int argc, char const *argv[]) {
    int code;
    // clearScreen();
    do {
        printBold("Ingin melakukan apa?\n");
        puts("(0) Akhiri Program");
        puts("(1) Tambah Barang");
        puts("(2) Lihat Barang");
        puts("(3) Tambah Membership");
        puts("(4) Lihat Membership");
        scanf("%d", &code);
        clearScreen();
        switch (code) {
        case 1:
            inputBarang();
            break;
        case 2:
            renderBarang();
            break;
        case 3:
            inputMember();
            break;
        case 4:
            renderMember();
            break;
        default:
            puts("Akhir dari program.");
        }
    } while (code != 0);

    return 0;
}
