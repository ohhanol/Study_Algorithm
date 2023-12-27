#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0
/*
과제 2(힙정렬)
입력: n  (사용자로부터 n을 입력 받음)
처리: n개 랜덤 수 발생, n개 랜덤 수를 힙정렬 알고리즘으로 내림 정렬
출력: : n개 랜덤 수(정렬 전), n개 랜덤 수(정렬 후)
*/

void Heapsort(int arr[], int n);
void buildHeap(int arr[], int n);
void heapify(int arr[], int k, int n);

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

	Heapsort(randnum, n);	// 힙정렬 함수 호출
	print(randnum, n);		// 정렬후 데이터 출력

	free(randnum);			// 동적할당된 배열 해제
}

void Heapsort(int arr[], int n) {
	int tmp;
	buildHeap(arr, n);						//주어진 배열을 힙으로 만들기
	for (int i = n; i >= 1; i--) {		
		tmp = arr[0];						//루트값과 마지막 노드 교환해서
		arr[0] = arr[i];
		arr[i] = tmp;
		heapify(arr, 0, i - 1);				//루트값 빼고 나머지를 다시 힙으로 만들기
	}
}

//arr[]배열을 힙으로 만드는 함수
void buildHeap(int arr[], int n) {
	for (int i = n / 2; i >= 0; i--) {		//마지막 노드 위층의(자식을 가진)최우측 노드부터 수행
		heapify(arr, i, n);					//arr[i]와 그 자식을 힙 성질을 만족하도록 수선한다
	}
}

// arr[k]와 그 자식을 힙성질 만족하도록 수선하는 함수
void heapify(int arr[], int k, int n) {				//k는 내가 쳐다볼 노드, n은 최대 인덱스(arr배열의 전체 크기)
	int left = 2 * k; int right = 2 * k + 1;		//k의 왼쪽, 오른쪽 자식노드들 설정
	int bigger, tmp;

	if (right <= n) {								//k가 두 자식을 가지는 경우				
		if (arr[left] > arr[right])				
			bigger = left;
		else
			bigger = right;
	}
	else if (left <= n) bigger = left;				//k가 왼쪽 자식만 있는 경우
	else return;									//k가 자식이 없는 경우
	

	if (arr[bigger] > arr[k]) {						//찾은 bigger가 k보다 크면
		tmp = arr[k];
		arr[k] = arr[bigger];
		arr[bigger] = tmp;
		heapify(arr, bigger, n);					//자리가 바뀐 bigger을 기준으로 다시 수선작업(heapify)
	}
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

