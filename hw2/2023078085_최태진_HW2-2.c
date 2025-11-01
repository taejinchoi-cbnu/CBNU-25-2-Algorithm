#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_ARRAY 100
#define MAX_LEN 100
#define MAX_NAME 30

typedef struct OffsetArray
{
    char name[MAX_NAME];
    int start;
    int value[MAX_LEN];
} OffsetArray;

OffsetArray all_array[MAX_ARRAY];

int array_cnt = 0;

int check(char *string)
{
    char *open_braket = strchr(string, '[');

    if (open_braket == NULL)
    {
        return atoi(string);
    }

    char name[MAX_NAME];
    strncpy(name, string, open_braket - string);
    name[open_braket - string] = '\0';

    char *closing_braket = strrchr(string, ']');
    char inner_string[257];

    strncpy(inner_string, open_braket + 1, closing_braket - (open_braket + 1));
    inner_string[closing_braket - (open_braket + 1)] = '\0';

    int offset_idx = check(inner_string);

    for (int i = 0; i < array_cnt; i++)
    {
        if (strcmp(all_array[i].name, name) == 0)
        {
            int start = all_array[i].start;
            int real_idx = offset_idx - start;

            return all_array[i].value[real_idx];
        }
    }

    return -1;
}

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int n;
    scanf("%d", &n);
    fgetc(stdin);
    for (int i = 0; i < n; i++)
    {
        char assignment[1025] = "";
        scanf("%[^\n]", assignment);
        fgetc(stdin);

        char *before_equal = strtok(assignment, "=");
        char *after_equal = strtok(NULL, "");

        char name[MAX_NAME];
        int start, end;

        sscanf(before_equal, "%[^[][%d..%d]", name, &start, &end);

        OffsetArray *current_arr = &all_array[array_cnt];
        strcpy(current_arr->name, name);
        current_arr->start = start;

        char *token = strtok(after_equal, " ");
        int val_idx = 0;
        while (token != NULL)
        {
            if (strlen(token) > 0 && token[0] != '\n')
            {
                current_arr->value[val_idx] = atoi(token);
                val_idx++;
            }
            token = strtok(NULL, " ");
        }
        array_cnt++;
    }
    char x[257] = "";
    scanf("%[^\n]", x);

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");
    int res = check(x);
    printf("%d\n", res);

    return 0;
}