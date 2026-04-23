// optimized.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100003

typedef struct {
    char ip[16];
    int count;
    int used;
} Entry;

Entry* table;

unsigned int hash(char* ip) {
    unsigned int h = 0;
    while (*ip) {
        h = (h * 31) + (*ip++);
    }
    return h % TABLE_SIZE;
}

void insert_or_update(char* ip) {
    unsigned int idx = hash(ip);

    while (table[idx].used) {
        if (strcmp(table[idx].ip, ip) == 0) {
            table[idx].count++;
            return;
        }
        idx = (idx + 1) % TABLE_SIZE;
    }

    strcpy(table[idx].ip, ip);
    table[idx].count = 1;
    table[idx].used = 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./optimized logfile.txt\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    table = (Entry*)calloc(TABLE_SIZE, sizeof(Entry));

    char ip[16], type[10];
    int total_requests = 0;
    int error_count = 0;

    clock_t start = clock();

    while (fscanf(file, "%15s %9s", ip, type) == 2) {
        total_requests++;

        if (strcmp(type, "ERROR") == 0) {
            error_count++;
        }

        insert_or_update(ip);
    }

    clock_t end = clock();

    printf("Total Requests: %d\n", total_requests);
    printf("Error Count: %d\n", error_count);

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].used) {
            printf("%s -> %d\n", table[i].ip, table[i].count);
        }
    }

    printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(table);
    fclose(file);
    return 0;
}