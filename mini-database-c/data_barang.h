#define FILE_NAME "database/db_barang.csv"
FILE *inp, *outp;

void renderBarang() {
    inp = fopen(FILE_NAME, "r");

    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DAFTAR BARANG\n");

    char line[1000];
    char *namaBarang;
    int ID, harga, stok;
    const char *delimiter = ",";

    printBold("ID   |\t Nama Barang\t| Harga\t| Stok\n");
    printf("---------------------------------------\n");
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        namaBarang = strtok(NULL, delimiter);
        harga = atoi(strtok(NULL, delimiter));
        stok = atoi(strtok(NULL, delimiter));

        char space[] = "    ";
        space[3] = (ID < 10) ? ' ' : '\0';

        printf("%d%s|\t %s\t| %d\t| %d\n", ID, space, namaBarang, harga, stok);
    }

    fclose(inp);
}

void inputBarang() {
    char namaBarang[100];
    int ID, harga, stok;

    inp = fopen(FILE_NAME, "r");
    char line[1000];
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
    fgets(namaBarang, 100, stdin);
    printf("Harga : ");
    scanf("%d", &harga);
    printf("Stok : ");
    scanf("%d", &stok);

    if (namaBarang[strlen(namaBarang) - 1] == '\n') {
        namaBarang[strlen(namaBarang) - 1] = '\0';
    }

    outp = fopen(FILE_NAME, "a");
    fprintf(outp, "%d,%s,%d,%d\n", ID, namaBarang, harga, stok);
    fclose(outp);
}