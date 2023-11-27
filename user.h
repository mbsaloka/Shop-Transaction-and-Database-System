void memberTopUp() {
    int topUpAmount, newBalance;
    do {
        clearScreen();
        printf("Masukkan jumlah uang yang ingin Anda isi!\n");
        printf("Jumlah Uang : ");
        topUpAmount = getNumINT();
        if (topUpAmount == -1) return;
        if (topUpAmount > 10000000) {
            clearScreen();
            printf("ISI SALDO GAGAL!\nNominal yang dimasukkan tidak bisa melebihi 10 juta.");
            sleep(1);
        } else {
            break;
        }
    } while (1);

    for (int i = 0; i < numMember; i++) {
        if (onlineUser.ID == member[i].ID) {
            member[i].balance += topUpAmount;
            onlineUser.balance += topUpAmount;
        }
    }
    updateData(member, sizeof(Member), numMember, FILE_MEMBER);

    printf("Isi Saldo Berhasil!\nSaldo anda sekarang ");
    printMoney(onlineUser.balance);
    sleep(1);
}

int memberLogin() {
    int isFound = 0, passFlag;
    char username[101], password[101];
    do {
        clearScreen();
        printBold("LOGIN MEMBERSHIP\n");
        printBold("Masukkan Username dan Password\n");
        printf("Username : ");
        getAlphaNum(username);
        if (strcmp(username, "ESCAPE") == 0) return -1;
        printf("Password : ");
        getPass(password);
        if (strcmp(password, "ESCAPE") == 0) return -1;

        char *temp, *tempName;
        int tempID;
        passFlag = 1;
        for (int i = 0; i < numMember; i++) {
            if (strcmp(member[i].username, username) == 0) {
                if (strcmp(member[i].password, password) == 0) {
                    isFound = 1;
                    onlineUser = member[i];
                } else {
                    passFlag = 0;
                }
                break;
            }
        }

        if (!isFound) {
            if (passFlag) {
                printf("Username tidak terdaftar!\n");
            } else {
                printf("Password salah!\n");
            }
            printf("Coba login kembali? (Y/N) ");
            char exitCode = getYesNo();
            if (exitCode == 'N') return 0;
            if (exitCode == 'E') return -1;
        }
    } while (!isFound);
    return 1;
}

void user() {
    clearScreen();
    char exitCode;
    int isMember = 0;
    printBold("Apakah Anda sudah berlangganan Membership? (Y/N) ");
    exitCode = getYesNo();
    if (exitCode == 'Y') {
        isMember = memberLogin();
    } else if (exitCode == 'E') {
        return;
    }

    if (isMember == -1) return;
    if (!isMember) {
        clearScreen();
        printBold("Masukkan nama Anda (guest)\n");
        printf("Nama : ");
        char name[101];
        getAlpha(name);
        if (strcmp(name, "ESCAPE") == 0) return;
        strcpy(onlineUser.name, name);
        onlineUser.ID = 0;
        onlineUser.balance = 100000;
    }

    clearScreen();
    printf("Selamat Datang %s!", onlineUser.name);
    sleep(1);
    int code;
    char *option[] = {
        "Mulai Belanja",
        "Daftar Membership",
        "Isi Saldo",
        "Ubah Data Diri",
        "Keluar",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printBold("Ingin melakukan apa?\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            shoppingMenu();
            break;
        case 1:
            if (isMember) {
                printf("Anda sudah terdaftar.");
                sleep(1);
            } else {
                int before = numMember;
                inputMember();
                if (before != numMember) {
                    onlineUser = member[numMember - 1];
                    isMember = 1;
                }
            }
            break;
        case 2:
            if (!isMember) {
                printf("Anda harus menjadi member terlebih dahulu untuk mengisi saldo.");
                sleep(1);
            } else {
                memberTopUp();
            }
            break;
        case 3:
            if (!isMember) {
                printf("Anda harus menjadi member terlebih dahulu untuk mengubah data diri.");
                sleep(1);
                break;
            }
            int idx = 0;
            char name[101], phoneNum[20], address[101], username[101], password[101];
            for (int i = 0; i < numMember; i++) {
                if (member[i].ID == onlineUser.ID) {
                    idx = i;
                    break;
                }
            }
            printBold("\nPERBARUI DATA DIRI (tekan tab untuk isi otomatis.)\n");
            printf("ID : %d\n", member[idx].ID);
            printf("Nama : \x1b[90m%s\x1b[0m\n", member[idx].name);
            printf("No Telp : \x1b[90m%s\x1b[0m\n", member[idx].phoneNum);
            printf("Alamat : \x1b[90m%s\x1b[0m\n", member[idx].address);
            printf("Username : \x1b[90m%s\x1b[0m\n", member[idx].username);
            printf("Password : \x1b[90m%s\x1b[0m\n", member[idx].password);
            printf("\033[5A\r");
            printf("Nama : ");
            if (getTabStr(name, member[idx].name) == -1) break;
            printf("No Telp : ");
            if (getTabStr(phoneNum, member[idx].phoneNum) == -1) break;
            printf("Alamat : ");
            if (getTabStr(address, member[idx].address) == -1) break;
            printf("Username : ");
            if (getTabStr(username, member[idx].username) == -1) break;
            printf("Password : ");
            if (getTabStr(password, member[idx].password) == -1) break;

            printf("Apakah Anda yakin ingin memperbarui member %s? (Y/N) ", name);
            if (getYesNo() == 'Y') {
                clearScreen();

                strcpy(member[idx].name, name);
                strcpy(member[idx].phoneNum, phoneNum);
                strcpy(member[idx].address, address);
                strcpy(member[idx].username, username);
                strcpy(member[idx].password, password);

                updateData(member, sizeof(Member), numMember, FILE_MEMBER);
                onlineUser = member[idx];

                printf("%s berhasil diperbarui.", name);
                sleep(1);
                clearScreen();
            } else {
                printf("Proses dibatalkan.");
                sleep(1);
                clearScreen();
            }
            break;
        case 4:
            printBold("Selamat Berbelanja Kembali!\n");
            sleep(1);
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != lengthOption - 1);
}