// baseline.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char ip[16];
    int count;
    struct Node* next;
} Node;

Node* head = NULL;

Node* find(char* ip) {
    Node* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->ip, ip) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void insert(char* ip) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->ip, ip);
    newNode->count = 1;
    newNode->next = head;
    head = newNode;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./baseline logfile.txt\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    char ip[16], type[10];
    int total_requests = 0;
    int error_count = 0;

    clock_t start = clock();

    while (fscanf(file, "%15s %9s", ip, type) == 2) {
        total_requests++;

        if (strcmp(type, "ERROR") == 0) {
            error_count++;
        }

        Node* node = find(ip);
        if (node != NULL) {
            node->count++;
        } else {
            insert(ip);
        }
    }

    clock_t end = clock();

    printf("Total Requests: %d\n", total_requests);
    printf("Error Count: %d\n", error_count);

    Node* curr = head;
    while (curr != NULL) {
        printf("%s -> %d\n", curr->ip, curr->count);
        curr = curr->next;
    }

    printf("Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    fclose(file);
    return 0;
}