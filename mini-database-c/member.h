#define FILE_MEMBER "database/db_member.csv"
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
    int COL_MAX = 22;
    int COL_MIN = 15;
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

        char name2[100];
        strcpy(name2, name);
        if (strlen(name2) > COL_MAX) {
            name2[COL_MAX - 2] = '.';
            name2[COL_MAX - 1] = '.';
            name2[COL_MAX] = '\0';
        }

        if (strlen(name2) < COL_MIN) {
            int nameLength = strlen(name2);
            for (int i = 0; i <= COL_MIN - nameLength; i++) {
                strcat(name2, " ");
            }
        }
        printf("%d%s|\t %s\t| %s\t| %s\t| %s %s\n", ID, space, name2, phoneNum, address, registDate, registTime);
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
        char *temp, exitCode;
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
            exitCode = getYesNo();
            if (exitCode != 'Y') {
                clearScreen();
                return 0;
            }
        } else {
            printf("Lanjutkan membuat akun? (Y/N) ");
            exitCode = getYesNo();
            clearScreen();
            if (exitCode != 'Y') {
                printf("Proses dibatalkan.");
                sleep(1);
                clearScreen();
                printf("Coba buat akun lagi? (Y/N) ");
                exitCode = getYesNo();
                if (exitCode != 'Y') {
                    clearScreen();
                    return 0;
                }
            } else {
                return 1;
            }
        }
    } while (1);
}

void inputMember() {
    char *name, *phoneNum, address[100], exitCode;
    int ID = getCurrentID() + 1;
    char line[1000];

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';

    while (createAccount()) {
        clearScreen();
        printBold("MASUKKAN DATA DIRI ANDA\n");
        printf("Nama : ");
        name = getAlpha();
        printf("\nNo Telpon : ");
        phoneNum = getNum();
        printf("\nAlamat : ");
        fgets(address, 100, stdin);
        address[strlen(address) - 1] = '\0';

        printf("Apakah data diri Anda sudah benar? (Y/N) ");
        exitCode = getYesNo();
        clearScreen();
        if (exitCode == 'Y') {
            outp = fopen(FILE_MEMBER, "a");
            fprintf(outp, "%d,%s,%s,%s,%s,%s,%s,%s\n", ID, name, phoneNum, address, getDate(), getTime(), username, password);
            free(name);
            free(phoneNum);
            fclose(outp);
            printf("Anda berhasil terdaftar sebagai membership.");
            sleep(1);
            clearScreen();
            break;
        } else {
            printf("Proses dibatalkan.");
            sleep(1);
            clearScreen();
            printf("Coba buat akun lagi? (Y/N) ");
            exitCode = getYesNo();
            if (exitCode != 'Y') {
                clearScreen();
                break;
            }
        }
    }
}
