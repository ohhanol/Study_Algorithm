#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

/*실습2 버블정렬
	- 입력 n(사용자로부터 입력받음)
	- 처리: n개의 랜덤수 발생, n개 랜덤수를 버블정렬 알고리즘으로 오름 정렬
	- 출력: n개 랜덤 수(정렬 전), n개 랜덤수(정렬 후)
*/

int Bubblesort(int rand[], int n);

int main(void) {
	int n;
	scanf_s("%d", &n);

	srand((unsigned int)time(NULL));
	int* randnum;
	randnum = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		randnum[i] = rand() / (double)RAND_MAX * 1000;
		printf("%d ", randnum[i]);
	}
	printf("\n");

	Bubblesort(randnum, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", randnum[i]);
	}
	free(randnum);
}



int Bubblesort(int rand[], int n) {
	int tmp;
	for (int last = n-1; last >= 1; last--) {	//고정하는 for루프
		for (int i = 0; i < last-1; i++) {	//비교하는 for루프
			if (rand[i] > rand[i + 1]) {
				tmp = rand[i];
				rand[i] = rand[i + 1];
				rand[i + 1] = tmp;}
			
		}
	}
}