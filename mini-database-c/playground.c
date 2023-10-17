#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

int main() {
    printf("HALO 1\n");
    printf("HALO 2\n");
    printf("HALO 3\n");
    printf("HALO 4\n");
    printf("HALO 5\n");
    sleep(1);
    printf("\033[A\33[2K\r");
    sleep(1);
    printf("\033[A\33[2K\r");
    sleep(1);
    printf("\033[A\33[2K\r");
    sleep(1);
    printf("\033[A\33[2K\r");
    printf("HEHEHE\n");

    return 0;
}