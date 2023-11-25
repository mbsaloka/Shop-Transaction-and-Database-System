FILE *inp, *outp;

static char *username, *pass;
char exitCode;

void showMember(char *filter) {
    int COL_MAX = 22;
    int COL_MIN = 15;
    char *name, *phoneNum, *address, *registDate, *registTime;
    int ID, balance;

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");
    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar      | Saldo\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < numMember; i++) {
        ID = member[i].ID;
        name = member[i].name;
        phoneNum = member[i].phoneNum;
        address = member[i].address;
        balance = member[i].balance;
        registDate = member[i].registDate;
        registTime = member[i].registTime;

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
        for (int i = 0; i < numMember; i++) {
            if (strcmp(member[i].username, username) == 0) {
                isUsed = 1;
                break;
            }
        }

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
    int ID, balance = 1000000;

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
            int idx = numMember;
            member[idx].ID = (idx == 0) ? 1 : member[idx - 1].ID + 1;
            strcpy(member[idx].name, name);
            strcpy(member[idx].phoneNum, phoneNum);
            strcpy(member[idx].address, address);
            strcpy(member[idx].username, username);
            strcpy(member[idx].password, pass);
            strcpy(member[idx].registDate, getDate());
            strcpy(member[idx].registTime, getTime());
            member[idx].balance = balance;
            addToDb(&member[numMember], sizeof(Member), FILE_MEMBER);
            numMember++;
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
