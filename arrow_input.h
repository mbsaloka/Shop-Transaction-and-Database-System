int chooseOption(char *option[], int length) {
    char *arrow = "\x1b[1m\x1b[94m> ";
    char *redArrow = "\x1b[1m\x1b[91m> ";
    char *noEffect = "\x1b[0m";
    char *hiddenCursor = "\e[?25l";
    char *visibleCursor = "\e[?25h";
    for (int i = 0; i < length; i++) {
        printf("  %s\n", option[i]);
    }
    printf("%s", hiddenCursor);
    printf("\033[%dA\r", length);
    printf("%s", arrow);
    printf("%s%s", option[0], noEffect);
    int code = 0;
    int input, prev;
    do {
        prev = input;
        input = getch();

        if ((prev == '\0' || prev == 224) && input == 'P') {  // down
            printf("\r  %s%s", noEffect, option[code]);
            code++;
            if (code >= length) {
                code = 0;
                printf("\r\033[%dA%s%s%s", length - 1, arrow, option[code], noEffect);
            } else {
                if (code == length - 1) {
                    printf("\r\033[B%s%s%s", redArrow, option[code], noEffect);
                } else {
                    printf("\r\033[B%s%s%s", arrow, option[code], noEffect);
                }
            }
        } else if ((prev == '\0' || prev == 224) && input == 'H') {  // up
            printf("\r  %s%s", noEffect, option[code]);
            code--;
            if (code < 0) {
                code = length - 1;
                printf("\r\033[%dB%s%s%s", length - 1, redArrow, option[code], noEffect);
            } else {
                if (code == length - 1) {
                    printf("\r\033[A%s%s%s", redArrow, option[code], noEffect);
                } else {
                    printf("\r\033[A%s%s%s", arrow, option[code], noEffect);
                }
            }
        } else if (input == 3) {
            printf("%s", visibleCursor);
            exit(0);
        } else if (input == 27) {
            printf("%s", visibleCursor);
            return length - 1;
        }
    } while (input != 13);
    printf("%s", visibleCursor);
    return code;
}

int printLineItem(void *item) {
    Item *i = (Item *)item;
    char space[] = "    ";
    space[3] = (i->ID < 10) ? ' ' : '\0';
    char name2[101];
    int COL_MAX = 21;
    int COL_MIN = 14;
    strcpy(name2, i->name);
    if (strlen(name2) > COL_MAX) {
        name2[COL_MAX - 2] = '.';
        name2[COL_MAX - 1] = '.';
        name2[COL_MAX] = '\0';
    }

    while (strlen(name2) <= COL_MIN) {
        strcat(name2, " ");
    }
    printf("%d%s|\t ", i->ID, space);
    printf("%s\t| ", name2);
    printf("%d\t| ", i->price);
    printf("%d\r", i->stock);
    return ((Item *)item)->ID;
}

int printLineMember(void *member) {
    Member *i = (Member *)member;
    char space[] = "    ";
    space[3] = (i->ID < 10) ? ' ' : '\0';
    char name2[101];
    int COL_MAX = 21;
    int COL_MIN = 14;
    strcpy(name2, i->name);
    if (strlen(name2) > COL_MAX) {
        name2[COL_MAX - 2] = '.';
        name2[COL_MAX - 1] = '.';
        name2[COL_MAX] = '\0';
    }

    while (strlen(name2) <= COL_MIN) {
        strcat(name2, " ");
    }
    printf("%d%s|\t ", i->ID, space);
    printf("%s\t| ", name2);
    printf("%s\t| ", i->phoneNum);
    printf("%s\t| ", i->address);
    printf("%s %s | ", i->registDate, i->registTime);
    printf("%s\t| ", i->username);
    printf("%s\t\t| ", i->password);
    printMoney(i->balance);

    return ((Member *)member)->ID;
}

int printLineTransaction(void *transaction) {
    Transaction *i = (Transaction *)transaction;
    char space[] = "    ";
    space[3] = (i->ID < 10) ? ' ' : '\0';
    char name2[101];
    int COL_MAX = 21;
    int COL_MIN = 14;
    strcpy(name2, i->name);
    if (strlen(name2) > COL_MAX) {
        name2[COL_MAX - 2] = '.';
        name2[COL_MAX - 1] = '.';
        name2[COL_MAX] = '\0';
    }

    while (strlen(name2) <= COL_MIN) {
        strcat(name2, " ");
    }

    printf("%d%s|\t ", i->ID, space);
    printf("%s %s\t| ", i->transactionDate, i->transactionTime);
    printf("%s\t| ", name2);
    (i->memberID == 0) ? printf("guest     | ") : printf("%d\t    | ", i->memberID);
    printf("Rp%s\r", strMoney(i->totalPrice));
    return ((Transaction *)transaction)->ID;
}

int printLineCart(int idx) {
    char name[101], space[] = "    ";
    int COL_MAX = 14;
    int COL_MIN = 6;

    strcpy(name, cart[idx].name);
    if (strlen(name) > COL_MAX) {
        name[COL_MAX - 2] = '.';
        name[COL_MAX - 1] = '.';
        name[COL_MAX] = '\0';
    }
    if (strlen(name) < COL_MIN) {
        strcat(name, "    ");
    }
    space[3] = (cart[idx].ID < 10) ? ' ' : '\0';

    printf("%d%s|\t %s\t| %d\t| ", cart[idx].ID, space, name, cart[idx].amount);
    printMoney(cart[idx].price * cart[idx].amount);
    printf("\r");

    return cart[idx].ID;
}

int chooseData(void *data, size_t dataSize, int totalIndex, int (*printLineData)(void *)) {
    char *highlight = "\x1b[1m\033[38;5;208m";
    char *greenHighlight = "\x1b[1m\x1b[92m";
    char *noEffect = "\x1b[0m";
    char *hiddenCursor = "\e[?25l";
    char *visibleCursor = "\e[?25h";
    void *currentData = (char *)data + (dataSize * 0);

    int code = 0, ID;
    int input, prev;

    if (totalIndex == 0) {
        printf("%s", greenHighlight);
        printf("\rMasukkan Filter : \x1b[90m(enter untuk menerapkan filter)\033[31D");
        printf("%s%s", noEffect, visibleCursor);
        ID = (getEnter() == 13) ? -2 : -1;
    } else {
        printf("%s", hiddenCursor);
        printf("\033[%dA\r", totalIndex + 1);
        printf("%s", highlight);
        ID = printLineData(currentData);
        printf("%s", noEffect);
    }

    while (input != 13 && totalIndex > 0) {
        prev = input;
        input = getch();

        if (((prev == '\0' || prev == 224) && input == 'P') || ((prev == '\0' || prev == 224) && input == 'H')) {
            printf("\r%s", noEffect);
            if (ID == -2) {
                printf("Masukkan Filter : ");
                for (int i = 0; i < 31; i++) putchar(' ');
                printf("%s", hiddenCursor);
            } else {
                printLineData(currentData);
            }
            if (input == 'P') {
                code++;
                if (code == totalIndex) {
                    code++;
                    printf("\r\033[2B");
                } else if (code > totalIndex) {
                    code = 0;
                    printf("\r\033[%dA", totalIndex + 1);
                } else {
                    printf("\r\033[B");
                }
            } else if (input == 'H') {
                code--;
                if (code < 0) {
                    code = totalIndex + 1;
                    printf("\r\033[%dB", totalIndex + 1);
                } else if (code == totalIndex) {
                    code--;
                    printf("\r\033[2A");
                } else {
                    printf("\r\033[A");
                }
            }
            currentData = (char *)data + (dataSize * code);
            if (code < totalIndex) {
                printf("%s", highlight);
                ID = printLineData(currentData);
                printf("%s\r", noEffect);
            } else {
                printf("%s", greenHighlight);
                printf("Masukkan Filter : \x1b[90m(enter untuk menerapkan filter)\033[31D");
                printf("%s%s", noEffect, visibleCursor);
                ID = -2;
            }
        } else if (input == 3) {
            printf("%s", visibleCursor);
            exit(0);
        } else if (input == 27) {
            printf("%s", visibleCursor);
            return -1;
        }
    }
    if (ID == -2) {
        for (int i = 0; i < 31; i++) putchar(' ');
        printf("\033[31D");
    } else {
        printf("\033[%dB", totalIndex - code + 2);
        clearRow();
        clearRow();
    }
    printf("%s", visibleCursor);
    return ID;
}

int chooseCart() {
    char *highlight = "\x1b[1m\033[38;5;208m";
    char *blueArrow = "\x1b[1m\x1b[94m> ";
    char *redArrow = "\x1b[1m\x1b[91m> ";
    char *noEffect = "\x1b[0m";
    char *hiddenCursor = "\e[?25l";
    char *visibleCursor = "\e[?25h";

    char *option[] = {
        "Selesai & Bayar",
        "Kembali ke Menu Belanja",
    };
    printf("%s", hiddenCursor);

    printBold("Ingin melakukan apa?\n");
    printf("  Selesai & Bayar\n");
    printf("  Kembali ke Menu Belanja");

    int code = 0, ID;
    int input, prev;

    if (numCart == 0) {
        printf("\n");
        clearRow();
        clearRow();
        clearRow();
        printf("%sKembali ke Menu Belanja", blueArrow);
        printf("%s", noEffect);
        ID = getEnter();
        return -1;
    } else {
        printf("\033[%dA\r", numCart + 4);
        printf("%s", highlight);
        printLineCart(0);
        printf("%s", noEffect);
    }

    while (input != 13 && numCart > 0) {
        prev = input;
        input = getch();

        if (((prev == '\0' || prev == 224) && input == 'P') || ((prev == '\0' || prev == 224) && input == 'H')) {
            printf("\r%s", noEffect);
            if (ID == -2) {
                printf("  Selesai & Bayar");
            } else if (ID == -3) {
                printf("  Kembali ke Menu Belanja");
            } else {
                printLineCart(code);
            }
            if (input == 'P') {
                code++;
                if (code == numCart) {
                    code = numCart + 3;
                    printf("\r\033[4B");
                } else if (code == numCart + 5) {
                    code = 0;
                    printf("\r\033[%dA", numCart + 4);
                } else {
                    printf("\r\033[B");
                }
            } else if (input == 'H') {
                code--;
                if (code < 0) {
                    code = numCart + 4;
                    printf("\r\033[%dB", numCart + 4);
                } else if (code == numCart + 2) {
                    code = numCart - 1;
                    printf("\r\033[4A");
                } else {
                    printf("\r\033[A");
                }
            }
            if (code < numCart) {
                printf("%s", highlight);
                ID = printLineCart(code);
                printf("\r%s", noEffect);
            } else if (code == numCart + 3) {
                printf("%s", blueArrow);
                printf("Selesai & Bayar");
                printf("%s", noEffect);
                ID = -2;
            } else if (code == numCart + 4) {
                printf("%s", redArrow);
                printf("Kembali ke Menu Belanja");
                printf("%s", noEffect);
                ID = -3;
            }
        } else if (input == 3) {
            printf("%s", visibleCursor);
            exit(0);
        } else if (input == 27) {
            printf("%s", visibleCursor);
            return -1;
        }
    }
    if (ID == -2) {
        clearScreen();
    } else if (ID == -3) {
        clearRow();
        clearRow();
    } else {
        printf("\033[%dB", numCart - code + 4);
        clearRow();
        clearRow();
    }
    printf("%s", visibleCursor);
    return ID;
}