#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0
/*
�ǽ� 1 (��������)
�Է�: n  (����ڷκ��� n�� �Է� ����)
ó��: n�� ���� �� �߻�, n�� ���� ���� �������� �˰������� ���� ����
���: : n�� ���� ��(���� ��), n�� ���� ��(���� ��)
*/

void Mergesort(int arr[], int p, int r);	//���ҽ�Ű�� �Լ�
void Merge(int arr[], int p, int q, int r);	//�պ���Ű�� �Լ�
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

	Mergesort(randnum, 0,n-1);	//�������� �Լ� ȣ��
	print(randnum, n);		//������ ������ ���

	free(randnum);			//�����Ҵ�� �迭 ����
}



void Mergesort(int arr[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;	//��� �κ�=q
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