void clearScreen() {
    printf("\x1b[2J\x1b[H");
}

void bold(char *s) {
    printf("\x1b[1m%s\x1b[0m\n", s);
}

void underline(char *s) {
    printf("\x1b[4m%s\x1b[0m\n", s);
}

/*
ANSI
\x1b[0m : normal text
\x1b[1m : bold
\x1b[4m : underline
\x1b[2J\x1b[H : clear screen
*/