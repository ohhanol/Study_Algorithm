#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0
/*
* 과제 1(병합정렬)
입력: n  (사용자로부터 n을 입력 받음)
처리: n개 랜덤 수 발생, n개 랜덤 수를 병합정렬 알고리즘으로 내림 정렬 
출력: : n개 랜덤 수(정렬 전), n개 랜덤 수(정렬 후)


*/

void Mergesort(int arr[], int p, int r);	//분할시키는 함수
void Merge(int arr[], int p, int q, int r);	//합병시키는 함수
void print(int arr[], int n);

int main(void) {
	int n;
	scanf_s("%d", &n);

	srand((unsigned int)time(NULL));			// 랜덤변수 초기화
	int* randnum;								// 포인터 변수 선언
	randnum = (int*)malloc(sizeof(int) * n);	// 랜덤수 넣을 배열 크기 동적할당
	for (int i = 0; i < n; i++) {
		randnum[i] = (int)rand() / (double)RAND_MAX * 1000;	// 발생시킨 랜덤값을 randomnum 배열에 넣음
	}
	print(randnum, n);		// 정렬전 데이터 출력
	printf("\n");

	Mergesort(randnum, 0, n - 1);	// 병합정렬 함수 호출
	print(randnum, n);		// 정렬후 데이터 출력

	free(randnum);			// 동적할당된 배열 해제
}


void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}

void Mergesort(int arr[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;		// 가운데 부분 = q
		Mergesort(arr, p, q);		// 왼쪽 정렬
		Mergesort(arr, q + 1, r);	// 오른쪽 정렬
		Merge(arr, p, q, r);		// 합병
	}
}


void Merge(int arr[], int p, int q, int r) {
	int i = p;		// 왼쪽 덩어리 index 기능
	int j = q + 1;	// 오른쪽 덩어리 index 기능
	int t = 0;		// 정렬 결과를 채울 곳의 위치

	int* tmp;	// 정렬 결과를 채울 배열 동적할당
	tmp = (int*)malloc(sizeof(int) * (r - p + 1));



	// 정렬 알고리즘
	while (i <= q && j <= r) {		// i가 왼쪽을 다 돌때까지 AND j가 오른쪽 다 돌 때까지
		if (arr[i] >= arr[j])		// 내림정렬이므로 i(왼쪽)가 j(오른쪽)보다 크면
			tmp[t++] = arr[i++];	// tmp배열에 i번째 원소를 넣고 t와 i 하나씩 증가시키기
		else
			tmp[t++] = arr[j++];	//반대의 경우엔 tmp에 j번째 원소를 넣고 j 하나씩 증가시키기
	}


	/*
	반복문이 끝나면, 즉 한쪽 정렬이 끝나면 수행되는 코드
	*/
	while (i <= q)				
		tmp[t++] = arr[i++];
	while (j <= r)
		tmp[t++] = arr[j++];


	i = p; t = 0;
	while (i <= r)	//tmp 배열을 arr배열에 복사
		arr[i++] = tmp[t++];
	free(tmp);

}

