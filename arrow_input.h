int downArrow(int a, int b) {
    return ((a == '\0' || a == 224) && b == 'P');
}

int upArrow(int a, int b) {
    return ((a == '\0' || a == 224) && b == 'H');
}

int chooseOption(char *option[], int length) {
    int code = 0;
    int input, prev;
    for (int i = 0; i < length; i++) {
        printf("  %s\n", option[i]);
    }
    printf("%s", HIDE_CURSOR);
    CURSOR_UP(length);
    printf("%s> %s%s", BLUE, option[0], NO_EFFECT);
    do {
        prev = input;
        input = getch();

        if (downArrow(prev, input) || upArrow(prev, input)) {
            printf("\r  %s", option[code]);
            (input == 'P') ? code++ : code--;
            if (code >= length) {
                code = 0;
                CURSOR_UP(length - 1);
            } else if (code < 0) {
                code = length - 1;
                CURSOR_DOWN(length - 1);
            } else {
                (input == 'P') ? CURSOR_DOWN(1) : CURSOR_UP(1);
            }
            printf("%s> ", (code == length - 1) ? RED : BLUE);
            printf("%s%s", option[code], NO_EFFECT);
        }

        if (input == 3) {
            printf("%s", SHOW_CURSOR);
            exit(0);
        } else if (input == 27) {
            printf("%s", SHOW_CURSOR);
            return length - 1;
        }
    } while (input != 13);
    printf("%s", SHOW_CURSOR);
    return code;
}

int printLineItem(void *item) {
    Item *i = (Item *)item;
    printf("%-5.d|\t %-22.22s | %-5.d | ", i->ID, i->name, i->stock);
    printMoney(i->price);
    printf("\r");
    return ((Item *)item)->ID;
}

int printLineMember(void *member) {
    Member *i = (Member *)member;
    printf("%-5.d|\t %-22.22s | %-13.13s | %-21.21s | %s %s | ", i->ID, i->name, i->phoneNum, i->address, i->registDate, i->registTime);
    printf("%-15.15s | %-13.13s | ", i->username, i->password);
    printMoney(i->balance);
    return ((Member *)member)->ID;
}

int printLineTransaction(void *transaction) {
    Transaction *i = (Transaction *)transaction;
    printf("%-5.d| %s %s | %-22.22s | ", i->ID, i->transactionDate, i->transactionTime, i->name);
    (i->memberID == 0) ? printf("guest     | ") : printf("%-10.d| ", i->memberID);
    printMoney(i->totalPrice);
    printf("\r");
    return ((Transaction *)transaction)->ID;
}

int printLineCart(int idx) {
    printf("%-5.d|\t %-14.14s\t| %d\t| ", cart[idx].ID, cart[idx].name, cart[idx].amount);
    printMoney(cart[idx].price * cart[idx].amount);
    return cart[idx].ID;
}

int chooseData(void *data, size_t dataSize, int totalIndex, int (*printLineData)(void *)) {
    void *currentData = (char *)data + (dataSize * 0);
    int code = 0, ID;
    int input, prev;

    if (totalIndex == 0) {
        printf("%s", GREEN);
        printf("\rMasukkan Filter : ");
        printf("%s(enter untuk menerapkan filter)", GRAY);
        CURSOR_LEFT(31);
        printf("%s", NO_EFFECT);
        ID = (getEnter() == 13) ? -2 : -1;
    } else {
        printf("%s", HIDE_CURSOR);
        CURSOR_UP(totalIndex + 1);
        printf("%s", ORANGE);
        ID = printLineData(currentData);
        printf("%s", NO_EFFECT);
    }

    while (input != 13 && totalIndex > 0) {
        prev = input;
        input = getch();

        if (downArrow(prev, input) || upArrow(prev, input)) {
            if (ID == -2) {
                printf("\rMasukkan Filter : %-31.s");
                printf("%s", HIDE_CURSOR);
            } else {
                printf("\r");
                printLineData(currentData);
            }

            if (input == 'P') {
                code++;
                if (code == totalIndex) {
                    code++;
                    CURSOR_DOWN(2);
                } else if (code > totalIndex) {
                    code = 0;
                    CURSOR_UP(totalIndex + 1);
                } else {
                    CURSOR_DOWN(1);
                }
            } else if (input == 'H') {
                code--;
                if (code == totalIndex) {
                    code--;
                    CURSOR_UP(2);
                } else if (code < 0) {
                    code = totalIndex + 1;
                    CURSOR_DOWN(totalIndex + 1);
                } else {
                    CURSOR_UP(1);
                }
            }

            if (code < totalIndex) {
                currentData = (char *)data + (dataSize * code);
                printf("%s", ORANGE);
                ID = printLineData(currentData);
                printf("%s\r", NO_EFFECT);
            } else {
                printf("%s", GREEN);
                printf("\rMasukkan Filter : ");
                printf("%s(enter untuk menerapkan filter)", GRAY);
                CURSOR_LEFT(31);
                printf("%s%s", NO_EFFECT, SHOW_CURSOR);
                ID = -2;
            }
        }

        if (input == 3) {
            printf("%s", SHOW_CURSOR);
            exit(0);
        } else if (input == 27) {
            printf("%s", SHOW_CURSOR);
            return -1;
        }
    }
    if (ID == -2) {
        printf("%-31.s");
        CURSOR_LEFT(31);
    } else {
        CURSOR_DOWN(totalIndex - code + 2);
        CLEAR_ROW(2);
    }
    printf("%s", SHOW_CURSOR);
    return ID;
}

int chooseCart() {
    int code = 0, ID;
    int input, prev;
    char *option[] = {
        "Selesai & Bayar",
        "Kembali ke Menu Belanja",
    };

    printf("%s", HIDE_CURSOR);
    printBold("Ingin melakukan apa?\n");
    printf("  %s\n  %s\n", option[0], option[1]);

    if (numCart == 0) {
        CLEAR_ROW(2);
        printf("%s> Kembali ke Menu Belanja%s", BLUE, NO_EFFECT);
        ID = getEnter();
        return -1;
    } else {
        CURSOR_UP(numCart + 5);
        printf("%s", ORANGE);
        printLineCart(0);
        printf("%s\r", NO_EFFECT);
    }

    while (input != 13 && numCart > 0) {
        prev = input;
        input = getch();

        if (downArrow(prev, input) || upArrow(prev, input)) {
            if (ID == -2) {
                printf("  %s", option[0]);
            } else if (ID == -3) {
                printf("  %s", option[1]);
            } else {
                printLineCart(code);
            }

            if (input == 'P') {
                code++;
                if (code == numCart) {
                    code = numCart + 3;
                    CURSOR_DOWN(4);
                } else if (code == numCart + 5) {
                    code = 0;
                    CURSOR_UP(numCart + 4);
                } else {
                    CURSOR_DOWN(1);
                }
            } else if (input == 'H') {
                code--;
                if (code < 0) {
                    code = numCart + 4;
                    CURSOR_DOWN(numCart + 4);
                } else if (code == numCart + 2) {
                    code = numCart - 1;
                    CURSOR_UP(4);
                } else {
                    CURSOR_UP(1);
                }
            }

            if (code < numCart) {
                printf("%s", ORANGE);
                ID = printLineCart(code);
                printf("%s\r", NO_EFFECT);
            } else if (code == numCart + 3) {
                printf("%s> %s%s\r", BLUE, option[0], NO_EFFECT);
                ID = -2;
            } else if (code == numCart + 4) {
                printf("%s> %s%s\r", RED, option[1], NO_EFFECT);
                ID = -3;
            }
        }

        if (input == 3) {
            printf("%s", SHOW_CURSOR);
            exit(0);
        } else if (input == 27) {
            printf("%s", SHOW_CURSOR);
            return -1;
        }
    }
    if (ID == -2) {
        clearScreen();
    } else if (ID == -3) {
        CLEAR_ROW(2);
    } else {
        CURSOR_DOWN(numCart - code + 4);
        CLEAR_ROW(2);
    }
    printf("%s", SHOW_CURSOR);
    return ID;
}