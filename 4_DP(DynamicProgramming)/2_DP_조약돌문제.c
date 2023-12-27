#include <stdio.h>
#include <stdlib.h>

/* 조약돌 문제
아래 그림의 조약돌 문제의 최대값과 그때의 각 열의 패턴을 출력하는 프로그램
6   7   12  -5  5   3   11  3
-8  10  14  9   7   13  8   5  
11  12  7   4   8   -2  9   4

출력 형태 (예)
Max = 92
3,2,4,2,1,2,4,2
*/

void CalcW(int mat[3][8], int** w);
int pebble(int n, int** w);
int MAX(int** peb, int i, int p);

int main()
{
    // 저장된 행렬
    int matrix[3][8] = {
        { 6,7,12,-5,5,3,11,3 },
        { -8,10,14,9,7,13,8,5 },
        { 11,12,7,4,8,-2,9,4 }
    };

    // 행렬을 패턴만큼 저장하는 공간 생성
    int** w = (int**)malloc(sizeof(int*) * 8);
    for (int i = 0; i < 8; i++)
        w[i] = (int*)malloc(sizeof(int) * 4);

    CalcW(matrix, w);

    int maxScore = pebble(8, w);

    printf("최대값: %d\n", maxScore);

    for (int i = 0; i < 8; i++)
        free(w[i]);

    free(w);

    return 0;
}

void CalcW(int mat[3][8], int** w)
{
    int i, j, score;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 4; j++) {
            if (j == 0)
                score = mat[0][i];
            else if (j == 1)
                score = mat[1][i];
            else if (j == 2)
                score = mat[2][i];
            else
                score = mat[0][i] + mat[2][i];

            w[i][j] = score;
        }
    }
}

int pebble(int n, int** w)
{
    int** peb = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        peb[i] = (int*)malloc(sizeof(int) * 4);

    int p, i, j;

    // 부분문제들의 답을 n x 4 배열 peb에 저장한다
    for (p = 0; p < 4; p++)
        peb[0][p] = w[0][p];

    for (i = 1; i < n; i++)
        for (p = 0; p < 4; p++)
            peb[i][p] = MAX(peb, i, p) + w[i][p];

    int maxValue = peb[0][0];
    int pet = 0;
    printf("경로: "); // 경로 출력
    for (i = 0; i < n; i++) {
        for (j = 0; j < 4; j++) {
            if (maxValue < peb[i][j]) {
                maxValue = peb[i][j];
                pet = j + 1;
            }
        }
        printf("%d ", pet);
    }
    printf("\n");

    for (i = 0; i < n; i++)
        free(peb[i]);

    free(peb);

    return maxValue;
}

int MAX(int** peb, int i, int p)
{
    int max;

    // 4개의 패턴 p, p와 양립하는 패턴 반환
    if (p == 0) {
        if (peb[i - 1][1] > peb[i - 1][2])
            max = peb[i - 1][1];
        else
            max = peb[i - 1][2];

        if (max > peb[i - 1][3])
            return max;
        else
            return peb[i - 1][3];
    }
    else if (p == 1) {
        if (peb[i - 1][0] > peb[i - 1][2])
            max = peb[i - 1][0];
        else
            max = peb[i - 1][2];

        if (max > peb[i - 1][3])
            return max;
        else
            return peb[i - 1][3];
    }
    else if (p == 2) {
        if (peb[i - 1][0] > peb[i - 1][1])
            max = peb[i - 1][0];
        else
            max = peb[i - 1][1];

        if (max > peb[i - 1][3])
            return max;
        else
            return peb[i - 1][3];
    }
    else {
        if (peb[i - 1][0] > peb[i - 1][1])
            max = peb[i - 1][0];
        else
            max = peb[i - 1][1];

        if (max > peb[i - 1][2])
            return max;
        else
            return peb[i - 1][2];
    }
}
