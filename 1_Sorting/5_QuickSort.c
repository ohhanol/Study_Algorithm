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

	srand((unsigned int)time(NULL));			//�������� �ʱ�ȭ
	int* randnum;								//������ ���� ����
	randnum = (int*)malloc(sizeof(int) * n);	//������ ���� �迭 ũ�� �����Ҵ�
	for (int i = 0; i < n; i++) {
		randnum[i] = (int)rand() / (double)RAND_MAX * 1000;	//�߻���Ų �������� randomnum �迭�� ����
	}
	print(randnum, n);		//������ ������ ���
	printf("\n");

	quicksort(randnum, 0, n - 1);	//������ �Լ� ȣ��
	print(randnum, n);		//������ ������ ���

	free(randnum);			//�����Ҵ�� �迭 ����
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