void showMember(char *filter) {
    int COL_MAX = 22;
    int COL_MIN = 15;
    char name[101], phoneNum[20], address[101], username[101], password[101];
    char registDate[15], registTime[15];
    int ID, balance;

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");
    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar      | Saldo\t\t| Username\t| Password\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < numMember; i++) {
        ID = member[i].ID;
        strcpy(name, member[i].name);
        strcpy(phoneNum, member[i].phoneNum);
        strcpy(address, member[i].address);
        strcpy(username, member[i].username);
        strcpy(password, member[i].password);
        strcpy(registDate, member[i].registDate);
        strcpy(registTime, member[i].registTime);
        balance = member[i].balance;

        char space[] = "    ";
        space[3] = (ID < 10) ? ' ' : '\0';

        char name2[101];
        strcpy(name2, name);
        if (strlen(name) > COL_MAX) {
            name[COL_MAX - 2] = '.';
            name[COL_MAX - 1] = '.';
            name[COL_MAX] = '\0';
        }

        if (strlen(name) < COL_MIN) {
            int nameLength = strlen(name);
            for (int i = 0; i <= COL_MIN - nameLength; i++) {
                strcat(name, " ");
            }
        }

        for (int i = 0; i < strlen(filter); i++) {
            if (filter[i] >= 'A' && filter[i] <= 'Z') {
                filter[i] += 32;
            }
        }
        for (int i = 0; i < strlen(name2); i++) {
            if (name2[i] >= 'A' && name2[i] <= 'Z') {
                name2[i] += 32;
            }
        }

        if (strstr(name2, filter)) {
            printf("%d%s|\t %s\t| %s\t| %s\t| %s %s | ", ID, space, name, phoneNum, address, registDate, registTime);
            printMoney(balance);
            printf("\t| %s\t| %s\n", username, password);
        }
    }
}

int createAccount(char *username, char *password) {
    do {
        int isUsed = 0;
        clearScreen();
        printBold("BUAT AKUN MEMBERSHIP\n");

        printf("Username : ");
        fflush(stdin);
        getAllChar(username);
        if (strcmp(username, "ESCAPE") == 0) return 0;
        printf("Password : ");
        getPass(password);
        if (strcmp(password, "ESCAPE") == 0) return 0;

        for (int i = 0; i < numMember; i++) {
            if (strcmp(member[i].username, username) == 0) {
                isUsed = 1;
                break;
            }
        }

        if (isUsed) {
            printf("Username sudah terdaftar, gunakan username yang berbeda!\n");
            printf("Coba buat akun lagi? (Y/N) ");
            if (getYesNo() != 'Y') {
                clearScreen();
                return 0;
            }
        } else {
            printf("Lanjutkan membuat akun? (Y/N) ");
            if (getYesNo() != 'Y') {
                clearScreen();
                printf("Proses dibatalkan.");
                sleep(1);
                clearScreen();
                printf("Coba buat akun lagi? (Y/N) ");
                if (getYesNo() != 'Y') {
                    clearScreen();
                    return 0;
                }
            } else {
                return 1;
            }
        }
    } while (1);
    printf("Proses dibatalkan.\n");
    return 1;
}

void inputMember() {
    char name[101], phoneNum[20], address[101], username[101], password[101];
    int ID, balance = 1000000;

    while (createAccount(username, password)) {
        clearScreen();
        printBold("MASUKKAN DATA DIRI ANDA\n");
        printf("Nama : ");
        getAlpha(name);
        if (strcmp(name, "ESCAPE") == 0) return;
        printf("No Telpon : ");
        getNum(phoneNum);
        if (strcmp(phoneNum, "ESCAPE") == 0) return;
        printf("Alamat : ");
        getAllChar(address);
        if (strcmp(address, "ESCAPE") == 0) return;

        printf("Apakah data diri Anda sudah benar? (Y/N) ");
        if (getYesNo() == 'Y') {
            clearScreen();
            int idx = numMember;
            member[idx].ID = (idx == 0) ? 1 : member[idx - 1].ID + 1;
            strcpy(member[idx].name, name);
            strcpy(member[idx].phoneNum, phoneNum);
            strcpy(member[idx].address, address);
            strcpy(member[idx].username, username);
            strcpy(member[idx].password, password);
            strcpy(member[idx].registDate, getDate());
            strcpy(member[idx].registTime, getTime());
            member[idx].balance = balance;
            addToDb(&member[numMember], sizeof(Member), FILE_MEMBER);
            numMember++;
            printf("Anda berhasil terdaftar sebagai membership.");
            sleep(1);
            clearScreen();
            return;
        } else {
            clearScreen();
            printf("Proses dibatalkan.");
            sleep(1);
            printf("Coba buat akun lagi? (Y/N) ");
            if (getYesNo() != 'Y') {
                clearScreen();
                return;
            }
        }
    }
}
