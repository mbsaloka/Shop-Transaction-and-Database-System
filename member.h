FILE *inp, *outp;

static char *username, *pass;

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

void showMember(char *filter) {
    int COL_MAX = 22;
    int COL_MIN = 15;
    char *name, *phoneNum, *address, *registDate, *registTime;
    int ID, balance;
    char line[1000];
    const char *delimiter = ",";
    char *temp;
    inp = fopen(FILE_MEMBER, "r");

    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");
    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar      | Saldo\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        ID = atoi(strtok(line, delimiter));
        name = strtok(NULL, delimiter);
        phoneNum = strtok(NULL, delimiter);
        address = strtok(NULL, delimiter);
        registDate = strtok(NULL, delimiter);
        registTime = strtok(NULL, delimiter);
        for (int i = 0; i < 2; i++) temp = strtok(NULL, delimiter);
        balance = atoi(strtok(NULL, delimiter));

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

        for (int i = 0; i < strlen(filter); i++) {
            if (filter[i] >= 'A' && filter[i] <= 'Z') {
                filter[i] += 32;
            }
        }
        for (int i = 0; i < strlen(name); i++) {
            if (name[i] >= 'A' && name[i] <= 'Z') {
                name[i] += 32;
            }
        }

        if (strstr(name, filter)) {
            printf("%d%s|\t %s\t| %s\t| %s\t| %s %s | ", ID, space, name2, phoneNum, address, registDate, registTime);
            printMoney(balance);
            printf("\n");
        }
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
        username = getAllChar();
        if (strcmp(username, "ESCAPE") == 0) return 0;
        printf("Password : ");
        pass = getAllChar();
        if (strcmp(pass, "ESCAPE") == 0) {
            free(username);
            return 0;
        }

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
            free(username);
            free(pass);
            if (exitCode != 'Y') {
                clearScreen();
                return 0;
            }
        } else {
            printf("Lanjutkan membuat akun? (Y/N) ");
            exitCode = getYesNo();
            clearScreen();
            if (exitCode != 'Y') {
                free(username);
                free(pass);
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
    char *name, *phoneNum, *address, exitCode;
    int ID = getCurrentID() + 1, balance = 1000000;
    char line[1001];

    char nol[] = "00";
    nol[1] = (ID < 10) ? '0' : '\0';

    while (createAccount()) {
        clearScreen();
        printBold("MASUKKAN DATA DIRI ANDA\n");
        printf("Nama : ");
        name = getAlpha();
        if (strcmp(name, "ESCAPE") == 0) {
            free(username);
            free(pass);
            return;
        }
        printf("No Telpon : ");
        phoneNum = getNum();
        if (strcmp(phoneNum, "ESCAPE") == 0) {
            free(username);
            free(pass);
            free(name);
            return;
        }
        printf("Alamat : ");
        address = getAllChar();
        if (strcmp(address, "ESCAPE") == 0) {
            free(name);
            free(phoneNum);
            free(username);
            free(pass);
            return;
        }

        printf("Apakah data diri Anda sudah benar? (Y/N) ");
        exitCode = getYesNo();
        clearScreen();
        if (exitCode == 'Y') {
            outp = fopen(FILE_MEMBER, "a");
            fprintf(outp, "%d,%s,%s,%s,%s,%s,%s,%s,%d\n", ID, name, phoneNum, address, getDate(), getTime(), username, pass, balance);
            fclose(outp);
            free(name);
            free(phoneNum);
            free(address);
            free(username);
            free(pass);
            printf("Anda berhasil terdaftar sebagai membership.");
            sleep(1);
            clearScreen();
            return;
        } else {
            printf("Proses dibatalkan.");
            sleep(1);
            clearScreen();
            printf("Coba buat akun lagi? (Y/N) ");
            free(name);
            free(phoneNum);
            free(address);
            free(username);
            free(pass);
            exitCode = getYesNo();
            if (exitCode != 'Y') {
                clearScreen();
                return;
            }
        }
    }
}
