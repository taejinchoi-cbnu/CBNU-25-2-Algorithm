#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
        char line[1025] = "";
        if (scanf("%[^\n]", line) != 1)
        {
            line[0] = '\0';
        }
        fgetc(stdin);

        int doll_stack[256];
        int child_sum_stack[256];
        int top = -1;
        int cnt = 0;
        int err_flag = 0;
        int root_opened = 0;

        char *token = strtok(line, " \n\r");

        if (token == NULL)
        {
            err_flag = 1;
        }

        while (token != NULL)
        {
            int value;
            char extra_chars[10];

            if (sscanf(token, "%d%s", &value, extra_chars) != 1)
            {
                err_flag = 1;
                break;
            }

            if (value == 0)
            {
                err_flag = 1;
                break;
            }

            if (value < 0)
            {
                int size = -value;

                if (top == -1 && root_opened > 0)
                {
                    err_flag = 1;
                    break;
                }

                top++;
                doll_stack[top] = size;
                child_sum_stack[top] = 0;

                if (top == 0)
                {
                    root_opened = 1;
                }
            }
            else
            {
                int size = value;

                if (top < 0 || doll_stack[top] != size)
                {
                    err_flag = 1;
                    break;
                }

                int doll_size = doll_stack[top];
                int children_sum = child_sum_stack[top];
                top--;

                if (children_sum >= doll_size)
                {
                    err_flag = 1;
                    break;
                }

                if (children_sum == 0)
                {
                    cnt++;
                }

                if (top >= 0)
                {
                    child_sum_stack[top] += doll_size;
                }
            }

            token = strtok(NULL, " \n\r");
        }

        if (top != -1)
        {
            err_flag = 1;
        }

        if (root_opened == 0)
        {
            err_flag = 1;
        }

        if (err_flag)
        {
            printf("-1\n");
        }
        else
        {
            printf("%d\n", cnt);
        }
    }

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    return 0;
}