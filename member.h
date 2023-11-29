void showMember(char *filter) {
    char name[101];
    int ID, balance;
    numTempFilterMember = 0;

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");
    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar      | Username\t| Password\t| Saldo\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < numMember; i++) {
        strcpy(name, member[i].name);
        toLower(name);
        toLower(filter);

        if (strstr(name, filter)) {
            tempFilterMember[numTempFilterMember++] = member[i];
            printf("%-5.d|\t %-22.22s | %-13.13s | %-21.21s | %s %s | ", member[i].ID, member[i].name, member[i].phoneNum, member[i].address, member[i].registDate, member[i].registTime);
            printf("%-15.15s | %-15.15s | ", member[i].username, member[i].password);
            printMoney(member[i].balance);
            printf("\n");
        }
    }
}

void updateMember(int ID) {
    int idx = 0;
    int balance;
    char name[101], phoneNum[20], address[101], username[101], password[101];

    for (int i = 0; i < numMember; i++) {
        if (member[i].ID == ID) {
            idx = i;
            break;
        }
    }

    int code;
    char *option[] = {
        "Perbarui Info Member",
        "Hapus Member",
        "Kembali",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    printf("Ingin melakukan apa?\n");
    code = chooseOption(option, lengthOption);
    switch (code) {
    case 0:
        printf("\033[2B");
        CLEAR_ROW(3);
        printBold("\nPERBARUI INFO MEMBER (tekan tab untuk isi otomatis.)\n");
        printf("ID : %d\n", ID);
        printf("Nama : \x1b[90m%s\x1b[0m\n", member[idx].name);
        printf("No Telp : \x1b[90m%s\x1b[0m\n", member[idx].phoneNum);
        printf("Alamat : \x1b[90m%s\x1b[0m\n", member[idx].address);
        printf("Saldo : \x1b[90m%d\x1b[0m\n", member[idx].balance);
        printf("Username : \x1b[90m%s\x1b[0m\n", member[idx].username);
        printf("Password : \x1b[90m%s\x1b[0m\n", member[idx].password);
        printf("\033[6A\r");
        printf("Nama : ");
        if (getTabStr(name, member[idx].name) == -1) return;
        printf("No Telp : ");
        if (getTabStr(phoneNum, member[idx].phoneNum) == -1) return;
        printf("Alamat : ");
        if (getTabStr(address, member[idx].address) == -1) return;
        printf("Saldo : ");
        if (getTabInt(&balance, member[idx].balance) == -1) return;
        printf("Username : ");
        if (getTabStr(username, member[idx].username) == -1) return;
        printf("Password : ");
        if (getTabStr(password, member[idx].password) == -1) return;

        printf("Apakah Anda yakin ingin memperbarui member %s? (Y/N) ", name);
        if (getYesNo() == 'Y') {
            clearScreen();

            strcpy(member[idx].name, name);
            strcpy(member[idx].phoneNum, phoneNum);
            strcpy(member[idx].address, address);
            strcpy(member[idx].username, username);
            strcpy(member[idx].password, password);
            member[idx].balance = balance;

            updateData(member, sizeof(Member), numMember, FILE_MEMBER);

            printf("%s berhasil diperbarui.", name);
            sleep(1);
            clearScreen();
        } else {
            printf("Proses dibatalkan.");
            sleep(1);
            clearScreen();
        }
        break;
    case 1:
        clearScreen();
        printf("Apakah Anda yakin ingin menghapus Member %s? (Y/N) ", member[idx].name);
        if (getYesNo() == 'Y') {
            printf("%s berhasil dihapus.", member[idx].name);
            removeData(member, sizeof(Member), ID, &numMember, FILE_MEMBER, getMemberID);
            importFromDb(member, sizeof(Member), &numMember, FILE_MEMBER);

            sleep(1);
            clearScreen();
        } else {
            printf("Proses dibatalkan.");
            sleep(1);
            clearScreen();
        }
        break;
    }
}

int createAccount(char *username, char *password) {
    do {
        int isUsed = 0;
        clearScreen();
        printBold("BUAT AKUN MEMBERSHIP\n");

        printf("Username : ");
        getAlphaNum(username);
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
