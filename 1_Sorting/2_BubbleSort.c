#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

/*�ǽ�2 ��������
	- �Է� n(����ڷκ��� �Է¹���)
	- ó��: n���� ������ �߻�, n�� �������� �������� �˰������� ���� ����
	- ���: n�� ���� ��(���� ��), n�� ������(���� ��)
*/

int Bubblesort(int rand[], int n);

int main(void) {
	int n;
	scanf_s("%d", &n);

	srand((unsigned int)time(NULL));
	int* randnum;
	randnum = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		randnum[i] = rand() / (double)RAND_MAX * 1000;
		printf("%d ", randnum[i]);
	}
	printf("\n");

	Bubblesort(randnum, n);
	for (int i = 0; i < n; i++) {
		printf("%d ", randnum[i]);
	}
	free(randnum);
}



int Bubblesort(int rand[], int n) {
	int tmp;
	for (int last = n-1; last >= 1; last--) {	//�����ϴ� for����
		for (int i = 0; i < last-1; i++) {	//���ϴ� for����
			if (rand[i] > rand[i + 1]) {
				tmp = rand[i];
				rand[i] = rand[i + 1];
				rand[i + 1] = tmp;}
			
		}
	}
}