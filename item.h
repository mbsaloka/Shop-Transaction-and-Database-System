void showItem(char *filter) {
    int COL_MAX = 21;
    int COL_MIN = 14;
    char name[101];
    int ID, price, stock;

    printBold("DAFTAR BARANG\n");
    printBold("ID   |\t Nama Barang\t\t| Harga\t| Stok\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < numItem; i++) {
        ID = item[i].ID;
        strcpy(name, item[i].name);
        price = item[i].price;
        stock = item[i].stock;

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

        for (int j = 0; j < strlen(filter); j++) {
            if (filter[j] >= 'A' && filter[j] <= 'Z') {
                filter[j] += 32;
            }
        }
        for (int j = 0; j < strlen(name); j++) {
            if (name[j] >= 'A' && name[j] <= 'Z') {
                name[j] += 32;
            }
        }

        if (strstr(name, filter)) {
            printf("%d%s|\t %s\t| %d\t| %d\n", ID, space, name2, price, stock);
        }
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
    fflush(stdin);
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