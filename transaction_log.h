void showLog() {
    int COL_MAX = 21;
    int COL_MIN = 14;
    char dateTime[30], name[101];
    int transactionID, price, userID;

    printBold("CATATAN TRANSAKSI\n");
    printBold("ID   |\t Tanggal Transaksi\t| Nama Pelanggan\t| ID Member | Total Harga\n");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < numTransaction; i++) {
        transactionID = transaction[i].ID;
        strcpy(name, transaction[i].name);
        userID = transaction[i].memberID;
        price = transaction[i].totalPrice;
        char dateTime[101];
        strcpy(dateTime, transaction[i].transactionDate);
        strcat(dateTime, " ");
        strcat(dateTime, transaction[i].transactionTime);

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

void addTransactionLog(int totalPrice) {
    int idx = numTransaction;
    int transactionID = (idx == 0) ? 1 : transaction[idx - 1].ID + 1;
    transaction[idx].ID = transactionID;
    transaction[idx].memberID = onlineUser.ID;
    transaction[idx].totalPrice = totalPrice;
    strcpy(transaction[idx].name, onlineUser.name);
    strcpy(transaction[idx].transactionDate, getDate());
    strcpy(transaction[idx].transactionTime, getTime());

    addToDb(&transaction[idx], sizeof(Transaction), FILE_TRANSACTION);
    numTransaction++;
}
