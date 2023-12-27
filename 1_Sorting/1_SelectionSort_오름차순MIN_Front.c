#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

/*�ǽ�1 ��������
	- �Է� n(����ڷκ��� �Է¹���)
	- ó��: n���� ������ �߻�, n�� �������� �������� �˰������� ���� ����
	- ���: n�� ���� ��(���� ��), n�� ������(���� ��)
*/

//MIN ã�� Front�� �����ϴ� ���
int Selectionsort(int rand[], int n);

void main() {
	int n;
	scanf_s("%d", &n);	//����ڿ��� �Է¹��� �� n

	/*------------------------------------------------------------------*/
	srand((unsigned int)time(NULL));

	int* randnum;
	randnum = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		randnum[i] = rand() / (double)RAND_MAX * 1000;
		printf("%d ", randnum[i]);
	}
	/*----------����ڿ��� ���� n �Է¹޾� �׸�ŭ�� ������ �߻���Ŵ ---------*/
	printf("\n");

	Selectionsort(randnum, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", randnum[i]);
	}
	free(randnum);
}


int Selectionsort(int rand[], int n) {
	int tmp;
	for (int front = 0; front <n-1; front++) {
		int min = n-1;
		for (int i = min; i >front; i--) {
			if (rand[min] > rand[i - 1])
				min = i - 1;
		}
		tmp = rand[front];
		rand[front] = rand[min];
		rand[min] = tmp;
	}
}