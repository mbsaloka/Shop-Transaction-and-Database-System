#define FILE_ITEM "database/db_item.csv"
#define FILE_TEMP_SHOPPING "database/temp_shopping.csv"
#define FILE_TRANSACTION "database/db_transaction_log.csv"
FILE *inp, *outp;

void showLog() {
    int COL_MAX = 21;
    int COL_MIN = 14;
    char *dateTime, *name;
    int transactionID, price, userID;

    char line[1001];
    inp = fopen(FILE_TRANSACTION, "r");
    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("CATATAN TRANSAKSI\n");
    printBold("ID   |\t Tanggal Transaksi\t| Nama Pelanggan\t| ID Member | Total Harga\n");
    printf("---------------------------------------------------------------------------------\n");
    fgets(line, sizeof(line), inp);
    const char *delimiter = ",";
    while (fgets(line, sizeof(line), inp) != NULL) {
        transactionID = atoi(strtok(line, delimiter));
        dateTime = strtok(NULL, delimiter);
        name = strtok(NULL, delimiter);
        userID = atoi(strtok(NULL, delimiter));
        price = atoi(strtok(NULL, delimiter));

        if (strlen(name) > COL_MAX) {
            name[COL_MAX - 2] = '.';
            name[COL_MAX - 1] = '.';
            name[COL_MAX] = '\0';
        }
        if (strlen(name) < COL_MIN) {
            strcat(name, "          ");
        }
        char space[] = "    ";
        space[3] = (transactionID < 10) ? ' ' : '\0';
        printf("%d%s|\t %s\t| %s\t| ", transactionID, space, dateTime, name);
        if (userID == 0) {
            printf("guest     | Rp%s\n", strMoney(price));
        } else {
            printf("%d\t    | Rp%s\n", userID, strMoney(price));
        }
    }
    fclose(inp);
}

void showReceipt(int ID) {
    char *date, *time, *name;
    int transactionID, price, userID;

    char line[1001];
    inp = fopen(FILE_TRANSACTION, "r");
    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }
    fgets(line, sizeof(line), inp);
    const char *delimiter = ",";
    while (fgets(line, sizeof(line), inp) != NULL) {
        transactionID = atoi(strtok(line, delimiter));
        date = strtok(NULL, " ");
        time = strtok(NULL, delimiter);
        name = strtok(NULL, delimiter);
        userID = atoi(strtok(NULL, delimiter));
        price = atoi(strtok(NULL, delimiter));
        if (transactionID == ID) {
            break;
        } else {
            transactionID = -1;
        }
    }
    fclose(inp);

    if (transactionID == -1) {
        printf("ID Transaksi tidak ditemukan!\n");
        sleep(1);
        return;
    }

    char FILE_BILL[100];
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

    inp = fopen(FILE_BILL, "r");
    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }
    while (fgets(line, sizeof(line), inp) != NULL) {
        printf("%s", line);
    }
    fclose(inp);
}

void showTransactionLog() {
    int code;
    char exitCode;
    char *option[] = {
        "(0) Kembali ke Menu Admin",
        "(1) Tampilkan Struk",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();

        showLog();
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            return;
        case 1:
            showLog();
            printf("Masukkan ID Transaksi : ");
            int transactionID;
            transactionID = getNumINT();
            if (transactionID == -1) {
                break;
            }
            clearScreen();
            showReceipt(transactionID);
            printf("Tekan Enter untuk kembali.");
            char escapeCode = getEnter();
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}

void showItem(int param, char *filter) {
    char fileName[101];
    if (param == 0) {
        strcpy(fileName, FILE_ITEM);
    } else if (param == 1) {
        strcpy(fileName, FILE_TEMP_SHOPPING);
    }
    int COL_MAX = 21;
    int COL_MIN = 14;
    char *name;
    int ID, price, stock;
    char line[1001];
    inp = fopen(fileName, "r");
    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DAFTAR BARANG\n");
    printBold("ID   |\t Nama Barang\t\t| Harga\t| Stok\n");
    printf("---------------------------------------\n");
    fgets(line, sizeof(line), inp);
    const char *delimiter = ",";
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        name = strtok(NULL, delimiter);
        price = atoi(strtok(NULL, delimiter));
        stock = atoi(strtok(NULL, delimiter));

        char name2[101];
        strcpy(name2, name);
        if (strlen(name) > COL_MAX) {
            name2[COL_MAX - 2] = '.';
            name2[COL_MAX - 1] = '.';
            name2[COL_MAX] = '\0';
        }

        while (strlen(name2) <= COL_MIN) {
            strcat(name2, " ");
        }

        char space[] = "    ";
        space[3] = (ID < 10) ? ' ' : '\0';

        for (int i = 0; i < strlen(filter); i++) {
            if (filter[i] >= 'A' && filter[i] <= 'Z') {
                filter[i] += 32;
            }
        }
        for (int i = 0; i < strlen(name); i++) {
            if (name[i] >= 'A' && name[i] <= 'Z') {
                name[i] += 32;
            }
        }

        if (strstr(name, filter)) {
            printf("%d%s|\t %s\t| %d\t| %d\n", ID, space, name2, price, stock);
        }
    }

    fclose(inp);
}

void inputItem() {
    char *name, exitCode;
    int ID, price, stock;
    char line[1001];
    inp = fopen(FILE_ITEM, "r");
    while (fgets(line, sizeof(line), inp)) {
        ID = atoi(strtok(line, ",")) + 1;
    }
    fclose(inp);

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';

    printBold("TAMBAHKAN BARANG BARU\n");
    printf("ID %s%d\n", nol, ID);
    fflush(stdin);
    printf("Nama Barang : ");
    name = getAllChar();
    if (strcmp(name, "ESCAPE") == 0) return;
    // fgets(name, 101, stdin);
    // name[strlen(name) - 1] = '\0';
    printf("Harga : ");
    price = getNumINT();
    if (price == -1) {
        free(name);
        return;
    }
    printf("Stok : ");
    stock = getNumINT();
    if (stock == -1) {
        free(name);
        return;
    }

    printf("Apakah Anda ingin menambahkan %s ke dalam daftar barang? (Y/N) ", name);
    exitCode = getYesNo();
    clearScreen();
    if (exitCode == 'Y') {
        outp = fopen(FILE_ITEM, "a");
        fprintf(outp, "%d,%s,%d,%d\n", ID, name, price, stock);
        fclose(outp);
        printf("%s berhasil ditambahkan.", name);
        sleep(1);
        clearScreen();
    } else {
        printf("Proses dibatalkan.");
        sleep(1);
        clearScreen();
    }
    free(name);
}