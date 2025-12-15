#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 1005

int P[MAX_N];
long long cache_money[MAX_N];
int cache_next[MAX_N];

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int L;
    int C;
    int N;
    scanf("%d%d%d", &L, &C, &N);
    for (int i = 0; i < N; i++)
    {
        int pi;
        scanf("%d", &pi);
        P[i] = pi;
    }

    for (int i = 0; i < N; i++)
    {
        long long current_earnings = 0;
        int current_idx = i;
        int groups_on_board = 0;

        while (current_earnings + P[current_idx] <= L)
        {
            current_earnings += P[current_idx];
            current_idx = (current_idx + 1) % N;
            groups_on_board++;

            if (groups_on_board == N)
            {
                break;
            }
        }

        cache_money[i] = current_earnings;
        cache_next[i] = current_idx;
    }

    long long total_dirhams = 0;
    int current_first_group_idx = 0;

    for (int i = 0; i < C; i++)
    {
        total_dirhams += cache_money[current_first_group_idx];
        current_first_group_idx = cache_next[current_first_group_idx];
    }

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    printf("%lld\n", total_dirhams);

    return 0;
}