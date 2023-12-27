#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

/*실습1 선택정렬
	- 입력 n(사용자로부터 입력받음)
	- 처리: n개의 랜덤수 발생, n개 랜덤수를 선택정렬 알고리즘으로 오름 정렬
	- 출력: n개 랜덤 수(정렬 전), n개 랜덤수(정렬 후)
*/

//MIN 찾아 Front에 고정하는 방식
int Selectionsort(int rand[], int n);

void main() {
	int n;
	scanf_s("%d", &n);	//사용자에게 입력받을 수 n

	/*------------------------------------------------------------------*/
	srand((unsigned int)time(NULL));

	int* randnum;
	randnum = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		randnum[i] = rand() / (double)RAND_MAX * 1000;
		printf("%d ", randnum[i]);
	}
	/*----------사용자에게 숫자 n 입력받아 그만큼의 랜덤수 발생시킴 ---------*/
	printf("\n");

	Selectionsort(randnum, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", randnum[i]);
	}
	free(randnum);
}


int Selectionsort(int rand[], int n) {
	int tmp;
	for (int front = 0; front <n-1; front++) {
		int min = n-1;
		for (int i = min; i >front; i--) {
			if (rand[min] > rand[i - 1])
				min = i - 1;
		}
		tmp = rand[front];
		rand[front] = rand[min];
		rand[min] = tmp;
	}
}