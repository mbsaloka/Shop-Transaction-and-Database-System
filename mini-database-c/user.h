static char *username, *pass, guestName[101];
static int guestID = 0;

int memberTopUp() {
    int topUpAmount = 0;
    int newBalance;
    do {
        clearScreen();
        printf("Masukkan jumlah uang yang ingin Anda isi!\n");
        printf("Jumlah Uang : ");
        topUpAmount = getNumINT();
        if (topUpAmount > 10000000) {
            clearScreen();
            printf("ISI SALDO GAGAL!\nNominal yang dimasukkan tidak bisa melebihi 10 juta.");
            sleep(1);
        } else {
            break;
        }
    } while (1);
    char *temp;
    int tempID;
    char line[1000];
    inp = fopen(FILE_MEMBER, "r");
    outp = fopen("database/temp_member.csv", "w");
    fgets(line, sizeof(line), inp);
    fprintf(outp, line);
    while (fgets(line, sizeof(line), inp) != NULL) {
        tempID = atoi(strtok(line, ","));
        fprintf(outp, "%d", tempID);
        for (int i = 0; i < 7; i++) {
            temp = strtok(NULL, ",");
            fprintf(outp, ",%s", temp);
        }
        if (tempID == guestID) {
            newBalance = atoi(strtok(NULL, ",")) + topUpAmount;
            printf("NEW BALANCE : %d\n", newBalance);
            fprintf(outp, ",%d\n", newBalance);
        } else {
            temp = strtok(NULL, ",");
            fprintf(outp, ",%s", temp);
        }
    }
    fclose(inp);
    fclose(outp);

    inp = fopen("database/temp_member.csv", "r");
    outp = fopen(FILE_MEMBER, "w");
    while (fgets(line, sizeof(line), inp) != NULL) {
        fprintf(outp, line);
    }
    fclose(inp);
    fclose(outp);

    remove("database/temp_member.csv");

    printf("Isi Saldo Berhasil!\n Saldo anda sekarang ");
    printMoney(newBalance);
    sleep(1);
}

int memberLogin() {
    const char *delimiter = ",";
    char line[1000];
    int isFound = 0, passFlag;
    do {
        clearScreen();
        printBold("LOGIN MEMBERSHIP\n");
        printBold("Masukkan Username dan Password\n");
        printf("Username : ");
        fflush(stdin);
        username = getAllChar();
        if (strcmp(username, "ESCAPE") == 0) return -1;
        printf("Password : ");
        pass = getPass();
        if (strcmp(pass, "ESCAPE") == 0) {
            free(username);
            return -1;
        }

        // Check is username exist
        char *temp, *tempName, exitCode;
        int tempID;
        passFlag = 1;
        inp = fopen(FILE_MEMBER, "r");
        fgets(line, sizeof(line), inp);
        while (fgets(line, sizeof(line), inp) != NULL) {
            tempID = atoi(strtok(line, delimiter));
            tempName = strtok(NULL, delimiter);
            for (int i = 0; i < 5; i++) temp = strtok(NULL, delimiter);
            if (strcmp(temp, username) == 0) {
                temp = strtok(NULL, delimiter);
                if (strcmp(temp, pass) == 0) {
                    isFound = 1;
                    strcpy(guestName, tempName);
                    guestID = tempID;
                    break;
                } else {
                    printf("Password salah!\n");
                    passFlag = 0;
                }
            }
        }
        free(username);
        free(pass);
        if (!isFound) {
            if (passFlag) {
                printf("Username tidak terdaftar!\n");
            }
            printf("Coba login kembali? (Y/N) ");
            exitCode = getYesNo();
            if (exitCode == 'N') return 0;
            if (exitCode == 'E') return -1;
        }
        fclose(inp);
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
        guestID = 0;
        printBold("Masukkan nama Anda (guest)\n");
        printf("Nama : ");
        char *temp;
        temp = getAlpha();
        if (strcmp(temp, "ESCAPE") == 0) return;
        strcpy(guestName, temp);
        free(temp);
    }

    clearScreen();
    printf("Selamat Datang %s!", guestName);
    sleep(1);
    int code;
    char *option[] = {
        "(0) Keluar",
        "(1) Mulai Belanja",
        "(2) Daftar Membership",
        "(3) Isi Saldo",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printBold("Ingin melakukan apa?\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            printBold("Selamat Berbelanja Kembali!\n");
            sleep(1);
            break;
        case 1:
            shoppingMenu(guestName, guestID);
            break;
        case 2:
            if (isMember) {
                printf("Anda sudah terdaftar.");
                sleep(1);
            } else {
                int before = getCurrentID();
                inputMember();
                int after = getCurrentID();
                if (before != after) isMember = 1;
            }
            break;
        case 3:
            if (!isMember) {
                printf("Anda harus menjadi member terlebih dahulu untuk mengisi saldo.");
                sleep(1);
            } else {
                memberTopUp(guestID);
            }
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}