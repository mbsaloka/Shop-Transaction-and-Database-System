#include <stdio.h>
#include <stdlib.h>
#define FILE_MEMBER "database/db_member.bin"
#define FILE_TEMP "database/temp.bin"

typedef struct member_s {
    int ID, balance;
    char username[101], password[101];
    char name[101], noTelp[15], address[101], dateRegist[15], timeRegist[15];
} Member;

Member member[1000];
int numMember;

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

void inputMember() {
    int idx = numMember;
    printf("TAMBAHKAN MEMBER BARU\n");

    member[idx].ID = (idx == 0) ? 1 : member[idx - 1].ID + 1;
    printf("ID : %d\n", member[idx].ID);

    printf("Username : ");
    scanf("%s", member[idx].username);
    printf("Password : ");
    scanf("%s", member[idx].password);

    printf("Nama : ");
    fflush(stdin);
    gets(member[idx].name);
    printf("No Telp : ");
    scanf("%s", member[idx].noTelp);
    printf("Alamat : ");
    fflush(stdin);
    gets(member[idx].address);
    member[idx].balance = 100000;
}

void showMember() {
    int n = numMember;
    for (int i = 0; i < n; i++) {
        printf("ID : %d\n", member[i].ID);
        printf("Username : %s\n", member[i].username);
        printf("Password : %s\n", member[i].password);
        printf("Nama : %s\n", member[i].name);
        printf("No Telp : %d\n", member[i].noTelp);
        printf("Alamat : %d\n", member[i].address);
        printf("Saldo : %d\n", member[i].balance);
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

int getMemberID(void *member) {
    return ((Member *)member)->ID;
}

int main() {
    int code = 1;
    importFromDb(member, sizeof(Member), &numMember, FILE_MEMBER);
    printf("NUM MEMBER : %d\n", numMember);

    while (code != 0) {
        printf("(1) Tampilkan Member\n");
        printf("(2) Tambahkan Member\n");
        printf("(3) Hapus Member\n");
        scanf("%d", &code);
        system("cls");
        switch (code) {
        case 1:
            showMember();
            break;
        case 2:
            inputMember();
            addToDb(&member[numMember], sizeof(Member), FILE_MEMBER);
            numMember++;
            break;
        case 3:
            int removeID;
            printf("ID Member yang mau dihapus : ");
            scanf("%d", &removeID);
            removeData(member, sizeof(Member), removeID, &numMember, FILE_MEMBER, getMemberID);
            importFromDb(member, sizeof(Member), &numMember, FILE_MEMBER);
            break;
        }
    }
}