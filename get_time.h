int day, month, year, hour, minute, second;

void generateTime() {
    time_t now;
    struct tm *current_time;
    time(&now);
    current_time = localtime(&now);
    day = current_time->tm_mday;
    month = current_time->tm_mon + 1;
    year = current_time->tm_year + 1900;

    hour = current_time->tm_hour;
    minute = current_time->tm_min;
    second = current_time->tm_sec;
}

char *getDate() {
    generateTime();
    static char date[20];
    sprintf(date, "%02d/%02d/%04d", day, month, year);

    return date;
}

char *getTime() {
    generateTime();
    static char time[20];
    sprintf(time, "%02d:%02d:%02d", hour, minute, second);

    return time;
}
