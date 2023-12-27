#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0
/*
���� 2(������)
�Է�: n  (����ڷκ��� n�� �Է� ����)
ó��: n�� ���� �� �߻�, n�� ���� ���� ������ �˰������� ���� ����
ppt 3, 4 �������� main�� random �Լ� �����Ͽ� ���α׷� �ۼ�
���: : n�� ���� ��(���� ��), n�� ���� ��(���� ��)
*/

void Heapsort(int arr[], int n);
void buildHeap(int arr[], int n);
void heapify(int arr[], int k, int n);

void Mergesort(int arr[], int p, int r);	//���ҽ�Ű�� �Լ�
void Merge(int arr[], int p, int q, int r);	//�պ���Ű�� �Լ�
void print(int arr[], int n);

int main(void) {
	int n;
	scanf_s("%d", &n);

	srand((unsigned int)time(NULL));			// �������� �ʱ�ȭ
	int* randnum;								// ������ ���� ����
	randnum = (int*)malloc(sizeof(int) * n);	// ������ ���� �迭 ũ�� �����Ҵ�
	for (int i = 0; i < n; i++) {
		randnum[i] = (int)rand() / (double)RAND_MAX * 1000;	// �߻���Ų �������� randomnum �迭�� ����
	}
	print(randnum, n);		// ������ ������ ���
	printf("\n");

	Heapsort(randnum, n);	// ������ �Լ� ȣ��
	print(randnum, n);		// ������ ������ ���

	free(randnum);			// �����Ҵ�� �迭 ����
}

void Heapsort(int arr[], int n) {
	int tmp=0;
	buildHeap(arr, n);						//�־��� �迭�� ������ �����
	for (int i = n-1 ; i >= 1; i--) {
		tmp = arr[i];						//��Ʈ���� ������ ��� ��ȯ�ؼ�
		arr[i] = arr[0];
		arr[0] = tmp;
		heapify(arr, 0, i - 1);				//��Ʈ�� ���� �������� �ٽ� ������ �����
	}
}

//arr[]�迭�� ������ ����� �Լ�
void buildHeap(int arr[], int n) {
	for (int i = n / 2; i >= 0; i--) {		//������ ��� ������(�ڽ��� ����)�ֿ��� ������ ����
		heapify(arr, i, n);					//arr[i]�� �� �ڽ��� �� ������ �����ϵ��� �����Ѵ�
	}
}

// arr[k]�� �� �ڽ��� ������ �����ϵ��� �����ϴ� �Լ�
void heapify(int arr[], int k, int n) {				//k�� ���� �Ĵٺ� ���, n�� �ִ� �ε���(arr�迭�� ��ü ũ��)
	int left = 2 * k; int right = 2 * k + 1;		//k�� ����, ������ �ڽĳ��� ����
	int smaller, tmp;

	if (right <= n) {								//k�� �� �ڽ��� ������ ���				
		if (arr[left] < arr[right])
			smaller = left;
		else
			smaller = right;
	}
	else if (left <= n) smaller = left;				//k�� ���� �ڽĸ� �ִ� ���
	else return;									//k�� �ڽ��� ���� ���


	if (arr[smaller] < arr[k]) {						//ã�� smaller�� k���� ������
		tmp = arr[k];
		arr[k] = arr[smaller];
		arr[smaller] = tmp;
		heapify(arr, smaller, n);					//�ڸ��� �ٲ� smaller�� �������� �ٽ� �����۾�(heapify)
	}
}
void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}
void Mergesort(int arr[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;		// ��� �κ� = q
		Mergesort(arr, p, q);		// ���� ����
		Mergesort(arr, q + 1, r);	// ������ ����
		Merge(arr, p, q, r);		// �պ�
	}
}
void Merge(int arr[], int p, int q, int r) {
	int i = p;		// ���� ��� index ���
	int j = q + 1;	// ������ ��� index ���
	int t = 0;		// ���� ����� ä�� ���� ��ġ

	int* tmp;	// ���� ����� ä�� �迭 �����Ҵ�
	tmp = (int*)malloc(sizeof(int) * (r - p + 1));



	// ���� �˰���
	while (i <= q && j <= r) {		// i�� ������ �� �������� AND j�� ������ �� �� ������
		if (arr[i] >= arr[j])		// ���������̹Ƿ� i(����)�� j(������)���� ũ��
			tmp[t++] = arr[i++];	// tmp�迭�� i��° ���Ҹ� �ְ� t�� i �ϳ��� ������Ű��
		else
			tmp[t++] = arr[j++];	//�ݴ��� ��쿣 tmp�� j��° ���Ҹ� �ְ� j �ϳ��� ������Ű��
	}


	/*
	�ݺ����� ������, �� ���� ������ ������ ����Ǵ� �ڵ�
	*/
	while (i <= q)
		tmp[t++] = arr[i++];
	while (j <= r)
		tmp[t++] = arr[j++];


	i = p; t = 0;
	while (i <= r)	//tmp �迭�� arr�迭�� ����
		arr[i++] = tmp[t++];
	free(tmp);

}

