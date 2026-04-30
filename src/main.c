#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filters.c"
#include "internal.c"

char **locations;

void addToDb(char *entry) {
    if (getMatch(filterEqual, entry) != NULL) {
        return;
    }

    FILE *file = fopen(DB_PATH, "a");
    fprintf(file, "%s\n", entry);
}

void findLocation(char* entry) {
    char *match = getMatch(filterIn, entry);
    if (match == NULL) {
        fprintf(stderr, "Shit not found\n");
        printf("-");
        return;
    }

    printf(match);
}

int main(int argc, char *args[]) {
    if (argc < 2) {
        return 0;
    }

    if (strcmp(args[1], "add") == 0) {
        if (argc < 3) {
            return 0;
        }

        addToDb(args[2]);
    } else if (strcmp(args[1], "find") == 0) {
        if (argc < 3) {
            printf("--");
            return 0;
        }

        findLocation(args[2]);
    }
}
