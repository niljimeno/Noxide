#include <dirent.h>
#include <errno.h>

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

    char *line = malloc(PATH_MAX * sizeof(char));

    while (fgets(line, PATH_MAX, file)) {
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
    char command[PATH_MAX];
    sprintf(command, "cat %s | fzf", DB_PATH);

    char *buffer = malloc(PATH_MAX * sizeof(char));
    buffer[0] = '\0';

    FILE *fp = popen(command, "r");

    if (fp == NULL) {
        perror("popen failed");
        return "";
    }

    fgets(buffer, sizeof(char) * PATH_MAX, fp);

    pclose(fp);
    return buffer;
}

int getFileSize(FILE *file) {
    fseek(file, 0L, SEEK_END);
    return ftell(file) + 1;
}

int directoryExists(char *directory) {
    DIR* dir = opendir(directory);
    int result = dir ? 1 : 0;
    closedir(dir);
    return result;
}

void removeOldEntries() {
    FILE *file = fopen(DB_PATH, "r");
    if (file == NULL) {
        return;
    }

    int fileSize = getFileSize(file);

    fclose(file);
    file = fopen(DB_PATH, "r");

    char *line = malloc(PATH_MAX * sizeof(char));
    char *newFile = malloc(fileSize);
    int newFileIndex = 0;

    while (fgets(line, PATH_MAX, file)) {
        if (!directoryExists(trimNewline(line))) {
            continue;
        }

        for (int i = 0; i < strlen(line); ++i) {
            newFile[newFileIndex] = line[i];
            newFileIndex++;
        }

        newFile[newFileIndex] = '\n';
        newFileIndex++;
    }

    newFile[newFileIndex] = '\0';
    fclose(file);
    remove(DB_PATH);

    file = fopen(DB_PATH, "w");
    fprintf(file, newFile);
    fclose(file);

    return;
}

void removeDatabase() {
    remove(DB_PATH);
}
