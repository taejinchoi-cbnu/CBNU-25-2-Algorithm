#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// rank와 같이 책을 저장할 구조체
typedef struct
{
    char name[1025];
    int rank; // -1 = None (TBR), 0~10 = rank
} Book;

// 출력 전 정렬 함수
int sorting_books(const void *a, const void *b)
{
    const Book *A = a;
    const Book *B = b;
    return strcmp(A->name, B->name);
}

int main()
{
    // 새 책 입력받기
    int b;
    scanf("%d", &b);
    fgetc(stdin);
    char new_books[1000][1025];
    int new_count = 0;

    for (int i = 0; i < b; i++)
    {
        char title[1025];
        fgets(title, 1025, stdin);
        size_t L = strlen(title);
        if (L > 0 && title[L - 1] == '\n')
            title[L - 1] = '\0';

        // 새 책 입력값에서 중복 있으면 skip
        int dup = 0;
        for (int j = 0; j < new_count; j++)
        {
            if (strcmp(new_books[j], title) == 0)
            {
                dup = 1;
                break;
            }
        }
        // 중복 아니면 추가
        if (!dup)
        {
            strcpy(new_books[new_count++], title);
        }
    }

    // 선반에 있는 책 입력받기
    int n;
    scanf("%d", &n);
    fgetc(stdin);

    Book shelf_books[1000];
    int shelf_size = n;

    for (int i = 0; i < n; i++)
    {
        char name[1025];
        fgets(name, 1025, stdin);
        // 공백 기준으로 분리해서 책 이름이랑 rank 구조체에 저장
        size_t L = strlen(name);
        if (L > 0 && name[L - 1] == '\n')
            name[L - 1] = '\0';

        char *rank_str = strrchr(name, ' ');
        *rank_str = '\0';
        rank_str++;
        strcpy(shelf_books[i].name, name);
        if (strcmp(rank_str, "None") == 0)
        {
            shelf_books[i].rank = -1; // tbr인 경우 rank -1로
        }
        else
        {
            shelf_books[i].rank = atoi(rank_str); // tbr 아닌경우 rank값 그대로
        }
    }

    // 선방네 있는 책 중에서 최대 rank 찾기 (favorite book은 삭제하면 안됨)
    int max_rank = -1;
    for (int i = 0; i < shelf_size; i++)
    {
        if (shelf_books[i].rank > max_rank)
            max_rank = shelf_books[i].rank;
    }

    // 새 책을 넣어야할 공간 계산
    while (1)
    {
        int needed_slots = 0;
        for (int i = 0; i < new_count; i++)
        {
            int found = 0;
            for (int j = 0; j < shelf_size; j++)
            {
                if (strcmp(new_books[i], shelf_books[j].name) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (!found)
                needed_slots++;
        }
        // 선반에서 책 제거 안해도 자리 있는 경우
        if (shelf_size + needed_slots <= n)
            break;

        // 책을 제거하고 선반에 넣어하는 경우를 위한 가장 낮은 rank 계산
        int min_rank = INT_MAX;
        for (int i = 0; i < shelf_size; i++)
        {
            if (shelf_books[i].rank != -1 && shelf_books[i].rank != max_rank)
            {
                if (shelf_books[i].rank < min_rank)
                    min_rank = shelf_books[i].rank;
            }
        }
        // 선반에 책을 못넣는 경우
        if (min_rank == INT_MAX)
        {
            printf("Your TBR is out of control Clara!\n");
            return 0;
        }

        // 작은 rank인 책들 삭제
        int w = 0;
        for (int i = 0; i < shelf_size; i++)
        {
            if (shelf_books[i].rank == min_rank)
                continue;
            shelf_books[w++] = shelf_books[i];
        }
        shelf_size = w;
    }

    // 새 책들 추가하기
    for (int i = 0; i < new_count; i++)
    {
        int found = 0;
        for (int j = 0; j < shelf_size; j++)
        {
            if (strcmp(new_books[i], shelf_books[j].name) == 0)
            {
                found = 1; // 이미 있으면 skip해버림
                break;
            }
        }
        if (!found)
        {
            strcpy(shelf_books[shelf_size].name, new_books[i]);
            shelf_size++;
        }
    }

    // 최종 선반에 있는 책 정렬 후 출력
    qsort(shelf_books, shelf_size, sizeof(Book), sorting_books);

    for (int i = 0; i < shelf_size; i++)
    {
        printf("%s\n", shelf_books[i].name);
    }

    return 0;
}
