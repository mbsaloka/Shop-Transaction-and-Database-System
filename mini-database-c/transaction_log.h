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
