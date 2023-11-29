void addItemToCart() {
    int ID, price, stock;
    char name[101];
    clearScreen();

    char filter[101] = "\0";
    while (1) {
        clearScreen();
        showItem(filter);
        printBold("Saldo : ");
        printMoney(onlineUser.balance);
        printf("\nMasukkan Filter : ");
        int ID = chooseData(tempFilterItem, sizeof(Item), numTempFilterItem, printLineItem);
        if (ID == -2) {
            printf("\r%sMasukkan Filter : %-31.s", GREEN);
            CURSOR_LEFT(31);
            printf("%s(ketik di sini)%s", GRAY, NO_EFFECT);
            CURSOR_LEFT(15);
            getFilter(filter);
        } else if (ID == -1) {
            if (numTempFilterItem < numItem) {
                filter[0] = '\0';
            } else {
                break;
            }
        } else {
            int idx;
            for (int i = 0; i < numItem; i++) {
                if (item[i].ID == ID) {
                    idx = i;
                    break;
                }
            }
            if (item[idx].stock <= 0) {
                printf("Stok produk yang Anda pilih sedang kosong.");
                sleep(1);
                return;
            }
            printBold("Saldo : ");
            printMoney(onlineUser.balance);
            int amount = 0;

            for (int i = 0; i < numItem; i++) {
                if (ID == item[i].ID) {
                    strcpy(name, item[i].name);
                    price = item[i].price;
                    stock = item[i].stock;
                    if (stock <= 0) {
                        printf("Stok produk yang Anda pilih sedang kosong.");
                        sleep(1);
                        return;
                    }
                    break;
                }
            }

            printBold("\n\nDetail Produk\n");
            printf("Nama : %s\n", item[idx].name);
            printf("Harga : ");
            printMoney(item[idx].price);
            printf("\nStok : %d\n", item[idx].stock);

            printBold("\nMasukkan jumlah yang ingin dibeli!\n");
            while (1) {
                printf("Jumlah : ");
                amount = getNumINT();
                if (amount == -1) return;
                if (amount > stock) {
                    printf("\nJumlah yang dipilih tidak boleh melebihi stok produk.\n");
                    printf("Tolong masukkan kembali jumlah yang sesuai.\n");
                    pause();
                } else if (amount == 0) {
                    printf("\nJumlah yang dipilih tidak boleh sama dengan 0.\n");
                    printf("Tolong masukkan kembali jumlah yang sesuai.\n");
                    pause();
                } else {
                    int isListed = 0;
                    for (int i = 0; i < numCart; i++) {
                        if (ID == cart[i].ID) {
                            cart[i].amount += amount;
                            cart[i].stock -= amount;
                            isListed = 1;
                            break;
                        }
                    }
                    if (!isListed) {
                        cart[numCart].ID = item[idx].ID;
                        cart[numCart].price = item[idx].price;
                        cart[numCart].amount = amount;
                        cart[numCart].stock = item[idx].stock - amount;
                        strcpy(cart[numCart].name, item[idx].name);
                        numCart++;
                    }
                    item[idx].stock -= amount;
                    printf("\nProduk %s sejumlah %d berhasil ditambahkan ke keranjang.\n", item[idx].name, amount);
                    sleep(1);
                    return;
                }
                CLEAR_ROW(4);
            }
        }
    }
}

int checkoutCart() {
    int total = 0;
    for (int i = 0; i < numCart; i++) {
        total += cart[i].price * cart[i].amount;
    }

    if (numCart == 0) {
        printf("Keranjang Anda kosong.\n");
        sleep(1);
    } else if (onlineUser.balance < total) {
        printf("Saldo kurang! Hapus beberapa barang dari keranjang.\n");
        sleep(1);
    } else {
        onlineUser.balance -= total;

        for (int i = 0; i < numMember; i++) {
            if (onlineUser.ID == member[i].ID) {
                member[i].balance = onlineUser.balance;
                updateData(member, sizeof(Member), numMember, FILE_MEMBER);
                break;
            }
        }
        updateData(item, sizeof(Item), numItem, FILE_ITEM);

        addTransactionLog(total);
        saveReceipt();
        numCart = 0;
        printf("Transaksi Sukses!\n");
        sleep(1);
        return 1;
    }
    return 0;
}

void openCart() {
    while (1) {
        clearScreen();
        printBold("Saldo : ");
        printMoney(onlineUser.balance);
        showBill();
        int ID = chooseCart();
        if (ID == -2) {
            if (checkoutCart()) return;
        } else if (ID == -3) {
            return;
        } else if (ID == -1) {
            return;
        } else {
            int code, idx, cartIdx;
            for (int i = 0; i < numItem; i++) {
                if (item[i].ID == ID) {
                    idx = i;
                    break;
                }
            }
            for (int i = 0; i < numCart; i++) {
                if (cart[i].ID == ID) {
                    cartIdx = i;
                    break;
                }
            }
            printf("HAPUS ATAU UBAH JUMLAH BARANG\n");
            char* option[] = {
                "Hapus Barang dari Keranjang",
                "Ubah Jumlah Barang         ",
                "Kembali",
            };
            int lengthOption = sizeof(option) / sizeof(option[0]);
            code = chooseOption(option, lengthOption);
            switch (code) {
            case 0:
                int isRemoved = 0;
                for (int i = 0; i < numCart; i++) {
                    if (ID == cart[i].ID) {
                        item[idx].stock += cart[i].amount;
                        isRemoved = 1;
                        numCart--;
                    }
                    if (isRemoved) cart[i] = cart[i + 1];
                }
                clearScreen();
                printf("Barang berhasil dihapus dari keranjang.\n");
                sleep(1);
                break;
            case 1:
                printBold("\n\n\nDetail Produk\n");
                printf("Nama : %s\n", item[idx].name);
                printf("Harga : ");
                printMoney(item[idx].price);
                printf("\nStok : %d\n", item[idx].stock + cart[cartIdx].amount);

                printBold("\nMasukkan jumlah yang ingin dibeli!\n");
                while (1) {
                    printf("Jumlah : ");
                    int amount = getNumINT();
                    if (amount == -1) break;
                    if (amount > item[idx].stock + cart[cartIdx].amount) {
                        printf("\nJumlah yang dipilih tidak boleh melebihi stok produk.\n");
                        printf("Tolong masukkan kembali jumlah yang sesuai.\n");
                        pause();
                    } else if (amount == 0) {
                        printf("\nJumlah yang dipilih tidak boleh sama dengan 0.\n");
                        printf("Tolong masukkan kembali jumlah yang sesuai.\n");
                        pause();
                    } else {
                        item[idx].stock += cart[cartIdx].amount;
                        cart[cartIdx].amount = amount;
                        item[idx].stock -= amount;
                        cart[cartIdx].stock = item[idx].stock;

                        printf("\nPerubahan berhasil dilakukan.\n");
                        sleep(1);
                        break;
                    }
                    CLEAR_ROW(4);
                }
                break;
            case 2:
                break;
            }
        }
    }
}
void shoppingMenu() {
    int code;
    char* option[] = {
        "Masukkan Filter   ",
        "Pilih Produk",
        "Lihat Keranjang (Bayar)",
        "Kembali ke Menu Utama",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    char filter[101] = "\0";
    do {
        clearScreen();
        showItem(filter);
        printBold("Saldo : ");
        printMoney(onlineUser.balance);
        printBold("\nIngin melakukan apa?\n");

        code = chooseOption(option, lengthOption);
        switch (code) {
        case 0:
            printf("\r%s> Masukkan Filter : %s(ketik di sini)%s", GREEN, GRAY, NO_EFFECT);
            CURSOR_LEFT(15);
            getFilter(filter);
            break;
        case 1:
            addItemToCart();
            break;
        case 2:
            clearScreen();
            openCart();
            break;
        case 3:
            clearScreen();
            if (filter[0] != '\0') {
                filter[0] = '\0';
                code = 0;
                break;
            }
            printf("Jika keluar maka keranjang akan dikosongkan.\nYakin ingin keluar? (Y/N) ");
            if (getYesNo() == 'Y') {
                clearScreen();
                numCart = 0;
                importFromDb(item, sizeof(Item), &numItem, FILE_ITEM);
                return;
            } else {
                code = -1;
            }
            break;
        }
    } while (code != lengthOption - 1);
}