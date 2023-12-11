#define FILE_ITEM "database/db_item.bin"
#define FILE_MEMBER "database/db_member.bin"
#define FILE_TEMP "database/temp.bin"
#define FILE_TRANSACTION "database/db_transaction_log.bin"

typedef struct item_s {
    int ID, price, stock;
    char name[101];
    struct item_s *next, *prev;
} Item;

typedef struct member_s {
    int ID, balance;
    char username[101], password[101];
    char name[101], phoneNum[20], address[101];
    char registDate[15], registTime[15];
    struct member_s *next, *prev;
} Member;

typedef struct cart_s {
    int ID, price, amount, stock;
    char name[101];
    struct cart_s *next, *prev;
} Cart;

typedef struct transaction_s {
    int ID, memberID, totalPrice;
    char name[101], transactionDate[15], transactionTime[15];
    struct transaction_s *next, *prev;
} Transaction;

Item *item = NULL, *filterItem = NULL;
Member *member = NULL, onlineUser, *filterMember = NULL;
Cart *cart = NULL;
Transaction *transaction = NULL, *filterTransaction = NULL;
int numItem, numMember, numCart, numTransaction;
int numFilterItem, numFilterMember, numFilterTransaction;

void importItemFromDb() {
    FILE *inp;
    inp = fopen(FILE_ITEM, "rb");
    if (inp == NULL) {
        perror("Error opening file");
        return;
    }

    Item data;
    Item *newItem = (Item *)malloc(sizeof(Item));
    numItem = 0;
    while (fread(&data, sizeof(Item), 1, inp) == 1) {
        if (item == NULL) {
            *item = data;
        } else {
            *newItem = data;
        }
        numItem++;
    }

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
    FILE *outp;
    outp = fopen(fileName, "wb");
    if (outp == NULL) {
        perror("Error opening file");
        return;
    }
    while (data != NULL) {
        printf("Updating %s\n", fileName);
        fwrite(data, dataSize, 1, outp);
        data = getNext(data);
    }
    fclose(outp);
}