void showMember(char *filter) {
    char name[101];
    numTempFilterMember = 0;
    tempFilterMember = NULL;

    printBold("DAFTAR PELANGGAN MEMBERSHIP\n");
    printBold("ID   |\t Nama Pelanggan    \t| No Telp\t| Alamat Pelanggan\t| Tanggal Daftar      | Username\t| Password\t| Saldo\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");
    Member *curMember = member, *prevFilterMember = NULL;
    while (curMember != NULL) {
        strcpy(name, curMember->name);
        toLower(name);
        toLower(filter);
        if (strstr(name, filter)) {
            numTempFilterMember++;
            Member *newFilterMember = (Member *)malloc(sizeof(Member));
            newFilterMember = curMember;
            if (tempFilterMember == NULL) {
                tempFilterMember = newFilterMember;
                tempFilterMember->next = NULL;
                prevFilterMember = tempFilterMember;
            } else {
                prevFilterMember->next = newFilterMember;
                newFilterMember->next = NULL;
                prevFilterMember = newFilterMember;
            }
            printf("%-5.d|\t %-22.22s | %-13.13s | %-21.21s | %s %s | ", curMember->ID, curMember->name, curMember->phoneNum, curMember->address, curMember->registDate, curMember->registTime);
            printf("%-15.15s | %-13.13s | ", curMember->username, curMember->password);
            printMoney(curMember->balance);
            printf("\n");
        }
    }
}

void searchMemberByID(int ID, Member **curMember, Member **prevMember) {
    Member *cur = member;
    curMember = NULL;
    prevMember = NULL;
    if (cur->ID == ID) {
        *curMember = cur;
        *prevMember = NULL;
        return;
    }
    while (cur != NULL) {
        if (cur->next->ID == ID) {
            *curMember = cur->next;
            *prevMember = cur;
            return;
        }
        cur = cur->next;
    }
}

void updateMember(int ID) {
    Member *curMember, *prevMember;
    searchMemberByID(ID, &curMember, &prevMember);

    int balance;
    char name[101] = "\0", phoneNum[20] = "\0", address[101] = "\0";
    char username[101] = "\0", password[101] = "\0";

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
        CURSOR_DOWN(2);
        CLEAR_ROW(3);
        printBold("\nPERBARUI INFO MEMBER (tekan tab untuk isi otomatis.)\n");
        printf("ID : %d\n", ID);
        printf("Nama : %s%s%s\n", GRAY, curMember->name, NO_EFFECT);
        printf("No Telp : %s%s%s\n", GRAY, curMember->phoneNum, NO_EFFECT);
        printf("Alamat : %s%s%s\n", GRAY, curMember->address, NO_EFFECT);
        printf("Saldo : %s%d%s\n", GRAY, curMember->balance, NO_EFFECT);
        printf("Username : %s%s%s\n", GRAY, curMember->username, NO_EFFECT);
        printf("Password : %s%s%s\n", GRAY, curMember->password, NO_EFFECT);
        CURSOR_UP(6);
        printf("Nama : ");
        if (getTabStr(name, curMember->name) == -1) return;
        printf("No Telp : ");
        if (getTabNumStr(phoneNum, curMember->phoneNum) == -1) return;
        printf("Alamat : ");
        if (getTabStr(address, curMember->address) == -1) return;
        printf("Saldo : ");
        if (getTabInt(&balance, curMember->balance) == -1) return;
        printf("Username : ");
        if (getTabStr(username, curMember->username) == -1) return;
        printf("Password : ");
        if (getTabStr(password, curMember->password) == -1) return;

        printf("Apakah Anda yakin ingin memperbarui member %s? (Y/N) ", name);
        if (getYesNo() == 'Y') {
            clearScreen();

            strcpy(curMember->name, name);
            strcpy(curMember->phoneNum, phoneNum);
            strcpy(curMember->address, address);
            strcpy(curMember->username, username);
            strcpy(curMember->password, password);
            curMember->balance = balance;

            updateData(member, sizeof(Member), FILE_MEMBER, getMemberNext);

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
        printf("Apakah Anda yakin ingin menghapus Member %s? (Y/N) ", curMember->name);
        if (getYesNo() == 'Y') {
            printf("%s berhasil dihapus.", curMember->name);
            prevMember->next = curMember->next;
            updateData(member, sizeof(Member), FILE_MEMBER, getMemberNext);
            numMember--;
            free(curMember);

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

        Member *cur = member;
        while (cur != NULL) {
            if (strcmp(cur->username, username) == 0) {
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
    char name[101] = "\0", phoneNum[20] = "\0", address[101] = "\0", username[101] = "\0", password[101] = "\0";
    int ID, balance = 1000000;
    Member *curMember = member;
    while (curMember != NULL) {
        ID = curMember->ID;
        curMember = curMember->next;
    }
    ID++;

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

            Member *newMember = (Member *)malloc(sizeof(Member));
            newMember->ID = ID;
            strcpy(newMember->name, name);
            strcpy(newMember->phoneNum, phoneNum);
            strcpy(newMember->address, address);
            strcpy(newMember->username, username);
            strcpy(newMember->password, password);
            strcpy(newMember->registDate, getDate());
            strcpy(newMember->registTime, getTime());
            newMember->balance = balance;
            newMember->next = NULL;

            if (member == NULL) {
                member = newMember;
            } else {
                curMember->next = newMember;
            }

            addToDb(&member, sizeof(Member), FILE_MEMBER);
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
