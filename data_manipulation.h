#define FILE_ITEM "database/db_item.bin"
#define FILE_MEMBER "database/db_member.bin"
#define FILE_TEMP "database/temp.bin"
#define FILE_TRANSACTION "database/db_transaction_log.bin"

typedef struct item_s {
    int ID, price, stock;
    char name[101];
    struct item_s *next;
} Item;

typedef struct member_s {
    int ID, balance;
    char username[101], password[101];
    char name[101], phoneNum[20], address[101];
    char registDate[15], registTime[15];
    struct member_s *next;
} Member;

typedef struct cart_s {
    int ID, price, amount, stock;
    char name[101];
    struct cart_s *next;
} Cart;

typedef struct transaction_s {
    int ID, memberID, totalPrice;
    char name[101], transactionDate[15], transactionTime[15];
    struct transaction_s *next;
} Transaction;

Item *item = NULL, *tempFilterItem = NULL;
Member *member = NULL, onlineUser, *tempFilterMember = NULL;
Cart *cart = NULL;
Transaction *transaction = NULL, *tempFilterTransaction = NULL;
int numItem, numMember, numCart, numTransaction;
int numTempFilterItem, numTempFilterMember, numTempFilterTransaction;

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

    fread(data, dataSize, *n, inp);

    fclose(inp);
}

void copyData(char *src, char *dest) {
    FILE *inp, *outp;
    inp = fopen(src, "rb");
    outp = fopen(dest, "wb");
    char buffer[1001];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), inp)) > 0) {
        fwrite(buffer, 1, bytesRead, outp);
    }
    fclose(inp);
    fclose(outp);
}

void *getItemNext(void *data) {
    return ((Item *)data)->next;
}

void *getMemberNext(void *data) {
    return ((Member *)data)->next;
}

void updateData(void *data, size_t dataSize, char *fileName, void *(*getNext)(void *)) {
    while (data != NULL) {
        addToDb(data, dataSize, FILE_TEMP);
        data = getNext(data);
    }
    copyData(FILE_TEMP, fileName);
    remove(FILE_TEMP);
}
