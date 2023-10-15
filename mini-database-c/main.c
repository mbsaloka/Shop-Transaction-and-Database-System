#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "text_style.h"
#include "get_time.h"
#include "item.h"
#include "member.h"
#include "admin.h"
#include "user.h"
#include "user_belanja.h"

int main(int argc, char const *argv[]) {
    int code;
    do {
        clearScreen();
        printBold("Selamat Datang di Sistem\n");
        puts("(0) Akhiri Program");
        puts("(1) Login Sebagai Admin");
        puts("(2) Login Sebagai Pelanggan");
        scanf("%d", &code);
        clearScreen();
        switch (code) {
        case 1:
            admin();
            break;
        case 2:
            user();
            clearScreen();
            break;
        default:
            printBold("[Akhir dari program.]\n");
        }
    } while (code != 0);

    return 0;
}
