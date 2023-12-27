#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
/*
 Counting Sort 구현 및 분석
입력: n, k
과정: 최대 k까지의 자연수 n개 랜덤 발생, n개 랜덤 수 내림정렬
출력: n개 랜덤 수(정렬 전), n개 랜덤 수(정렬 후)
*/

int partition(int arr[], int p, int r);
int select(int arr[], int p, int r, int i);
void print(int arr[], int n);

int main(void) {
	int n; int i;
	printf("n: ");	scanf_s("%d", &n);			//발생시킬 랜덤수 입력
	printf("i: ");	scanf_s("%d", &i);			//몇번째 작은 수 찾을건지 입력

	srand((unsigned int)time(NULL));			//랜덤변수 초기화
	int* randnum;								//포인터 변수 선언
	randnum = (int*)malloc(sizeof(int) * n);	//랜덤수 넣을 배열 크기 동적할당

	for (int i = 0; i < n; i++) {
		randnum[i] = (int)(rand() / (double)RAND_MAX * 1000);
	}

	print(randnum, n);
	printf("\n");

	int x = select(randnum, 0, n - 1, i);	//선택알고리즘 함수 호출
	printf("\n%d개의 랜덤수 발생, %d번째 큰 수: %d \n", n, i, x);

	free(randnum);			//동적할당된 배열 해제
}

int partition(int arr[], int p, int r) {
	int pivot = arr[r];						//피봇
	int tmp;
	int i = p - 1;							//i는 1구역(피봇보다 큼)의 끝지점
	for (int j = p; j <= r - 1; j++) {		//j는 3구역(아직 정렬 전)의 시작점
		if (arr[j] >= pivot) {				//정렬하고자 하는 원소 > 피봇 이면
			tmp = arr[++i];					//1구역 끝지점 인덱스를 하나 증가 후
			arr[i] = arr[j];				//정렬하고자 하는 원소와 교환
			arr[j] = tmp;
		}
	}
	tmp = arr[i + 1];
	arr[i + 1] = arr[r];
	arr[r] = tmp;

	return i + 1;
}

int select(int arr[], int p, int r, int i) {	//arr배열에서 i번째 큰 원소를 찾는다
	if (p == r)								//원소가 하나뿐인 경우 i는 반드시 1
		return arr[p];
	int q = partition(arr, p, r);			//퀵정렬의 파티션 함수와 동일
	int k = q - p + 1;						//기준원소 q가 arr[]에서 k번째 작은 원소임을 의미
	if (i < k)								//왼쪽 그룹으로 범위를 좁힘
		return select(arr, p, q - 1, i);
	else if (i == k)						//기준 원소가 바로 찾는 원소일 때
		return arr[q];
	else									//오른쪽 그룹으로 범위를 좁힘
		return select(arr, q + 1, r, i - k);
}

void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}


