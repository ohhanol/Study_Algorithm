#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0
/*
평균 선형시간 선택알고리즘 구현 및 분석
입력: n, i
과정: n개 랜덤 수 발생, i 번째 작은 수 선택
출력: n개 랜덤 수, i 번째 작은 수
*/

void countingSort(int* arr, int k, int n);
void print(int arr[], int n);

int main(void) {
	int n; int k;
	printf("n: ");	scanf_s("%d", &n);
	printf("k: ");	scanf_s("%d", &k);

	srand((unsigned int)time(NULL));			//랜덤변수 초기화
	int* randnum;								//포인터 변수 선언
	randnum = (int*)malloc(sizeof(int) * n);	//랜덤수 넣을 배열 크기 동적할당

	for (int i = 0; i < n; i++) {
		randnum[i] = (rand() % k) + 1;
	}

	print(randnum, n);		//정렬전 데이터 출력
	printf("\n");

	countingSort(randnum, k, n);	//병합정렬 함수 호출
	print(randnum, n);		//정렬후 데이터 출력

	free(randnum);			//동적할당된 배열 해제
}


void countingSort(int* arr, int k, int n) {
	int i;
	int* result; int* grade;
	result = (int*)malloc(sizeof(int) * n);
	grade = (int*)malloc(sizeof(int) * k);
	for (i = 0; i < k; i++)
		grade[i] = 0;
	for (i = 0; i < n; i++)
		grade[arr[i]]++;
	for (i = 1; i < k; i++)
		grade[i] = grade[i] + grade[i - 1];
	for (i = n - 1; i >= 0; i--) {
		result[grade[arr[i]] - 1] = arr[i];
		grade[arr[i]]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = result[i];
}

void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}