char *userName[100];

void user() {
    clearScreen();
    printf("Masukkan Nama Anda\n");
    printf("Nama : ");
    scanf("%s", userName);
    printf("Selamat Datang %s!", userName);
    sleep(1);
    clearScreen();
    int code;
    do {
        printBold("Ingin melakukan apa?\n");
        puts("(0) Keluar");
        puts("(1) Lihat Barang");
        scanf("%d", &code);
        clearScreen();
        switch (code) {
        case 1:
            renderBarang();
            break;
        default:
            printBold("Selamat Berbelanja Kembali!\n");
            sleep(1);
            return;
        }
    } while (code != 0);
}