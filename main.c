#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int global_quantity = 0;

void knots_adj(int *pMass, int lines_counts)
{
    _Bool flag = 1;
    if (global_quantity != lines_counts * lines_counts)
    {
        printf("incorrect adjacency matrix");
        return;
    }
    for (int i = 0; i < lines_counts; i++)
    {
        if (pMass[lines_counts * i + i] == 1)
        {
            if (flag)
            {
                flag = 0;
                printf("LOOP DETECTED:\n\r");
            }
            printf("i: %d\tj: %d\n\r", i, i);
        }
    }
    if (flag)
        printf("NO LOOP");
}

void knots_inc(int *pMass, int lines_counts)
{
    _Bool flag = 1;
    int ch_in_str = global_quantity / lines_counts;
    for (int i = 0; i < global_quantity; i++)
    {
        if (pMass[i] == 2)
        {
            if (flag)
            {
                flag = 0;
                printf("LOOP DETECTED:\n\r");
            }
            printf("i: %d\tj: %d\n\r", i/ch_in_str, i%(i/ch_in_str*ch_in_str));
        }
    }
    if (flag)
        printf("NO LOOP");
}

void read_numbers(FILE *file, int quantity, int *numbers)
{
    fseek(file, 0, SEEK_SET);
    for (int i = 0; i < quantity; ++i)
    {
        fscanf(file, "%d", &numbers[i]);
    }
}

int strCount(char *argv)
{
    FILE *file = fopen(argv, "r");
    int lines_count = 0;
    fseek(file, 0, SEEK_SET);
    while (!feof(file))
    {
        if (fgetc(file) == '\n')
            //fseek(file, lines_count, SEEK_SET);
            //if ((fgetc(file)))
             lines_count++;
    }
    fclose(file);
    //lines_count++;
    printf("%d\n\r", lines_count);
    return lines_count;
}

int numberCount(FILE *file)
{
    int counter = 0;
    int str = 0;
    fseek(file, 0, SEEK_SET);
    while (1)
    {
        int value;
        if (fscanf(file, "%d", &value) == 1)
            counter++;
        if (feof(file))
            break;
    }
    return counter;
}

int *getfile(char *argv)
{
    FILE *file = fopen(argv, "r");
    if (file == NULL)
    {
        printf("File open error\n\r");
        exit(EXIT_FAILURE);
    }

    int quantity = numberCount(file); // counting numbers
    global_quantity = quantity;
    int *numbers = (int *)malloc(quantity * sizeof(int));
    read_numbers(file, quantity, numbers);
    return numbers;
}

int main(int argc, char *argv[])
{
    float start, stop;
    if (argc != 3)
    {
        printf("invalid arguments");
        return 1;
    }

    int mode = (int)(*argv[2] - '0');
    int *pMass = getfile(argv[1]);
    int lines_count = strCount(argv[1]);

    switch (mode)
    {
    case 0:
        start = clock();
        knots_adj(pMass, lines_count);
        stop = clock();
        break;
    case 1:
        start = clock();
        knots_inc(pMass, lines_count);
        stop = clock();
        break;
    default:
    {
        printf("invalid arguments");
        return 1;
    }
    }

    printf("\n\r%f ms", stop - start);
    return 0;
}