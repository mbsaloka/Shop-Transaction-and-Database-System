
struct Cart {
    int ID, price, amount, stock;
    char name[100];
};

static struct Cart item[100];
static int balance, itemIndex, transactionID, userID;
static char userName[101];

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

void updateUserBalance(int ID) {
    char *temp;
    int tempID;
    char line[1000];
    inp = fopen(FILE_MEMBER, "r");
    outp = fopen("database/temp_member.csv", "w");
    fgets(line, sizeof(line), inp);
    fprintf(outp, line);
    while (fgets(line, sizeof(line), inp) != NULL) {
        tempID = atoi(strtok(line, ","));
        fprintf(outp, "%d", tempID);
        for (int i = 0; i < 7; i++) {
            temp = strtok(NULL, ",");
            fprintf(outp, ",%s", temp);
        }
        if (tempID == userID) {
            fprintf(outp, ",%d\n", balance);
        } else {
            temp = strtok(NULL, ",");
            fprintf(outp, ",%s", temp);
        }
    }
    fclose(inp);
    fclose(outp);

    inp = fopen("database/temp_member.csv", "r");
    outp = fopen(FILE_MEMBER, "w");
    while (fgets(line, sizeof(line), inp) != NULL) {
        fprintf(outp, line);
    }
    fclose(inp);
    fclose(outp);

    remove("database/temp_member.csv");
}

void addItemToCart() {
    int ID, price, stock;
    char *name;
    clearScreen();
    showItem(1);
    printBold("Saldo : ");
    printMoney(balance);
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

        printf("%d%s|\t %s\t| %d\t| ", ID, space, name, amount);
        printMoney(price);
        printf("\n");
    }
    printf("---------------------------------------------\n");
    printBold("\t\t\t  TOTAL\t: ");
    printMoney(finalPrice);
    printf("\n");
    return finalPrice;
}

void addBill() {
    FILE *inp, *outp;
    char FILE_BILL[100];
    char *date = getDate();
    char *time = getTime();
    strcpy(FILE_BILL, "bill/bill_");
    strcat(FILE_BILL, date);
    strcat(FILE_BILL, "_");
    strcat(FILE_BILL, time);
    strcat(FILE_BILL, ".txt");

    char *ptr = FILE_BILL + 6;
    while (*ptr) {
        if (*ptr == '/' || *ptr == ':') {
            memmove(ptr, ptr + 1, strlen(ptr));
        } else {
            ptr++;
        }
    }

    outp = fopen(FILE_BILL, "w");
    int length = 1;
    for (int i = 1; i <= transactionID; i *= 10) length++;

    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "================ ITS MIRT ===================\n");
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "Tanggal         : %s %s\n", date, time);
    fprintf(outp, "Nomor Transaksi : T");
    for (int i = 0; i < 5 - length; i++) fprintf(outp, "0");
    fprintf(outp, "%d\n", transactionID);
    fprintf(outp, "Nama Pelanggan  : %s", userName);
    if (userID) {
        fprintf(outp, " (member)\n");
        fprintf(outp, "ID Member       : %d", userID);
    }
    fprintf(outp, "\n");
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "ID   |\t Nama Barang\t| Jmlh\t| Total Harga\n");
    fprintf(outp, "---------------------------------------------\n");
    int finalPrice = 0;
    for (int i = 0; i < itemIndex; i++) {
        int COL_MAX = 14;
        int COL_MIN = 11;
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

        fprintf(outp, "%d%s|\t %s\t| %d \t| Rp%s\n", ID, space, name, amount, strMoney(price));
    }
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "\t\t\tTOTAL\t: Rp%s\n", strMoney(finalPrice));
    fclose(outp);
}

void addTransactionLog(int finalPrice) {
    char *date = getDate();
    char *time = getTime();
    char *name = userName;
    int ID = userID;
    transactionID = 0;

    inp = fopen(FILE_TRANSACTION, "r");
    char line[1000];
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        transactionID = atoi(strtok(line, ","));
    }
    transactionID++;
    fclose(inp);

    outp = fopen(FILE_TRANSACTION, "a");
    fprintf(outp, "%d,%s %s,%s,%d,%d\n", transactionID, date, time, name, ID, finalPrice);
    fclose(outp);
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
        printMoney(balance);
        int finalPrice = showBill();
        printBold("\nIngin melakukan apa?\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            break;
        case 1:
            printBold("Saldo : ");
            printMoney(balance);
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
            } else if (balance < finalPrice) {
                printf("Saldo kurang! Hapus beberapa barang dari keranjang.\n");
                sleep(1);
            } else {
                balance -= finalPrice;
                addTransactionLog(finalPrice);
                addBill();
                updateDBItem();
                updateUserBalance(userID);
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

int getUserBalance(int ID) {
    char *temp;
    int tempID;
    char line[1000];
    inp = fopen(FILE_MEMBER, "r");
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        tempID = atoi(strtok(line, ","));
        if (tempID == userID) {
            for (int i = 0; i < 7; i++) temp = strtok(NULL, ",");
            return atoi(strtok(NULL, ","));
        }
    }
    printMoney(balance);
    printf("\n");
    fclose(inp);

    return 0;
}

void shoppingMenu(char name[101], int ID) {
    strcpy(userName, name);
    userID = ID;
    balance = (userID > 0) ? getUserBalance(ID) : 100000;

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
        "(2) Lihat Keranjang (Bayar)",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        showItem(1);
        printBold("Saldo : ");
        printMoney(balance);
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