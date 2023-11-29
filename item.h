void showItem(char* filter) {
    char name[101];
    numTempFilterItem = 0;

    printBold("DAFTAR BARANG\n");
    printBold("ID   |\t Nama Barang\t\t| Harga\t| Stok\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < numItem; i++) {
        strcpy(name, item[i].name);
        toLower(name);
        toLower(filter);
        if (strstr(name, filter)) {
            tempFilterItem[numTempFilterItem++] = item[i];
            printf("%-5.d|\t %-22.22s | %d\t| %d\n", item[i].ID, item[i].name, item[i].price, item[i].stock);
        }
    }
}

void updateItem(int ID) {
    int idx = 0;
    char name[101];
    int price, stock;
    for (int i = 0; i < numItem; i++) {
        if (item[i].ID == ID) {
            idx = i;
            break;
        }
    }

    int code;
    char* option[] = {
        "Perbarui Info Barang",
        "Hapus Barang",
        "Kembali",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    printf("Ingin melakukan apa?\n");
    code = chooseOption(option, lengthOption);
    switch (code) {
    case 0:
        printf("\033[2B");
        CLEAR_ROW(3);
        printBold("\nPERBARUI INFO BARANG (tekan tab untuk isi otomatis.)\n");
        printf("ID : %d\n", ID);
        printf("Nama Barang : \x1b[90m%s\x1b[0m\n", item[idx].name);
        printf("Harga : \x1b[90m%d\x1b[0m\n", item[idx].price);
        printf("Stok : \x1b[90m%d\x1b[0m\n", item[idx].stock);
        printf("\033[3A\r");
        printf("Nama Barang : ");
        if (getTabStr(name, item[idx].name) == -1) return;
        printf("Harga : ");
        if (getTabInt(&price, item[idx].price) == -1) return;
        printf("Stok : ");
        if (getTabInt(&stock, item[idx].stock) == -1) return;

        printf("Apakah Anda yakin ingin memperbarui barang %s? (Y/N) ", name);
        if (getYesNo() == 'Y') {
            clearScreen();
            item[idx].ID = ID;
            strcpy(item[idx].name, name);
            item[idx].price = price;
            item[idx].stock = stock;

            updateData(item, sizeof(Item), numItem, FILE_ITEM);

            printf("%s berhasil diperbarui.", name);
            sleep(1);
            clearScreen();
        } else {
            printf("Proses dibatalkan.");
            sleep(1);
            clearScreen();
        }
        break;
    case 1:
        clearScreen();
        printf("Apakah Anda yakin ingin menghapus barang %s? (Y/N) ", item[idx].name);
        if (getYesNo() == 'Y') {
            printf("%s berhasil dihapus.", item[idx].name);
            removeData(item, sizeof(Item), ID, &numItem, FILE_ITEM, getItemID);
            importFromDb(item, sizeof(Item), &numItem, FILE_ITEM);

            sleep(1);
            clearScreen();
        } else {
            printf("Proses dibatalkan.");
            sleep(1);
            clearScreen();
        }
        break;
    }
}

void inputItem() {
    int idx = numItem;
    char name[101];
    int ID, price, stock;

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';
    ID = (idx == 0) ? 1 : item[idx - 1].ID + 1;

    printBold("TAMBAHKAN BARANG BARU\n");
    printf("ID %s%d\n", nol, ID);
    printf("Nama Barang : ");
    getAllChar(name);
    if (strcmp(name, "ESCAPE") == 0) return;
    printf("Harga : ");
    price = getNumINT();
    if (price == -1) return;
    printf("Stok : ");
    stock = getNumINT();
    if (stock == -1) return;

    printf("Apakah Anda ingin menambahkan %s ke dalam daftar barang? (Y/N) ", name);
    if (getYesNo() == 'Y') {
        clearScreen();
        item[idx].ID = ID;
        strcpy(item[idx].name, name);
        item[idx].price = price;
        item[idx].stock = stock;

        addToDb(&item[idx], sizeof(Item), FILE_ITEM);
        numItem++;

        printf("%s berhasil ditambahkan.", name);
        sleep(1);
        clearScreen();
    } else {
        printf("Proses dibatalkan.");
        sleep(1);
        clearScreen();
    }
}