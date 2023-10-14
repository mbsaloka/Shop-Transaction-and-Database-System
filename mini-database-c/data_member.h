#define FILE_MEMBER "database/db_member.csv"
#define CHAR_LIMIT 14
FILE *inp, *outp;

void renderMember() {
    inp = fopen(FILE_MEMBER, "r");

    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");

    char line[1000];
    char *namaPelanggan, *noTelp, *alamat, *tanggalDaftar, *waktuDaftar;
    int ID;
    const char *delimiter = ",";

    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar\n");
    printf("-----------------------------------------------------------------------------------------\n");
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        namaPelanggan = strtok(NULL, delimiter);
        noTelp = strtok(NULL, delimiter);
        alamat = strtok(NULL, delimiter);
        tanggalDaftar = strtok(NULL, delimiter);
        waktuDaftar = strtok(NULL, delimiter);

        // if (strlen(namaBarang) > CHAR_LIMIT) {
        //     namaBarang[CHAR_LIMIT - 2] = '.';
        //     namaBarang[CHAR_LIMIT - 1] = '.';
        //     namaBarang[CHAR_LIMIT] = '\0';
        // }

        char space[] = "    ";
        space[3] = (ID < 10) ? ' ' : '\0';

        printf("%d%s|\t %s\t| %s\t| %s\t| %s %s", ID, space, namaPelanggan, noTelp, alamat, tanggalDaftar, waktuDaftar);
    }

    fclose(inp);
}

void inputMember() {
    char namaPelanggan[100], noTelp[20], alamat[100];
    int ID = 1;

    inp = fopen(FILE_MEMBER, "r");
    char line[1000];
    while (fgets(line, sizeof(line), inp)) {
        ID = atoi(strtok(line, ",")) + 1;
    }
    fclose(inp);

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';

    printBold("MASUKKAN DATA DIRI ANDA\n");
    printf("ID %s%d\n", nol, ID);
    fflush(stdin);
    printf("Nama : ");
    fgets(namaPelanggan, 100, stdin);
    printf("No Telpon : ");
    fgets(noTelp, 20, stdin);
    printf("Alamat : ");
    fgets(alamat, 100, stdin);

    namaPelanggan[strlen(namaPelanggan) - 1] = '\0';
    noTelp[strlen(noTelp) - 1] = '\0';
    alamat[strlen(alamat) - 1] = '\0';

    outp = fopen(FILE_MEMBER, "a");
    fprintf(outp, "%d,%s,%s,%s,%s,%s\n", ID, namaPelanggan, noTelp, alamat, getDate(), getTime());
    fclose(outp);
}