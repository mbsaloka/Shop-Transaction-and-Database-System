#define ADMIN_NAME "Admin1"
#define PASSWORD "mbsaloka12"

void admin() {
    char username[100], pass[100], exitCode[10];
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
            scanf("%s", exitCode);
            if (strcmp(exitCode, "Y") != 0 && strcmp(exitCode, "y") != 0) return;
        } else if (strcmp(pass, PASSWORD) != 0) {
            printf("Password salah!\n");
            printf("Coba login kembali? (Y/N) ");
            scanf("%s", exitCode);
            if (strcmp(exitCode, "Y") != 0 && strcmp(exitCode, "y") != 0) return;
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
        scanf("%d", &code);
        clearScreen();
        switch (code) {
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
            printBold("[Keluar Dari Mode Admin]\n");
            sleep(1);
            return;
        }
    } while (code != 0);
}