#define FILE_ITEM "database/db_item.bin"
#define FILE_TEMP "database/temp.bin"
#define FILE_TEMP_SHOPPING "database/temp_shopping.csv"
#define FILE_TRANSACTION "database/db_transaction_log.csv"
typedef struct item_s {
    int ID, price, stock;
    char name[101];
} Item;

Item item[1000];
int numItem;
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