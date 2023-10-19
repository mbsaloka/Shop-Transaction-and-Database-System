#define ADMIN_NAME "Admin1"
#define PASSWORD "mbsaloka12"

void admin() {
    char *username, *pass, exitCode;
    while (strcmp(pass, PASSWORD) != 0 || strcmp(username, ADMIN_NAME) != 0) {
        clearScreen();
        printBold("[MODE ADMIN]\n");
        printBold("Masukkan Username dan Password\n");
        printf("Username: ");
        fflush(stdin);
        username = getAllChar();
        if (strcmp(username, "ESCAPE") == 0) return;
        // fgets(username, 101, stdin);
        // username[strlen(username) - 1] = '\0';
        printf("Password: ");
        pass = getAllChar();
        if (strcmp(pass, "ESCAPE") == 0) return;
        // fgets(pass, 101, stdin);
        // pass[strlen(pass) - 1] = '\0';

        if (strcmp(username, ADMIN_NAME) != 0) {
            printf("Username tidak dikenali!\n");
            printf("Coba login kembali? (Y/N) ");
            exitCode = getYesNo();
            if (exitCode != 'Y') return;

        } else if (strcmp(pass, PASSWORD) != 0) {
            printf("Password salah!\n");
            printf("Coba login kembali? (Y/N) ");
            exitCode = getYesNo();
            if (exitCode != 'Y') return;
        }
    }

    clearScreen();
    printf("Selamat Datang %s!", username);
    sleep(1);
    free(username);
    free(pass);
    clearScreen();
    int code;
    char *option[] = {
        "(0) Keluar Dari Mode Admin",
        "(1) Tambah Barang",
        "(2) Lihat Barang",
        "(3) Tambah Membership",
        "(4) Lihat Membership",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        printBold("[MODE ADMIN]\n");
        printBold("Ingin melakukan apa?\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            printBold("[Keluar Dari Mode Admin]\n");
            sleep(1);
            clearScreen();
            return;
        case 1:
            inputItem();
            break;
        case 2:
            showItem(0);
            break;
        case 3:
            inputMember();
            break;
        case 4:
            showMember();
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
            clearScreen();
        }
    } while (code != 0);
}