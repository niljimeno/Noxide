char *DB_PATH = "/home/nil/.config/db.no";

char *getMatch(int (*filter)(char*, char*), char *entry) {
    FILE *file = fopen(DB_PATH, "r");
    if (file == NULL) {
        return NULL;
    }

    char *line = malloc(255 * sizeof(char));

    while (fgets(line, 255, file)) {
        line = trimNewline(line);
        if (filter(line, entry)) {
            fclose(file);
            return line;
        }
    }

    fclose(file);
    return NULL;
}

