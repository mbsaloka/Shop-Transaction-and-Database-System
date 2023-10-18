static char username[100], password[100], guestName[100];

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
        fgets(username, 100, stdin);
        printf("Password : ");
        fgets(password, 100, stdin);
        username[strlen(username) - 1] = '\0';
        password[strlen(password) - 1] = '\0';

        // Check is username exist
        char *temp, *tempName, exitCode;
        passFlag = 1;
        inp = fopen(FILE_MEMBER, "r");
        fgets(line, sizeof(line), inp);
        while (fgets(line, sizeof(line), inp) != NULL) {
            temp = strtok(line, delimiter);
            tempName = strtok(NULL, delimiter);
            for (int i = 0; i < 4; i++) temp = strtok(NULL, delimiter);
            temp = strtok(NULL, delimiter);
            if (strcmp(temp, username) == 0) {
                temp = strtok(NULL, delimiter);
                temp[strlen(temp) - 1] = '\0';
                if (strcmp(temp, password) == 0) {
                    isFound = 1;
                    strcpy(guestName, tempName);
                    break;
                } else {
                    printf("Password salah!\n");
                    passFlag = 0;
                }
            }
        }
        if (!isFound) {
            if (passFlag) {
                printf("Username tidak terdaftar!\n");
            }
            printf("Coba login kembali? (Y/N) ");
            exitCode = getYesNo();
            if (exitCode != 'Y') return 0;
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
    if (exitCode == 'Y') isMember = memberLogin();

    if (!isMember) {
        clearScreen();
        printBold("Masukkan nama Anda (guest)\n");
        printf("Nama : ");
        char *temp;
        temp = getAlpha();
        strcpy(guestName, temp);
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
            shoppingMenu();
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