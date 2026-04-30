char *trimNewline(char *entry) {
    int length = strlen(entry);
    if (length && entry[length-1] == '\n') entry[length-1] = '\0';
    return entry;
}

int filterEqual(char* a, char* b) {
    return (!strcmp(a, b));
}

int filterIn(char* data, char* entry) {
    return (!(strstr(data, entry) == NULL));
}

