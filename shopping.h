void addItemToCart() {
    int ID, price, stock;
    char name[101];
    clearScreen();
    showItem("");
    printBold("Saldo : ");
    printMoney(onlineUser.balance);
    printBold("\nMasukkan ID Barang yang ingin dibeli!\n");
    printf("ID : ");
    ID = getNumINT();
    if (ID == -1) return;
    int isFound = -1, amount = 0;

    for (int i = 0; i < numItem; i++) {
        if (ID == item[i].ID) {
            strcpy(name, item[i].name);
            price = item[i].price;
            stock = item[i].stock;
            isFound = i;
            if (stock <= 0) {
                printf("Stok produk yang Anda pilih sedang kosong.");
                sleep(1);
                return;
            }
            break;
        }
    }

    if (isFound == -1) {
        printf("ID %d tidak ada di dalam daftar.", ID);
        sleep(1);
        return;
    }

    printBold("\nDetail Produk\n");
    printf("Nama : %s\n", name);
    printf("Harga : ");
    printMoney(price);
    printf("\nStok : %d\n", stock);

    printBold("\nMasukkan jumlah yang ingin dibeli!\n");
    while (1) {
        printf("Jumlah : ");
        amount = getNumINT();
        if (amount == -1) return;
        if (amount > stock) {
            printf("Jumlah yang dipilih tidak boleh melebihi stok produk.\n");
            printf("Tolong masukkan kembali jumlah yang sesuai.\n");
            sleep(1);
        } else if (amount == 0) {
            printf("Jumlah yang dipilih tidak boleh sama dengan 0.\n");
            printf("Tolong masukkan kembali jumlah yang sesuai.\n");
            sleep(1);
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
                cart[numCart].ID = ID;
                cart[numCart].price = price;
                cart[numCart].amount = amount;
                cart[numCart].stock = stock - amount;
                strcpy(cart[numCart].name, name);
                numCart++;
            }
            item[isFound].stock -= amount;
            printf("\nProduk %s sejumlah %d berhasil ditambahkan ke keranjang.\n", name, amount);
            sleep(1);
            break;
        }
        for (int i = 0; i < 3; i++) clearRow();
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
    int code;
    char *option[] = {
        "(0) Kembali ke Menu Belanja",
        "(1) Hapus Produk",
        "(2) Ubah Jumlah Produk",
        "(3) Selesai & Bayar",
    };
    int lengthOption = sizeof(option) / sizeof(option[0]);
    do {
        clearScreen();
        printBold("Saldo : ");
        printMoney(onlineUser.balance);
        showBill();
        printBold("\nIngin melakukan apa?\n");
        code = chooseOption(option, lengthOption);
        clearScreen();
        switch (code) {
        case 0:
            break;
        case 1:
            printBold("Saldo : ");
            printMoney(onlineUser.balance);
            showBill();
            printBold("\nMasukkan ID Barang yang ingin dihapus!\n");
            printf("ID : ");
            int ID = getNumINT();
            if (ID == -1) break;
            int isRemoved = 0;
            for (int i = 0; i < numItem; i++) {
                if (ID == item[i].ID) {
                    item[i].stock += cart[i].amount;
                    break;
                }
            }

            for (int i = 0; i < numCart; i++) {
                if (ID == cart[i].ID) {
                    isRemoved = 1;
                    numCart--;
                }
                if (isRemoved) cart[i] = cart[i + 1];
            }
            break;
        case 2:
            comingSoon();
            break;
        case 3:
            if (checkoutCart()) return;
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}

void shoppingMenu() {
    int code;
    char *option[] = {
        "(0) Kembali ke Menu Utama",
        "(1) Terapkan Filter",
        "(2) Pilih Produk",
        "(3) Lihat Keranjang (Bayar)",
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
        clearScreen();
        switch (code) {
        case 0:
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
        case 1:
            showItem("");
            printf("Masukkan Filter : ");
            getFilter(filter);
            if (strcmp(filter, "ESCAPE") == 0) {
                break;
            }
            break;
        case 2:
            addItemToCart();
            break;
        case 3:
            openCart();
            break;
        default:
            printBold("Input tidak valid.\n");
            sleep(1);
        }
    } while (code != 0);
}