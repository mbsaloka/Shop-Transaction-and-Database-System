#define ADMIN_NAME "Admin1"
#define PASSWORD "mbsaloka12"

void admin() {
    char username[100], pass[100], exitCode;
    while (strcmp(pass, PASSWORD) != 0 || strcmp(username, ADMIN_NAME) != 0) {
        clearScreen();
        printBold("[MODE ADMIN]\n");
        printBold("Masukkan Username dan Password\n");
        printf("Username: ");
        fflush(stdin);
        fgets(username, 100, stdin);
        printf("Password: ");
        fgets(pass, 100, stdin);

        username[strlen(username) - 1] = '\0';
        pass[strlen(pass) - 1] = '\0';

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
    printf("Selamat Datang %s!", ADMIN_NAME);
    sleep(1);
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