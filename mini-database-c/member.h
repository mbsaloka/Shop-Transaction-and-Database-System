#define FILE_MEMBER "database/db_member.csv"
#define CHAR_LIMIT 14
FILE *inp, *outp;

static char username[100], password[100];

int getCurrentID() {
    inp = fopen(FILE_MEMBER, "r");
    char line[1000];
    int currentID = 1;
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        currentID = atoi(strtok(line, ","));
    }
    fclose(inp);
    return currentID;
}

void renderMember() {
    char *name, *phoneNum, *address, *registDate, *registTime;
    int ID;
    char line[1000];
    const char *delimiter = ",";
    char *temp;
    inp = fopen(FILE_MEMBER, "r");

    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");
    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar\n");
    printf("-----------------------------------------------------------------------------------------\n");
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        name = strtok(NULL, delimiter);
        phoneNum = strtok(NULL, delimiter);
        address = strtok(NULL, delimiter);
        registDate = strtok(NULL, delimiter);
        registTime = strtok(NULL, delimiter);

        char space[] = "    ";
        space[3] = (ID < 10) ? ' ' : '\0';

        printf("%d%s|\t %s\t| %s\t| %s\t| %s %s\n", ID, space, name, phoneNum, address, registDate, registTime);
    }

    fclose(inp);
}

int createAccount() {
    const char *delimiter = ",";
    char line[1000];
    do {
        int isUsed = 0;
        clearScreen();
        printBold("BUAT AKUN MEMBERSHIP\n");

        printf("Username : ");
        fflush(stdin);
        fgets(username, 100, stdin);
        printf("Password : ");
        fgets(password, 100, stdin);
        username[strlen(username) - 1] = '\0';
        password[strlen(password) - 1] = '\0';

        // Check is username used
        char *temp, exitCode[10];
        inp = fopen(FILE_MEMBER, "r");
        fgets(line, sizeof(line), inp);
        while (fgets(line, sizeof(line), inp) != NULL) {
            temp = strtok(line, delimiter);
            for (int i = 0; i < 5; i++) temp = strtok(NULL, delimiter);
            temp = strtok(NULL, delimiter);
            if (strcmp(temp, username) == 0) {
                isUsed = 1;
                break;
            }
        }
        fclose(inp);
        if (isUsed) {
            printf("Username sudah terdaftar, gunakan username yang berbeda!\n");
            printf("Coba buat akun lagi? (Y/N) ");
            scanf("%s", exitCode);
            if (strcmp(exitCode, "Y") != 0 && strcmp(exitCode, "y") != 0) {
                clearScreen();
                return 0;
            }
        } else {
            return 1;
        }
    } while (1);
}

void inputMember() {
    char name[100], phoneNum[20], address[100];
    int ID = getCurrentID() + 1;
    char line[1000];
    inp = fopen(FILE_MEMBER, "r");
    fclose(inp);

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';

    if (createAccount()) {
        clearScreen();
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
        fprintf(outp, "%d,%s,%s,%s,%s,%s,%s,%s\n", ID, name, phoneNum, address, getDate(), getTime(), username, password);
    }
    fclose(outp);
}
