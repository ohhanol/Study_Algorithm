#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
/*
���� 3 (��������)
�Է�: n  (����ڷκ��� n�� �Է� ����)
ó��: n�� ���� �� �߻�, n�� ���� ���� �������� �˰������� ���� ����
ppt 3, 4 �������� main�� random �Լ� �����Ͽ� ���α׷� �ۼ�
���: : n�� ���� ��(���� ��), n�� ���� ��(���� ��)
*/

#define True 1
#define False 0

void insertsort(int arr[], int n);
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

	insertsort(randnum, n);	//�������� �Լ� ȣ��
	print(randnum, n);		//������ ������ ���

	free(randnum);			//�����Ҵ�� �迭 ����
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