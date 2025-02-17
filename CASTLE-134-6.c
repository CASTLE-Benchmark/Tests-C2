#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int id;
    if (sscanf(argv[1], "%d", &id) != 1) {
        fprintf(stderr, "Invalid number: %s\n", argv[1]);
        return 1;
    }

    char* prefix = "%";
    char formatter[1024];
    snprintf(formatter, sizeof(formatter), "%s%d$d\n", prefix, id);
    printf(formatter, id);

    return 0;
}