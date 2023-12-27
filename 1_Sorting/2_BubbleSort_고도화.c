#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
���� 2 (�������� ��ȭ)
�Է�: n  (����ڷκ��� n�� �Է� ����)
ó��: n�� ���� �� �߻�, n�� ���� ���� �������� ��ȭ �˰������� ���� ����
ppt 3, 4 �������� main�� random �Լ� �����Ͽ� ���α׷� �ۼ�
�������� ��ȭ �˰����� ���� 92������ ����
���: : n�� ���� ��(���� ��), n�� ���� ��(���� ��)
*/

#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0

void Bubblesort(int arr[], int n);
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

	Bubblesort(randnum, n);	//�������� �Լ� ȣ��
	print(randnum, n);		//������ ������ ���

	free(randnum);			//�����Ҵ�� �迭 ����
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