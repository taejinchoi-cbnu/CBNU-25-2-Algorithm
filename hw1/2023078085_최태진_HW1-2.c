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
    int res = 5526; // res 최대값으로 init
    // the number of temperatures to analyse
    int n;
    scanf("%d", &n);
    if (n == 0)
        res = 0;
    for (int i = 0; i < n; i++)
    {
        // a temperature expressed as an integer ranging from -273 to 5526
        int t;
        scanf("%d", &t);
        // 절대값 t가 같은 경우 양수로 바꿔줌
        if (abs(res) == abs(t) && t > 0)
            res = t;
        // t가 res보다 0에 가까우면 바꿔줌
        if (abs(res) > abs(t))
            res = t;
    }

    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    printf("%d\n", res);

    return 0;
}

/*
트러블 슈팅
0에서 가까운거면 절대값이 작은게 맞음
abs()라는 메서드를 사용하면됨
res를 최대값으로 초기화 */