void showItem(char* filter) {
    char name[101];
    numFilterItem = 0;
    while (filterItem != NULL) {
        Item* temp = filterItem;
        filterItem = filterItem->next;
        free(temp);
    }

    printBold("DAFTAR BARANG\n");
    printBold("ID   |\t Nama Barang\t\t| Stok\t| Harga\n");
    printf("---------------------------------------------------\n");
    Item *curItem = item, *lastFilterItem = NULL;
    while (curItem != NULL) {
        strcpy(name, curItem->name);
        toLower(name);
        toLower(filter);
        if (strstr(name, filter)) {
            numFilterItem++;
            Item* newFilterItem = (Item*)malloc(sizeof(Item));
            newFilterItem = curItem;
            if (filterItem == NULL) {
                filterItem = newFilterItem;
                filterItem->next = NULL;
                filterItem->prev = NULL;
                lastFilterItem = filterItem;
            } else {
                lastFilterItem->next = newFilterItem;
                newFilterItem->next = NULL;
                newFilterItem->prev = lastFilterItem;
                lastFilterItem = newFilterItem;
            }
            printf("%-5.d|\t %-22.22s | %-5.d | ", curItem->ID, curItem->name, curItem->stock);
            printMoney(curItem->price);
            printf("\n");
        }
        curItem = curItem->next;
    }
}

Item* searchItemByID(int ID) {
    Item* cur = item;
    while (cur != NULL) {
        if (cur->ID == ID) return cur;
        cur = cur->next;
    }
    return NULL;
}

void updateItem(int ID) {
    Item* curItem = searchItemByID(ID);
    char name[101];
    int price, stock;

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
        CURSOR_DOWN(2);
        CLEAR_ROW(3);
        printBold("\nPERBARUI INFO BARANG (tekan tab untuk isi otomatis.)\n");
        printf("ID : %d\n", ID);
        printf("Nama Barang : %s%s%s\n", GRAY, curItem->name, NO_EFFECT);
        printf("Stok : %s%d%s\n", GRAY, curItem->stock, NO_EFFECT);
        printf("Harga : %s%d%s\n", GRAY, curItem->price, NO_EFFECT);
        CURSOR_UP(3);
        printf("Nama Barang : ");
        if (getTabStr(name, curItem->name) == -1) return;
        printf("Stok : ");
        if (getTabInt(&stock, curItem->stock) == -1) return;
        stock = MIN(99999, stock);
        printf("Harga : ");
        if (getTabInt(&price, curItem->price) == -1) return;

        printf("Apakah Anda yakin ingin memperbarui barang %s? (Y/N) ", name);
        if (getYesNo() == 'Y') {
            clearScreen();
            curItem->ID = ID;
            strcpy(curItem->name, name);
            curItem->price = price;
            curItem->stock = stock;
            updateData(item, sizeof(Item), FILE_ITEM, getItemNext);

            printf("%s berhasil diperbarui.", name);
            sleep(1);
        } else {
            printf("\nProses dibatalkan.");
            sleep(1);
            clearScreen();
        }
        break;
    case 1:
        clearScreen();
        printf("Apakah Anda yakin ingin menghapus barang %s? (Y/N) ", curItem->name);
        if (getYesNo() == 'Y') {
            printf("%s berhasil dihapus.", curItem->name);
            // lastItem->next = curItem->next;
            curItem->prev->next = curItem->next;
            if (curItem->next != NULL) {
                curItem->next->prev = curItem->prev;
            }
            updateData(item, sizeof(Item), FILE_ITEM, getItemNext);
            numItem--;
            free(curItem);

            sleep(1);
            clearScreen();
        } else {
            printf("\nProses dibatalkan.");
            sleep(1);
            clearScreen();
        }
        break;
    }
}

void inputItem() {
    char name[101] = "\0";
    int ID, price, stock;
    Item *curItem = item, *lastItem = NULL;

    if (curItem == NULL) {
        ID = 1;
    } else {
        while (curItem != NULL) {
            ID = curItem->ID;
            lastItem = curItem;
            curItem = curItem->next;
        }
        ID++;
    }

    printBold("TAMBAHKAN BARANG BARU\n");
    printf("ID %-.3d\n", ID);
    printf("Nama Barang : ");
    getAllChar(name);
    if (strcmp(name, "ESCAPE") == 0) return;
    printf("Stok : ");
    stock = getNumINT();
    stock = MIN(99999, stock);
    if (stock == -1) return;
    printf("Harga : ");
    price = getNumINT();
    if (price == -1) return;

    printf("Apakah Anda ingin menambahkan %s ke dalam daftar barang? (Y/N) ", name);
    if (getYesNo() == 'Y') {
        clearScreen();

        Item* newItem = (Item*)malloc(sizeof(Item));
        newItem->ID = ID;
        strcpy(newItem->name, name);
        newItem->stock = stock;
        newItem->price = price;
        newItem->next = NULL;
        newItem->prev = lastItem;

        if (item == NULL) {
            item = newItem;
        } else {
            lastItem->next = newItem;
        }

        // addToDb(newItem, sizeof(Item), FILE_ITEM);
        numItem++;
        updateData(item, sizeof(Item), FILE_ITEM, getItemNext);

        printf("%s berhasil ditambahkan.", name);
        sleep(1);
        clearScreen();
    } else {
        clearScreen();
        printf("Proses dibatalkan.");
        sleep(1);
        clearScreen();
    }
}