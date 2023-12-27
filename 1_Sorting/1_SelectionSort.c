#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
실습 1 (선택정렬)
입력: n  (사용자로부터 n을 입력 받음)
처리: n개 랜덤 수 발생, n개 랜덤 수를 선택정렬 알고리즘으로 오름 정렬 
ppt 2, 3 페이지의 main과 random 함수 참고하여 프로그램 작성
출력: : n개 랜덤 수(정렬 전), n개 랜덤 수(정렬 후)

*/


int selectionSort(int A[], int n);
int main(void)
{
	srand((unsigned int)time(NULL));
	int a;
	scanf_s("%d", &a);

	int* randomnum;
	randomnum = (int*)malloc(sizeof(int) * a);
	for (int i = 0; i < a; i++) {
		randomnum[i]= rand() / (double)RAND_MAX * 1000;
	}
	for (int i = 0; i < a; i++) {
		printf("%d ", randomnum[i]);
	}
	printf("\n");
	selectionSort(randomnum, a);

	for (int i = 0; i < a; i++) {
		printf("%d ", randomnum[i]);
	}

	free(randomnum);
}

int selectionSort(int A[], int n) {
	int max, tmp;
	for (int last = n - 1; last >= 1; last--) {
		max = 0;
		for (int i = 0; i < last; i++) {
			if (A[max] < A[i+1]) {
				max = i+1;
			}
		}
		tmp = A[last];
		A[last] = A[max];
		A[max] = tmp;
	}
}