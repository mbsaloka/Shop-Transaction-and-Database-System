#define FILE_NAME "database.csv"
FILE *inp, *outp;

void renderData() {
    inp = fopen(FILE_NAME, "r");

    if (inp == NULL) {
        puts("File failed to open.");
        return;
    }

    printBold("DATA MAHASISWA\n");

    char line[1000];
    char *word, *nama, *NRP, *jurusan;
    const char *delimiter = ",";

    printBold("Nama\t| NRP\t| Jurusan\n");

    fgets(line, sizeof(line), inp);
    while (fgets(line, sizeof(line), inp) != NULL) {
        nama = strtok(line, delimiter);
        NRP = strtok(NULL, delimiter);
        jurusan = strtok(NULL, delimiter);
        printf("%s\t| %s\t| %s", nama, NRP, jurusan);
    }

    fclose(inp);
}

void inputData() {
    char nama[100], NRP[100], jurusan[100];

    printBold("MASUKKAN DATA MAHASISWA\n");
    printf("Nama: ");
    scanf("%s", &nama);
    printf("NRP: ");
    scanf("%s", &NRP);
    printf("Jurusan: ");
    scanf("%s", &jurusan);

    outp = fopen(FILE_NAME, "a");
    fprintf(outp, "%s,%s,%s\n", nama, NRP, jurusan);
    fclose(outp);
}