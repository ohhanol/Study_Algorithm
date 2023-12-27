#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
/*
과제 3 (삽입정렬)
입력: n  (사용자로부터 n을 입력 받음)
처리: n개 랜덤 수 발생, n개 랜덤 수를 삽입정렬 알고리즘으로 오름 정렬
ppt 3, 4 페이지의 main과 random 함수 참고하여 프로그램 작성
출력: : n개 랜덤 수(정렬 전), n개 랜덤 수(정렬 후)
*/

#define True 1
#define False 0

void insertsort(int arr[], int n);
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

	insertsort(randnum, n);	//삽입정렬 함수 호출
	print(randnum, n);		//정렬후 데이터 출력

	free(randnum);			//동적할당된 배열 해제
}



void insertsort(int arr[], int n) {
	for (int i = 1; i <n; i++) {
		int loc = i - 1;
		int new_item = arr[i];
		while (loc >= 0 && new_item < arr[loc]) {
			arr[loc + 1] = arr[loc];
			loc--;
		}
		arr[loc + 1] = new_item;
	}
}

void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}