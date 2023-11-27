void showTransactionLog(char *filter) {
    int COL_MAX = 21;
    int COL_MIN = 14;
    char dateTime[30], name[101];
    int transactionID, price, userID;
    numTempFilterTransaction = 0;

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

        char name2[101];
        strcpy(name2, name);
        if (strlen(name) > COL_MAX) {
            name[COL_MAX - 2] = '.';
            name[COL_MAX - 1] = '.';
            name[COL_MAX] = '\0';
        }

        while (strlen(name) <= COL_MIN) {
            strcat(name, " ");
        }

        char space[] = "    ";
        space[3] = (transactionID < 10) ? ' ' : '\0';

        for (int i = 0; i < strlen(filter); i++) {
            if (filter[i] >= 'A' && filter[i] <= 'Z') {
                filter[i] += 32;
            }
        }
        for (int i = 0; i < strlen(name2); i++) {
            if (name2[i] >= 'A' && name2[i] <= 'Z') {
                name2[i] += 32;
            }
        }

        if (strstr(name2, filter)) {
            tempFilterTransaction[numTempFilterTransaction++] = transaction[i];
            printf("%d%s|\t %s\t| %s\t| ", transactionID, space, dateTime, name);
            if (userID == 0) {
                printf("guest     | Rp%s\n", strMoney(price));
            } else {
                printf("%d\t    | Rp%s\n", userID, strMoney(price));
            }
        }
    }
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
