void generateReceiptFileName(char *fileName, char *date, char *time) {
    strcpy(fileName, "receipt/receipt_");
    strcat(fileName, date);
    strcat(fileName, "_");
    strcat(fileName, time);
    strcat(fileName, ".txt");

    char *ptr = fileName + 9;
    while (*ptr) {
        if (*ptr == '/' || *ptr == ':') {
            memmove(ptr, ptr + 1, strlen(ptr));
        } else {
            ptr++;
        }
    }
}

void showBill() {
    printBold("\nISI KERANJANG ANDA ");
    printf("(%d produk)\n", numCart);
    printBold("ID   |\t Nama Barang\t| Jmlh\t| Total Harga\n");
    printf("---------------------------------------------\n");
    int totalPrice = 0;
    for (int i = 0; i < numCart; i++) {
        totalPrice += cart[i].price * cart[i].amount;
        printf("%-5.d|\t %-14.14s\t| %d\t| ", cart[i].ID, cart[i].name, cart[i].amount);
        printMoney(cart[i].price * cart[i].amount);
        printf("\n");
    }
    printf("---------------------------------------------\n");
    printBold("\t\t\t  TOTAL\t: ");
    printMoney(totalPrice);
    printf("\n");
}

void saveReceipt() {
    FILE *outp;
    char FILE_RECEIPT[101];
    char *date = transaction[numTransaction - 1].transactionDate;
    char *time = transaction[numTransaction - 1].transactionTime;
    int transactionID = transaction[numTransaction - 1].ID;
    int totalPrice = transaction[numTransaction - 1].totalPrice;
    generateReceiptFileName(FILE_RECEIPT, date, time);

    outp = fopen(FILE_RECEIPT, "w");
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "================ ITS MIRT ===================\n");
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "Tanggal         : %s %s\n", date, time);
    fprintf(outp, "Nomor Transaksi : T");
    fprintf(outp, "%.5d\n", transactionID);
    fprintf(outp, "Nama Pelanggan  : %s", onlineUser.name);
    if (onlineUser.ID) {
        fprintf(outp, " (member)\n");
        fprintf(outp, "ID Member       : %d", onlineUser.ID);
    }
    fprintf(outp, "\n---------------------------------------------\n");
    fprintf(outp, "ID   |\t Nama Barang\t| Jmlh\t| Total Harga\n");
    fprintf(outp, "---------------------------------------------\n");
    for (int i = 0; i < numCart; i++) {
        fprintf(outp, "%-5.d|\t %-14.14s\t| %d\t| Rp%s\n", cart[i].ID, cart[i].name, cart[i].amount, strMoney(cart[i].price * cart[i].amount));
    }
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "\t\t\tTOTAL\t: Rp%s\n", strMoney(totalPrice));
    fclose(outp);
}

void showReceipt(int ID) {
    FILE *inp;
    char date[15], time[15];
    int isFound = 0;

    for (int i = 0; i < numTransaction; i++) {
        if (transaction[i].ID == ID) {
            strcpy(date, transaction[i].transactionDate);
            strcpy(time, transaction[i].transactionTime);
            isFound = 1;
            break;
        }
    }

    if (!isFound) {
        printf("ID Transaksi tidak ditemukan!\n");
        sleep(1);
        return;
    }

    char FILE_RECEIPT[101];
    generateReceiptFileName(FILE_RECEIPT, date, time);

    inp = fopen(FILE_RECEIPT, "r");
    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }
    char line[1000];
    while (fgets(line, sizeof(line), inp) != NULL) {
        printf("%s", line);
    }
    fclose(inp);
}
