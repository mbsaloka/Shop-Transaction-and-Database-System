static int saldo = 100000;

void addProduct() {
    int ID, price, stock;
    char *name;
    clearScreen();
    renderItem();
    printBold("Saldo : ");
    printMoney(saldo);
    printBold("\nMasukkan ID Barang yang ingin dibeli!\n");
    printf("ID : ");
    ID = getNumINT();

    inp = fopen(FILE_ITEM, "r");
    char line[1000];
    int checkID = 1, isFound = 0, amount = 0;
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        checkID = atoi(strtok(line, ","));
        if (ID == checkID) {
            name = strtok(NULL, ",");
            price = atoi(strtok(NULL, ","));
            stock = atoi(strtok(NULL, ","));
            isFound = 1;
            if (stock <= 0) {
                printf("\nStok produk yang Anda pilih sedang kosong.");
                sleep(1);
                return;
            }
            break;
        }
    }
    fclose(inp);
    if (!isFound) {
        printf("\nID %d tidak ada di dalam daftar.", ID);
        sleep(1);
        return;
    }

    printBold("\n\nDetail Produk\n");
    printf("Nama : %s\n", name);
    printf("Harga : ");
    printMoney(price);
    printf("\nStok : %d\n", stock);

    printBold("\nMasukkan jumlah yang ingin dibeli!\n");
    while (1) {
        printf("Jumlah : ");
        amount = getNumINT();
        if (amount > stock) {
            printf("\nJumlah yang dipilih tidak boleh melebihi stok produk.\n");
            printf("Tolong masukkan kembali jumlah yang sesuai.\n");
            sleep(2);
        } else if (amount == 0) {
            printf("\nJumlah yang dipilih tidak boleh sama dengan 0.\n");
            printf("Tolong masukkan kembali jumlah yang sesuai.\n");
            sleep(2);
        } else {
            printf("\nProduk %s sejumlah %d berhasil ditambahkan ke keranjang.\n", name, amount);
            sleep(2);
            break;
        }
        for (int i = 0; i < 3; i++) clearRow();
    }
}

void shoppingMenu() {
    int code;
    char exitCode;
    do {
        clearScreen();
        renderItem();
        printBold("Saldo : ");
        printMoney(saldo);
        printBold("Ingin melakukan apa?\n");
        puts("(0) Kembali ke Menu Utama");
        puts("(1) Pilih Produk");
        puts("(2) Lihat Keranjang");
        code = getNumINT();
        clearScreen();
        switch (code) {
        case 0:
            printf("Jika keluar maka keranjang akan dikosongkan.\nYakin ingin keluar? (Y/N) ");
            exitCode = getYesNo();
            if (exitCode == 'Y') {
                clearScreen();
                return;
            } else {
                code = -1;
            }
            break;
        case 1:
            addProduct();
            break;
        case 2:
            comingSoon();
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}