static char *username, *pass, guestName[101];
static int guestID = 0;

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
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}