#define FILE_MEMBER "database/db_member.csv"
#define CHAR_LIMIT 14
FILE *inp, *outp;

static char *name, *phoneNum, *address, *registDate, *registTime;
static int ID;
static char line[1000];

void renderMember() {
    inp = fopen(FILE_MEMBER, "r");

    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");
    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar\n");
    printf("-----------------------------------------------------------------------------------------\n");
    fgets(line, sizeof(line), inp);
    const char *delimiter = ",";
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        name = strtok(NULL, delimiter);
        phoneNum = strtok(NULL, delimiter);
        address = strtok(NULL, delimiter);
        registDate = strtok(NULL, delimiter);
        registTime = strtok(NULL, delimiter);

        // if (strlen(namaBarang) > CHAR_LIMIT) {
        //     namaBarang[CHAR_LIMIT - 2] = '.';
        //     namaBarang[CHAR_LIMIT - 1] = '.';
        //     namaBarang[CHAR_LIMIT] = '\0';
        // }

        char space[] = "    ";
        space[3] = (ID < 10) ? ' ' : '\0';

        printf("%d%s|\t %s\t| %s\t| %s\t| %s %s", ID, space, name, phoneNum, address, registDate, registTime);
    }

    fclose(inp);
}

void inputMember() {
    char username[100], password[100];

    inp = fopen(FILE_MEMBER, "r");
    while (fgets(line, sizeof(line), inp)) {
        ID = atoi(strtok(line, ",")) + 1;
    }
    fclose(inp);

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';

    // do {
    //     clearScreen();
    //     printBold("BUAT AKUN MEMBERSHIP\n");
    //     printf("Username : ");
    //     fgets(username, 100, stdin);
    //     printf("Password : ");
    //     fgets(password, 100, stdin);
    //     username[strlen(username) - 1] = '\0';
    //     password[strlen(password) - 1] = '\0';
    // }

    printBold("MASUKKAN DATA DIRI ANDA\n");
    printf("ID %s%d\n", nol, ID);
    fflush(stdin);
    printf("Nama : ");
    fgets(name, 100, stdin);
    printf("No Telpon : ");
    fgets(phoneNum, 20, stdin);
    printf("Alamat : ");
    fgets(address, 100, stdin);

    name[strlen(name) - 1] = '\0';
    phoneNum[strlen(phoneNum) - 1] = '\0';
    address[strlen(address) - 1] = '\0';

    outp = fopen(FILE_MEMBER, "a");
    fprintf(outp, "%d,%s,%s,%s,%s,%s\n", ID, name, phoneNum, address, getDate(), getTime());
    fclose(outp);
}