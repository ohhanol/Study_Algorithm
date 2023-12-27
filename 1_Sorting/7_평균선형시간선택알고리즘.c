#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define True 1
#define False 0
/*
��� �����ð� ���þ˰��� ���� �� �м�
�Է�: n, i
����: n�� ���� �� �߻�, i ��° ���� �� ����
���: n�� ���� ��, i ��° ���� ��
*/

void countingSort(int* arr, int k, int n);
void print(int arr[], int n);

int main(void) {
	int n; int k;
	printf("n: ");	scanf_s("%d", &n);
	printf("k: ");	scanf_s("%d", &k);

	srand((unsigned int)time(NULL));			//�������� �ʱ�ȭ
	int* randnum;								//������ ���� ����
	randnum = (int*)malloc(sizeof(int) * n);	//������ ���� �迭 ũ�� �����Ҵ�

	for (int i = 0; i < n; i++) {
		randnum[i] = (rand() % k) + 1;
	}

	print(randnum, n);		//������ ������ ���
	printf("\n");

	countingSort(randnum, k, n);	//�������� �Լ� ȣ��
	print(randnum, n);		//������ ������ ���

	free(randnum);			//�����Ҵ�� �迭 ����
}


void countingSort(int* arr, int k, int n) {
	int i;
	int* result; int* grade;
	result = (int*)malloc(sizeof(int) * n);
	grade = (int*)malloc(sizeof(int) * k);
	for (i = 0; i < k; i++)
		grade[i] = 0;
	for (i = 0; i < n; i++)
		grade[arr[i]]++;
	for (i = 1; i < k; i++)
		grade[i] = grade[i] + grade[i - 1];
	for (i = n - 1; i >= 0; i--) {
		result[grade[arr[i]] - 1] = arr[i];
		grade[arr[i]]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = result[i];
}

void print(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
}