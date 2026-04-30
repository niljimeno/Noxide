#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "filters.c"
#include "internal.c"

char **locations;

void addToDb(char *entry) {
    if (getMatch(filterEqual, entry) != NULL) {
        return;
    }

    FILE *file = fopen(DB_PATH, "a");
    fprintf(file, "%s\n", entry);
    fclose(file);
}

void addPathToDb(char *entry) {
    char buffer[strlen(entry)+1];

    for (int i = 0; i <= strlen(entry); ++i) {
        if (entry[i] == '/') {
            buffer[i] = '/';
            buffer[i+1] = '\0';
            addToDb(buffer);
        }

        else if (entry[i] == '\0') {
            buffer[i] = '/';
            buffer[i+1] = '\0';
            break;
        }

        buffer[i] = entry[i];
    }

    addToDb(buffer);
}

void findLocation(char *entry) {
    removeOldEntries();

    char *match = getMatch(filterIn, entry);
    if (match == NULL) {
        printf(".");
        return;
    }

    printf(match);
}

void findInteractiveLocation(char *entry) {
    removeOldEntries();

    char *result = readFZF();
    if (strcmp(result, "") == 0) {
        printf(".");
        return;
    }

    printf(result);
}

int main(int argc, char *args[]) {
    if (argc < 2) {
        return 0;
    }

    if (strcmp(args[1], "init") == 0) {
        printf(SCRIPT);
    }

    else if (strcmp(args[1], "clean") == 0) {
        removeDatabase();
    }

    else if (strcmp(args[1], "add") == 0) {
        if (argc < 3) {
            return 0;
        }

        addPathToDb(args[2]);
    }

    else if (strcmp(args[1], "find") == 0) {
        if (argc < 3) {
            printf("--");
            return 0;
        }

        findLocation(args[2]);
    }

    else if (strcmp(args[1], "ifind") == 0) {
        findInteractiveLocation(args[2]);
    }
}
