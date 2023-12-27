#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
�ǽ� 1 (��������)
�Է�: n  (����ڷκ��� n�� �Է� ����)
ó��: n�� ���� �� �߻�, n�� ���� ���� �������� �˰������� ���� ���� 
ppt 2, 3 �������� main�� random �Լ� �����Ͽ� ���α׷� �ۼ�
���: : n�� ���� ��(���� ��), n�� ���� ��(���� ��)

*/


int selectionSort(int A[], int n);
int main(void)
{
	srand((unsigned int)time(NULL));
	int a;
	scanf_s("%d", &a);

	int* randomnum;
	randomnum = (int*)malloc(sizeof(int) * a);
	for (int i = 0; i < a; i++) {
		randomnum[i]= rand() / (double)RAND_MAX * 1000;
	}
	for (int i = 0; i < a; i++) {
		printf("%d ", randomnum[i]);
	}
	printf("\n");
	selectionSort(randomnum, a);

	for (int i = 0; i < a; i++) {
		printf("%d ", randomnum[i]);
	}

	free(randomnum);
}

int selectionSort(int A[], int n) {
	int max, tmp;
	for (int last = n - 1; last >= 1; last--) {
		max = 0;
		for (int i = 0; i < last; i++) {
			if (A[max] < A[i+1]) {
				max = i+1;
			}
		}
		tmp = A[last];
		A[last] = A[max];
		A[max] = tmp;
	}
}