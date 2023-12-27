#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
과제 2 (버블정렬 고도화)
입력: n  (사용자로부터 n을 입력 받음)
처리: n개 랜덤 수 발생, n개 랜덤 수를 버블정렬 고도화 알고리즘으로 오름 정렬
ppt 3, 4 페이지의 main과 random 함수 참고하여 프로그램 작성
버블정렬 고도화 알고리즘은 교재 92페이지 참고
출력: : n개 랜덤 수(정렬 전), n개 랜덤 수(정렬 후)
*/

#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0

void Bubblesort(int arr[], int n);
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

	Bubblesort(randnum, n);	//버블정렬 함수 호출
	print(randnum, n);		//정렬후 데이터 출력

	free(randnum);			//동적할당된 배열 해제
}



void Bubblesort(int arr[], int n) {
	int tmp;
	int sorted;
	for (int last = n-1; last >= 1; last--) {
		sorted = True;
		for (int i = 0; i < last - 1; i++) {	
			if (arr[i] > arr[i + 1]) {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = False;
			}
		}
		if (sorted == True)
			break;
	}
}

void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}