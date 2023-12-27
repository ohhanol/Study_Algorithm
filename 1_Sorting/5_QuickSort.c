#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS


void quicksort(int arr[], int p, int r);
int partition(int arr[], int p, int r);
void print(int arr[], int n);

int main(void) {
	int n;
	scanf_s("%d", &n);

	srand((unsigned int)time(NULL));			//랜덤변수 초기화
	int* randnum;								//포인터 변수 선언
	randnum = (int*)malloc(sizeof(int) * n);	//랜덤수 넣을 배열 크기 동적할당
	for (int i = 0; i < n; i++) {
		randnum[i] = (int)rand() / (double)RAND_MAX * 1000;	//발생시킨 랜덤값을 randomnum 배열에 넣음
	}
	print(randnum, n);		//정렬전 데이터 출력
	printf("\n");

	quicksort(randnum, 0, n - 1);	//퀵정렬 함수 호출
	print(randnum, n);		//정렬후 데이터 출력

	free(randnum);			//동적할당된 배열 해제
}



void quicksort(int arr[], int p, int r) {
	if (p < r) {
		int q = partition(arr, p, r);
		quicksort(arr, p, q - 1);
		quicksort(arr, q + 1, r);
	}
}

int partition(int arr[], int p, int r) {
	int x = arr[r];
	int i = p - 1;
	int tmp;
	for (int j = p; j <= r - 1; j++) {
		if (arr[j] <= x) {
			tmp = arr[++i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	tmp = arr[i + 1];
	arr[i + 1] = arr[r];
	arr[r] = tmp;
	return i + 1;
}

void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}