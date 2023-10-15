static char *guestName[100];
static int flagMember = 0;

void user() {
    clearScreen();
    char username[100], pass[100], exitCode[10];
    printBold("Apakah Anda sudah berlangganan Membership? (Y/N) \n");
    scanf("%s", exitCode);
    if (strcmp(exitCode, "Y") == 0 || strcmp(exitCode, "y") == 0) flagMember = 1;

    if (flagMember) {
    }

    printBold("Masukkan nama Anda\n");
    printf("Nama : ");
    scanf("%s", guestName);
    printf("Selamat Datang %s!", guestName);
    sleep(1);
    clearScreen();
    int code;
    do {
        printBold("Ingin melakukan apa?\n");
        puts("(0) Keluar");
        puts("(1) Mulai Belanja");
        puts("(2) Daftar Membership");
        scanf("%d", &code);
        clearScreen();
        switch (code) {
        case 1:
            renderItem();
            break;
        case 2:
            inputMember();
            break;
        default:
            printBold("Selamat Berbelanja Kembali!\n");
            sleep(1);
            return;
        }
    } while (code != 0);
}