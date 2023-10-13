#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char name[50];
    int qty_cpu, qty_monitor, qty_keyboard, qty_mouse, qty_printer; // deklarasi variable untuk qty per barang
    int ttl_cpu, ttl_monitor, ttl_keyboard, ttl_mouse, ttl_printer; // deklarasi variable untuk total per item
    int grand_total;

    printf("-------------------------------- \n");
    printf("== SELAMAT DATANG DI TOKO ABC == \n");
    printf("-------------------------------- \n");

    printf("Masukkan Nama Anda : ");
    fgets(name, 50, stdin); // isi variabel name

    printf("\nHai %s\n", name);
    printf("Daftar pemesanan (0 jika tidak ingin memesan) :\n");

    printf("CPU \t\t Rp. 2.000.000  \t: ");
    scanf("%d", &qty_cpu);

    printf("Monitor \t Rp. 2.400.000 \t\t: ");
    scanf("%d", &qty_monitor);

    printf("Keyboard \t Rp. 200.000 \t\t: ");
    scanf("%d", &qty_keyboard);

    printf("Mouse \t\t Rp. 150.000 \t\t: ");
    scanf("%d", &qty_mouse);

    printf("Printer \t Rp. 850.000 \t\t: ");
    scanf("%d", &qty_printer);

    printf("\n\n ----------  Rincian Pembelian ---------------\n");

    ttl_cpu = 2000000 * qty_cpu;
    ttl_monitor = 2400000 * qty_monitor;
    ttl_keyboard = 200000 * qty_keyboard;
    ttl_printer = 150000;
    ttl_mouse = 150000 * qty_mouse;
    ttl_printer = 850000 * qty_printer;

    grand_total = ttl_cpu + ttl_monitor + ttl_keyboard + ttl_mouse + ttl_printer;

    printf("CPU\t\t: %d = Rp. %d \n", qty_cpu, ttl_cpu);
    printf("Monitor\t\t: %d = Rp. %d \n" , qty_monitor, ttl_monitor);
    printf("Keyboard\t: %d = Rp. %d \n" , qty_keyboard, ttl_keyboard);
    printf("Mouse\t\t: %d = Rp. %d \n" , qty_mouse, ttl_mouse);
    printf("Printer\t\t: %d = Rp. %d \n" , qty_printer, ttl_printer);

    printf("\nTotal \t\t: Rp. %d\n\n", grand_total);
    printf("Terima kasih telah berbelanja di Toko Kami.....\n");

    return 0;
}