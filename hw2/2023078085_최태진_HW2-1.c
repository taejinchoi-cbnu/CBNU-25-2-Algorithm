#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10001

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

typedef struct node
{
    int person;
    struct node *next;
} Node;

Node *adj_list[MAX];

void add_person(int x, int y)
{
    Node *new_node = (Node *)malloc(sizeof(Node));

    new_node->person = y;
    new_node->next = adj_list[x];

    adj_list[x] = new_node;
}

int visited[MAX];

int dfs(int person)
{
    if (visited[person] != 0)
    {
        return visited[person];
    }

    int max_depth = 0;
    Node *current = adj_list[person];

    while (current != NULL)
    {
        int depth = dfs(current->person);

        if (depth > max_depth)
        {
            max_depth = depth;
        }

        current = current->next;
    }

    int my_depth = 1 + max_depth;
    return my_depth;
}

int main()
{
    for (int i = 0; i < MAX; i++)
    {
        adj_list[i] = NULL;
        visited[i] = NULL;
    }

    // the number of relationships of influence
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        // a relationship of influence between two people (x influences y)
        int x;
        int y;
        scanf("%d%d", &x, &y);
        add_person(x, y);
    }

    int res = 0;

    for (int i = 0; i < MAX; i++)
    {
        int current_length = dfs(i);

        if (current_length > res)
        {
            res = current_length;
        }
    }

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    // The number of people involved in the longest succession of influences
    printf("%d\n", res);

    return 0;
}