#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#include "text_style.h"
#include "data_manipulation.h"
#include "get_time.h"
#include "custom_input.h"
#include "arrow_input.h"
#include "item.h"
// #include "member.h"
#include "bill.h"
// #include "transaction_log.h"
// #include "shopping.h"
#include "admin.h"
// #include "user.h"

int main(int argc, char const *argv[]) {
    importItemFromDb();
    // importFromDb(member, sizeof(Member), &numMember, FILE_MEMBER);
    // importFromDb(transaction, sizeof(Transaction), &numTransaction, FILE_TRANSACTION);

    int code;
    char *option[] = {
        "Login Sebagai Admin",
        "Login Sebagai Pelanggan",
        "Akhiri Program",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printBold("Selamat Datang di ITS MIRT\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            admin();
            break;
            // case 1:
            //     user();
            //     clearScreen();
            //     break;
            // case 2:
            //     printBold("[Akhir dari program.]\n");
            //     break;
            // default:
            //     printBold("Input tidak valid.\n");
            //     sleep(1);
        }
    } while (code != lengthOption - 1);

    Item *current = item;
    while (current != NULL) {
        free(current);
        current = current->next;
    }

    return 0;
}
