#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#include "text_style.h"
#include "arrow_input.h"
#include "limited_input.h"
#include "get_time.h"
#include "item.h"
#include "member.h"
#include "shopping.h"
#include "admin.h"
#include "user.h"

int main(int argc, char const *argv[]) {
    int code;
    char *option[] = {
        "(0) Akhiri Program",
        "(1) Login Sebagai Admin",
        "(2) Login Sebagai Pelanggan",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printBold("Selamat Datang di Sistem\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            printBold("[Akhir dari program.]\n");
            break;
        case 1:
            admin();
            break;
        case 2:
            user();
            clearScreen();
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);

    return 0;
}
