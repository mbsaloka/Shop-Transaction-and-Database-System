void showTransactionLog(char *filter) {
    char dateTime[30], name[101];
    int transactionID, price, userID;
    numTempFilterTransaction = 0;

    printBold("CATATAN TRANSAKSI\n");
    printBold("ID   |\t Tanggal Transaksi\t| Nama Pelanggan\t| ID Member | Total Harga\n");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < numTransaction; i++) {
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
            tempFilterTransaction[numTempFilterTransaction++] = transaction[i];
            printf("%-5.d| %s %s | %-22.22s | ", transaction[i].ID, transaction[i].transactionDate, transaction[i].transactionTime, transaction[i].name);
            (transaction[i].memberID == 0) ? printf("guest     | ") : printf("%-10.d| ", transaction[i].memberID);
            printf("Rp%s\n", strMoney(transaction[i].totalPrice));
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
