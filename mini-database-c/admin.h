#define ADMIN_NAME ""
#define PASSWORD ""

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
    printBold("[MODE ADMIN]\n");
    int code;
    do {
        printBold("Ingin melakukan apa?\n");
        puts("(0) Keluar Dari Mode Admin");
        puts("(1) Tambah Barang");
        puts("(2) Lihat Barang");
        puts("(3) Tambah Membership");
        puts("(4) Lihat Membership");
        code = getNumINT();
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
            renderItem();
            break;
        case 3:
            inputMember();
            break;
        case 4:
            renderMember();
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
            clearScreen();
        }
    } while (code != 0);
}