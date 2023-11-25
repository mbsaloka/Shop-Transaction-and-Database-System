void showBill() {
    printBold("\nISI KERANJANG ANDA ");
    printf("(%d produk)\n", numCart);
    printBold("ID   |\t Nama Barang\t| Jmlh\t| Total Harga\n");
    printf("---------------------------------------------\n");
    int totalPrice = 0;
    for (int i = 0; i < numCart; i++) {
        int COL_MAX = 14;
        int COL_MIN = 6;
        char name[101];
        int ID, price, amount;

        strcpy(name, cart[i].name);
        ID = cart[i].ID;
        amount = cart[i].amount;
        price = cart[i].price * amount;
        totalPrice += price;

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
    strcpy(FILE_RECEIPT, "receipt/receipt_");
    strcat(FILE_RECEIPT, date);
    strcat(FILE_RECEIPT, "_");
    strcat(FILE_RECEIPT, time);
    strcat(FILE_RECEIPT, ".txt");

    char *ptr = FILE_RECEIPT + 9;
    while (*ptr) {
        if (*ptr == '/' || *ptr == ':') {
            memmove(ptr, ptr + 1, strlen(ptr));
        } else {
            ptr++;
        }
    }

    outp = fopen(FILE_RECEIPT, "w");
    int zeroLength = 1;
    for (int i = 1; i <= transactionID; i *= 10) zeroLength++;
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "================ ITS MIRT ===================\n");
    fprintf(outp, "---------------------------------------------\n");
    fprintf(outp, "Tanggal         : %s %s\n", date, time);
    fprintf(outp, "Nomor Transaksi : T");
    for (int i = 0; i < 5 - zeroLength; i++) fprintf(outp, "0");
    fprintf(outp, "%d\n", transactionID);
    fprintf(outp, "Nama Pelanggan  : %s", onlineUser.name);
    if (onlineUser.ID) {
        fprintf(outp, " (member)\n");
        fprintf(outp, "ID Member       : %d", onlineUser.ID);
    }
    fprintf(outp, "\n---------------------------------------------\n");
    fprintf(outp, "ID   |\t Nama Barang\t| Jmlh\t| Total Harga\n");
    fprintf(outp, "---------------------------------------------\n");
    for (int i = 0; i < numCart; i++) {
        int COL_MAX = 14;
        int COL_MIN = 11;
        char name[101];
        int ID, price, amount;

        ID = cart[i].ID;
        strcpy(name, cart[i].name);
        amount = cart[i].amount;
        price = cart[i].price * amount;

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
    strcpy(FILE_RECEIPT, "receipt/receipt_");
    strcat(FILE_RECEIPT, date);
    strcat(FILE_RECEIPT, "_");
    strcat(FILE_RECEIPT, time);
    strcat(FILE_RECEIPT, ".txt");

    char *ptr = FILE_RECEIPT + 9;
    while (*ptr) {
        if (*ptr == '/' || *ptr == ':') {
            memmove(ptr, ptr + 1, strlen(ptr));
        } else {
            ptr++;
        }
    }

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
