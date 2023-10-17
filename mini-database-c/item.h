#define FITE_ITEM "database/db_item.csv"
#define COL_MAX 14
#define COL_MIN 6
FILE *inp, *outp;

void renderItem() {
    char *name;
    int ID, price, stock;
    char line[1000];
    inp = fopen(FITE_ITEM, "r");
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
    char name[100];
    int ID, price, stock;
    char line[1000];
    inp = fopen(FITE_ITEM, "r");
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
    scanf("%d", &price);
    printf("Stok : ");
    scanf("%d", &stock);

    name[strlen(name) - 1] = '\0';

    outp = fopen(FITE_ITEM, "a");
    fprintf(outp, "%d,%s,%d,%d\n", ID, name, price, stock);
    fclose(outp);
}