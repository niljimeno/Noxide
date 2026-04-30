char *DB_PATH = "/home/nil/.config/db.no";

char *SCRIPT =  "__noxide_hook() {\n\tnoxide add \"$(pwd)\"\n}\n\n"
                "PS1=\"${PS1}\\$(__noxide_hook)\"\n\n"
                "z() {\n\tresult=\"$(noxide find \"$@\")\" && cd \"$result\"\n}\n\n"
                "zi() {\n\tresult=\"$(noxide ifind \"$@\")\" && cd \"$result\"\n}" ;

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

char *readFZF() {
    char command[255];
    sprintf(command, "cat %s | fzf", DB_PATH);

    char *buffer = malloc(sizeof(char) * 255);
    FILE *fp = popen(command, "r");

    if (fp == NULL) {
        perror("popen failed");
        return NULL;
    }

    fgets(buffer, sizeof(char) * 255, fp);

    pclose(fp);
    return buffer;
}

void removeOldEntries() {
    FILE *file = fopen(DB_PATH, "r");
    if (file == NULL) {
        return;
    }

    char *line = malloc(255 * sizeof(char));

    while (fgets(line, 255, file)) {
        if (access(line, F_OK) != 0) {
            remove(line);
        }
    }

    fclose(file);
    return;
}

void removeDatabase() {
    remove(DB_PATH);
}
