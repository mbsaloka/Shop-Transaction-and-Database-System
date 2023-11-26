#define ADMIN_NAME ""
#define ADMIN_PASSWORD ""

int adminLogin() {
    char username[101] = "", password[101] = "";
    while (strcmp(username, ADMIN_NAME) != 0 || strcmp(password, ADMIN_PASSWORD) != 0) {
        clearScreen();
        printBold("[MODE ADMIN]\n");
        printBold("Masukkan Username dan Password\n");
        printf("Username: ");
        getAlphaNum(username);
        if (strcmp(username, "ESCAPE") == 0) return 0;
        printf("Password: ");
        getPass(password);
        if (strcmp(password, "ESCAPE") == 0) return 0;

        if (strcmp(username, ADMIN_NAME) != 0) {
            printf("Username tidak dikenali!\n");
            printf("Coba login kembali? (Y/N) ");
            if (getYesNo() != 'Y') return 0;

        } else if (strcmp(password, ADMIN_PASSWORD) != 0) {
            printf("Password salah!\n");
            printf("Coba login kembali? (Y/N) ");
            if (getYesNo() != 'Y') return 0;
        }
    }

    clearScreen();
    printf("Selamat Datang %s!", username);
    sleep(1);

    return 1;
}

void admin() {
    if (!adminLogin()) return;
    clearScreen();
    int code;
    char *option[] = {
        "Tambah Barang",
        "Lihat Barang",
        "Tambah Membership",
        "Lihat Membership",
        "Lihat Catatan Traksaksi",
        "Keluar Dari Mode Admin",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printBold("[MODE ADMIN]\n");
        printBold("Ingin melakukan apa?\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            inputItem();
            break;
        case 1:
            char filter[101] = "\0";
            while (1) {
                clearScreen();
                showItem(filter);
                printBold("[FILTER] (Tekan Esc untuk kembali)\n");
                printf("Masukkan Filter : ");
                int ID = chooseData(tempFilterItem, sizeof(Item), numTempFilterItem, printLineItem);
                if (ID == -2) {
                    getFilter(filter);
                    if (strcmp(filter, "ESCAPE") == 0) break;
                } else if (ID == -1) {
                    break;
                } else {
                    updateItem(ID);
                }
            }
            break;
        case 2:
            inputMember();
            break;
        case 3:
            showMember("");
            while (1) {
                char filter[101];
                printBold("[FILTER] (Tekan Esc untuk kembali)\n");
                printf("Masukkan Filter : ");
                getFilter(filter);
                if (strcmp(filter, "ESCAPE") == 0) break;
                clearScreen();
                showMember(filter);
            }
            break;
        case 4:
            showTransactionLog();
            break;
        case 5:
            printBold("[Keluar Dari Mode Admin]\n");
            sleep(1);
            clearScreen();
            return;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
            clearScreen();
        }
    } while (code != lengthOption - 1);
}