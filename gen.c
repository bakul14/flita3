#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file = fopen("matrix3.txt", "w");
    int quantity = 0;
    sscanf(argv[1], "%d", &quantity);
    for (int i = 0; i < quantity; i++) {
        for (int j = 0; j < quantity; j++) {
            fprintf(file, "%d ", rand()%2);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("%d", quantity);

    return 0;
}