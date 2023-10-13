void clearScreen() {
    printf("\x1b[2J\x1b[H");
}

void printBold(char *s) {
    printf("\x1b[1m%s\x1b[0m", s);
}

/*
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
*/