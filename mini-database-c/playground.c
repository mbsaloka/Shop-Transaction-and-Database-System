#include <stdio.h>
#include <string.h>

char* GetString() {
    static char str[1000];
    char* t = "Ini adalah string yang dikembalikan dari fungsi";
    strcpy(str, t);

    return str;
}

int main() {
    char* result = GetString();

    // Gunakan string yang dikembalikan
    printf("String yang dikembalikan: %s\n", result);

    return 0;
}