#define BLUE "\x1b[1m\x1b[94m"
#define RED "\x1b[1m\x1b[91m"
#define ORANGE "\x1b[1m\033[38;5;208m"
#define GREEN "\x1b[1m\033[92m"
#define GRAY "\x1b[90m"
#define YELLOW "\x1b[33m"
#define NO_EFFECT "\x1b[0m"
#define HIDE_CURSOR "\e[?25l"
#define SHOW_CURSOR "\e[?25h"
#define CURSOR_UP(n) printf("\033[%dA\r", (n))
#define CURSOR_DOWN(n) printf("\033[%dB\r", (n))
#define CURSOR_LEFT(n) printf("\033[%dD", (n))
#define CURSOR_RIGHT(n) printf("\033[%dC", (n))
#define CLEAR_ROW(n) ({for (int i = 0; i < (n); i++) printf("\033[A\033[2K\r"); })
#define clearScreen() printf("\x1b[2J\x1b[H")
#define printBold(s) printf("\x1b[1m%s\x1b[0m", (s))

void toLower(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] += 32;
        }
    }
}

void comingSoon() {
    printBold("Coming Soon\n");
    printf("Text to erase****************************\n");
    int i = 3;
    while (i >= 0) {  // 3 second countdown
        printf("\033[A\33[2KT\rKembali ke menu dalam %d...\n", i);
        i--;
        sleep(1);
    }
}

void printMoney(int money) {
    char str[100];
    snprintf(str, sizeof(str), "%d", money);
    int n = strlen(str);
    int j = 0;
    for (int i = n - 1; i > 0; i--) {
        j++;
        if (j % 3 == 0) {
            char str2[100];
            strcpy(str2, str);
            char *temp = str2 + i;
            str[i] = '.';
            str[i + 1] = '\0';
            strcat(str, temp);
        }
    }
    printf("%sRp%s%s", YELLOW, str, NO_EFFECT);
}

char *strMoney(int money) {
    static char str[50];
    sprintf(str, "%d", money);
    int n = strlen(str);
    int j = 0;
    for (int i = n - 1; i > 0; i--) {
        j++;
        if (j % 3 == 0) {
            char str2[100];
            strcpy(str2, str);
            char *temp = str2 + i;
            str[i] = '.';
            str[i + 1] = '\0';
            strcat(str, temp);
        }
    }
    return str;
}

/*
Activate ANSI escape sequences in CMD
reg add HKCU\Console /v VirtualTerminalLevel /t REG_DWORD /d 1

Deactivate ANSI
reg delete HKCU\Console /v VirtualTerminalLevel /f

Hapus Satu Baris
\033[A\33[2K\r
\033[A : menggerakkan kursor satu baris ke atas
\033[B : menggerakkan kursor satu baris ke bawah
\33[2K : hapus baris saat ini dan di bawahnya
\r     : menggerakkan kursor ke awal baris

Hapus baris tertentu sampai akhir layar
\033[J

Kode Pengendali ANSI
\x1b[0m : normal text
\x1b[1m : bold
\x1b[4m : underline
\x1b[2J\x1b[H : clear screen

\x1b[32;43m : contoh penggabungan, hijau dengan latar belakang kuning.

Warna Teks:
\x1b[30m - Hitam
\x1b[31m - Merah
\x1b[32m - Hijau
\x1b[33m - Kuning
\x1b[34m - Biru
\x1b[35m - Magenta (Ungu)
\x1b[36m - Cyan (Biru Muda)
\x1b[37m - Putih
\x1b[90m - Abu-Abu Terang
\x1b[91m - Merah Terang
\x1b[92m - Hijau Terang
\x1b[93m - Kuning Terang
\x1b[94m - Biru Terang
\x1b[95m - Magenta Terang
\x1b[96m - Cyan Terang
\x1b[97m - Putih Terang
\x1b[38;5;206m - Pink

Warna Latar Belakang
\x1b[40m - Hitam
\x1b[41m - Merah
\x1b[42m - Hijau
\x1b[43m - Kuning
\x1b[44m - Biru
\x1b[45m - Magenta (Ungu)
\x1b[46m - Cyan (Biru Muda)
\x1b[47m - Putih
\x1b[100m - Abu-Abu Terang
\x1b[101m - Merah Terang
\x1b[102m - Hijau Terang
\x1b[103m - Kuning Terang
\x1b[104m - Biru Terang
\x1b[105m - Magenta Terang
\x1b[106m - Cyan Terang
\x1b[107m - Putih Terang

Arrow Key Code
\0H - UP
\0P - DOWN
\0K - LEFT
\0M - RIGHT

Hidden Cursor
\e[?25l - Hidden
\e[?25h - Visible



*/