#include <stdio.h>

int main() {
    char ID[100], namaBarang[100];
    // char harga[100], stok[100];
    int harga, stok;

    printf("TAMBAHKAN BARANG BARU\n");
    printf("ID: ");
    // scanf("%s", &ID);
    gets(ID);
    printf("Nama Barang: ");
    // scanf("%s", &namaBarang);
    gets(namaBarang);
    printf("Harga: ");
    scanf("%d", &harga);
    printf("Stok: ");
    scanf("%d", &stok);

    printf("=============\nHASIL\n");
    printf("ID : %s\n", ID);
    printf("Nama Barang : %s\n", namaBarang);
    printf("Harga : %d\n", harga);
    printf("Stok : %d\n", stok);
}