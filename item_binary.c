#include <stdio.h>
#include <stdlib.h>
#define FILE_ITEM "database/db_item.bin"
#define FILE_TEMP "database/temp.bin"

typedef struct item_s {
    int ID, price, stock;
    char name[101];
} Item;

void addToDb(void *data, size_t dataSize, char *fileName) {
    FILE *outp;
    outp = fopen(fileName, "ab");
    fwrite(data, dataSize, 1, outp);
    fclose(outp);
}

void importFromDb(void *data, size_t dataSize, int *n, char *fileName) {
    FILE *inp;
    inp = fopen(fileName, "rb");
    if (inp == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(inp, 0, SEEK_END);
    int fileSize = ftell(inp);
    *n = fileSize / dataSize;

    rewind(inp);

    const int maxData = 1000;
    *n = (*n > maxData) ? maxData : *n;

    fread(data, dataSize, *n, inp);

    fclose(inp);
}

void inputItem(Item *item, int i) {
    printf("TAMBAHKAN BARANG BARU\n");
    item[i].ID = (i == 0) ? 1 : item[i - 1].ID + 1;
    printf("ID : %d\n", item[i].ID);
    printf("Nama Barang : ");
    fflush(stdin);
    gets(item[i].name);
    printf("Harga : ");
    scanf("%d", &item[i].price);
    printf("Stok : ");
    scanf("%d", &item[i].stock);
}

void showItem(Item *item, int n) {
    for (int i = 0; i < n; i++) {
        printf("ID : %d\n", item[i].ID);
        printf("Nama Barang : %s\n", item[i].name);
        printf("Harga : %d\n", item[i].price);
        printf("Stok : %d\n", item[i].stock);
        printf("\n");
    }
}

void removeData(void *data, size_t dataSize, int removeID, int *totalIndex, char *fileName, int (*getID)(void *)) {
    int n = *totalIndex;
    for (int i = 0; i < n; i++) {
        void *currentData = (char *)data + (i * dataSize);
        int currentID = getID(currentData);
        if (currentID == removeID) {
            (*totalIndex)--;
        } else {
            addToDb(currentData, dataSize, FILE_TEMP);
        }
    }
    if (n == *totalIndex) {
        printf("ID tidak ditemukan.\n");
        system("pause");
    } else {
        system("pause");
        FILE *inp, *outp;
        inp = fopen(FILE_TEMP, "rb");
        outp = fopen(fileName, "wb");
        char buffer[1001];
        size_t bytesRead;
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), inp)) > 0) {
            fwrite(buffer, 1, bytesRead, outp);
        }
        fclose(inp);
        fclose(outp);
    }
    remove(FILE_TEMP);
}

int getItemID(void *item) {
    return ((Item *)item)->ID;
}

int main() {
    Item item[1000];
    int numItem;
    int code = 1;
    importFromDb(item, sizeof(Item), &numItem, FILE_ITEM);
    printf("NUM ITEM : %d\n", numItem);

    while (code != 0) {
        printf("(1) Tampilkan Item\n");
        printf("(2) Tambahkan Item\n");
        printf("(3) Hapus Item\n");
        scanf("%d", &code);
        system("cls");
        switch (code) {
        case 1:
            showItem(item, numItem);
            break;
        case 2:
            inputItem(item, numItem);
            addToDb(&item[numItem], sizeof(Item), FILE_ITEM);
            numItem++;
            break;
        case 3:
            int removeID;
            printf("ID Item yang mau dihapus : ");
            scanf("%d", &removeID);
            removeData(item, sizeof(Item), removeID, &numItem, FILE_ITEM, getItemID);
            importFromDb(item, sizeof(Item), &numItem, FILE_ITEM);
            break;
        }
    }
}