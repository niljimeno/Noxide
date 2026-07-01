char *trimNewline(char *entry) {
    int length = strlen(entry);
    if (length && entry[length-1] == '\n') entry[length-1] = '\0';
    return entry;
}

int filterEqual(char* a, char* b) {
    return (!strcmp(a, b));
}

int filterEqualName(char* a, char* b) {
    int len = strlen(a);

    if (len == 0) {
        return false;
    }
    len--;


    char original_char = a[len];
    a[len] = '\0';

    char *filename = strrchr(a, '/');
    filename = filename ? filename + 1 : a;
    int result = !strcmp(filename, b);

    a[len] = original_char;
    return result;
}

int filterIn(char* data, char* entry) {
    return (!(strstr(data, entry) == NULL));
}
