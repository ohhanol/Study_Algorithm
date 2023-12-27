#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0
/*
실습 1 (병합정렬)
입력: n  (사용자로부터 n을 입력 받음)
처리: n개 랜덤 수 발생, n개 랜덤 수를 병합정렬 알고리즘으로 오름 정렬
출력: : n개 랜덤 수(정렬 전), n개 랜덤 수(정렬 후)
*/

void Mergesort(int arr[], int p, int r);	//분할시키는 함수
void Merge(int arr[], int p, int q, int r);	//합병시키는 함수
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

	Mergesort(randnum, 0,n-1);	//병합정렬 함수 호출
	print(randnum, n);		//정렬후 데이터 출력

	free(randnum);			//동적할당된 배열 해제
}



void Mergesort(int arr[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;	//가운데 부분=q
		Mergesort(arr, p, q);
		Mergesort(arr, q + 1, r);
		Merge(arr, p, q, r);
	}
}


void Merge(int arr[], int p, int q, int r) {
	int i = p;
	int j = q + 1;
	int t = 0;

	int* tmp;
	tmp = (int*)malloc(sizeof(int) * (r - p + 1));

	while (i <= q && j <= r) {
		if (arr[i] <= arr[j])
			tmp[t++] = arr[i++];
		else
			tmp[t++] = arr[j++];
	}

	while (i <= q)
		tmp[t++] = arr[i++];
	while (j <= r)
		tmp[t++] = arr[j++];

	i = p; t = 0;
	while (i <= r)
		arr[i++] = tmp[t++];

}

void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}