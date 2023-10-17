#define FILE_ITEM "database/db_item.csv"
FILE *inp, *outp;

void renderItem() {
    int COL_MAX = 14;
    int COL_MIN = 6;
    char *name;
    int ID, price, stock;
    char line[1000];
    inp = fopen(FILE_ITEM, "r");
    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DAFTAR BARANG\n");
    printBold("ID   |\t Nama Barang\t| Harga\t| Stok\n");
    printf("---------------------------------------\n");
    fgets(line, sizeof(line), inp);
    const char *delimiter = ",";
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        name = strtok(NULL, delimiter);
        price = atoi(strtok(NULL, delimiter));
        stock = atoi(strtok(NULL, delimiter));

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

        printf("%d%s|\t %s\t| %d\t| %d\n", ID, space, name, price, stock);
    }

    fclose(inp);
}

void inputItem() {
    char name[100], *temp, exitCode;
    int ID, price, stock;
    char line[1000];
    inp = fopen(FILE_ITEM, "r");
    while (fgets(line, sizeof(line), inp)) {
        ID = atoi(strtok(line, ",")) + 1;
    }
    fclose(inp);

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';

    printBold("TAMBAHKAN BARANG BARU\n");
    printf("ID %s%d\n", nol, ID);
    fflush(stdin);
    printf("Nama Barang : ");
    fgets(name, 100, stdin);
    printf("Harga : ");
    price = getNumINT();
    printf("\nStok : ");
    stock = getNumINT();

    name[strlen(name) - 1] = '\0';

    printf("\nApakah Anda ingin menambahkan %s ke dalam daftar barang? (Y/N) ", name);
    exitCode = getYesNo();
    clearScreen();
    if (exitCode == 'Y') {
        outp = fopen(FILE_ITEM, "a");
        fprintf(outp, "%d,%s,%d,%d\n", ID, name, price, stock);
        fclose(outp);
        printf("%s berhasil ditambahkan.", name);
        sleep(1);
        clearScreen();
    } else {
        printf("Proses dibatalkan.");
        sleep(1);
        clearScreen();
    }
}