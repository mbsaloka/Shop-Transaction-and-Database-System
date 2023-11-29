void showTransactionLog(char *filter) {
    char dateTime[30], name[101];
    int transactionID, price, userID;
    numTempFilterTransaction = 0;

    printBold("CATATAN TRANSAKSI\n");
    printBold("ID   | Tanggal Transaksi   | Nama Pelanggan\t    | ID Member | Total Harga\n");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < numTransaction; i++) {
        strcpy(name, transaction[i].name);
        toLower(name);
        toLower(filter);

        if (strstr(name, filter)) {
            tempFilterTransaction[numTempFilterTransaction++] = transaction[i];
            printf("%-5.d| %s %s | %-22.22s | ", transaction[i].ID, transaction[i].transactionDate, transaction[i].transactionTime, transaction[i].name);
            (transaction[i].memberID == 0) ? printf("guest     | ") : printf("%-10.d| ", transaction[i].memberID);
            printMoney(transaction[i].totalPrice);
            printf("\n");
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
