static int saldo = 100000;

struct Cart {
    int ID, price, amount, stock;
    char name[100];
};

static struct Cart item[100];
static int itemIndex;

void createTempShoppingFile() {
    FILE *inp, *outp;
    char ch;

    inp = fopen(FILE_ITEM, "r");
    outp = fopen(FILE_TEMP_SHOPPING, "w");

    char line[1001];
    char *name;
    int ID, price, stock;
    const char *delimiter = ",";
    fgets(line, sizeof(line), inp);
    fprintf(outp, line);
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        name = strtok(NULL, delimiter);
        price = atoi(strtok(NULL, delimiter));
        stock = atoi(strtok(NULL, delimiter));

        for (int i = 0; i < itemIndex; i++) {
            if (ID == item[i].ID) {
                stock = item[i].stock;
            }
        }
        fprintf(outp, "%d,%s,%d,%d\n", ID, name, price, stock);
    }

    fclose(inp);
    fclose(outp);
}

void updateDBItem() {
    FILE *inp, *outp;
    char ch;

    inp = fopen(FILE_TEMP_SHOPPING, "r");
    outp = fopen(FILE_ITEM, "w");

    char line[1001];
    char *name;
    int ID, price, stock;
    const char *delimiter = ",";
    fgets(line, sizeof(line), inp);
    fprintf(outp, line);
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        name = strtok(NULL, delimiter);
        price = atoi(strtok(NULL, delimiter));
        stock = atoi(strtok(NULL, delimiter));

        for (int i = 0; i < itemIndex; i++) {
            if (ID == item[i].ID) {
                stock = item[i].stock;
            }
        }
        fprintf(outp, "%d,%s,%d,%d\n", ID, name, price, stock);
    }

    fclose(inp);
    fclose(outp);
}

void addItemToCart() {
    int ID, price, stock;
    char *name;
    clearScreen();
    showItem(1);
    printBold("Saldo : ");
    printMoney(saldo);
    printBold("\nMasukkan ID Barang yang ingin dibeli!\n");
    printf("ID : ");
    ID = getNumINT();
    if (ID == -1) return;

    inp = fopen(FILE_TEMP_SHOPPING, "r");
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
                printf("Stok produk yang Anda pilih sedang kosong.");
                sleep(1);
                return;
            }
            break;
        }
    }
    fclose(inp);
    if (!isFound) {
        printf("ID %d tidak ada di dalam daftar.", ID);
        sleep(1);
        return;
    }

    printBold("\nDetail Produk\n");
    printf("Nama : %s\n", name);
    printf("Harga : ");
    printMoney(price);
    printf("\nStok : %d\n", stock);

    printBold("\nMasukkan jumlah yang ingin dibeli!\n");
    while (1) {
        printf("Jumlah : ");
        amount = getNumINT();
        if (amount == -1) return;
        if (amount > stock) {
            printf("Jumlah yang dipilih tidak boleh melebihi stok produk.\n");
            printf("Tolong masukkan kembali jumlah yang sesuai.\n");
            sleep(1);
        } else if (amount == 0) {
            printf("Jumlah yang dipilih tidak boleh sama dengan 0.\n");
            printf("Tolong masukkan kembali jumlah yang sesuai.\n");
            sleep(1);
        } else {
            int isListed = 0;
            for (int i = 0; i < itemIndex; i++) {
                if (ID == item[i].ID) {
                    item[i].amount += amount;
                    item[i].stock -= amount;
                    isListed = 1;
                }
            }
            if (!isListed) {
                item[itemIndex].ID = ID;
                item[itemIndex].price = price;
                item[itemIndex].amount = amount;
                item[itemIndex].stock = stock - amount;
                strcpy(item[itemIndex].name, name);
                itemIndex++;
            }
            createTempShoppingFile();
            printf("\nProduk %s sejumlah %d berhasil ditambahkan ke keranjang.\n", name, amount);
            sleep(1);
            break;
        }
        for (int i = 0; i < 3; i++) clearRow();
    }
}

int showBill() {
    printBold("\nISI KERANJANG ANDA ");
    printf("(%d produk)\n", itemIndex);
    printBold("ID   |\t Nama Barang\t| Jmlh\t| Total Harga\n");
    printf("---------------------------------------------\n");
    int finalPrice = 0;
    for (int i = 0; i < itemIndex; i++) {
        int COL_MAX = 14;
        int COL_MIN = 6;
        char name[100];
        int ID, price, amount;

        strcpy(name, item[i].name);
        ID = item[i].ID;
        amount = item[i].amount;
        price = item[i].price * amount;
        finalPrice += price;

        if (strlen(name) > COL_MAX) {
            name[COL_MAX - 2] = '.';
            name[COL_MAX - 1] = '.';
            name[COL_MAX] = '\0';
        }

        if (strlen(name) < COL_MIN) {
            strcat(name, "    ");
        }

        char space[] = "    ";
        space[3] = (ID < 10) ? ' ' : '\0';

        printf("%d%s|\t %s\t| %d\t| ", ID, space, name, amount, price);
        printMoney(price);
        printf("\n");
    }
    printf("---------------------------------------------\n");
    printBold("\t\t\t  TOTAL\t: ");
    printMoney(finalPrice);
    printf("\n");
    return finalPrice;
}

void openCart() {
    int code;
    char exitCode;
    char *option[] = {
        "(0) Kembali ke Menu Belanja",
        "(1) Hapus Produk",
        "(2) Ubah Jumlah Produk",
        "(3) Selesai & Bayar",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printBold("Saldo : ");
        printMoney(saldo);
        int finalPrice = showBill();
        printBold("\nIngin melakukan apa?\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            break;
        case 1:
            printBold("Saldo : ");
            printMoney(saldo);
            showBill();
            printBold("\nMasukkan ID Barang yang ingin dihapus!\n");
            printf("ID : ");
            int ID = getNumINT();
            if (ID == -1) break;
            int isRemoved = 0;
            for (int i = 0; i < itemIndex; i++) {
                if (ID == item[i].ID) {
                    item[i].stock += item[i].amount;
                    createTempShoppingFile();
                    isRemoved = 1;
                    itemIndex--;
                }
                if (isRemoved) {
                    item[i] = item[i + 1];
                }
            }
            break;
        case 2:
            comingSoon();
            break;
        case 3:
            if (itemIndex == 0) {
                printf("Keranjang Anda kosong.\n");
                sleep(1);
            } else if (saldo < finalPrice) {
                printf("Saldo kurang! Hapus beberapa barang dari keranjang.\n");
                sleep(1);
            } else {
                saldo -= finalPrice;
                updateDBItem();
                itemIndex = 0;
                printf("Transaksi Sukses!\n");
                sleep(1);
                return;
            }
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}

void shoppingMenu() {
    struct Cart item[100];
    int itemIndex = 0;
    createTempShoppingFile();
    for (int i = 0; i < 100; i++) {
        item[i].ID = 0;
    }
    int code;
    char exitCode;
    char *option[] = {
        "(0) Kembali ke Menu Utama",
        "(1) Pilih Produk",
        "(2) Lihat Keranjang (Checkout)",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        showItem(1);
        printBold("Saldo : ");
        printMoney(saldo);
        printBold("\nIngin melakukan apa?\n");

        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            printf("Jika keluar maka keranjang akan dikosongkan.\nYakin ingin keluar? (Y/N) ");
            exitCode = getYesNo();
            if (exitCode == 'Y') {
                clearScreen();
                remove(FILE_TEMP_SHOPPING);
                return;
            } else {
                code = -1;
            }
            break;
        case 1:
            addItemToCart();
            break;
        case 2:
            openCart();
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}