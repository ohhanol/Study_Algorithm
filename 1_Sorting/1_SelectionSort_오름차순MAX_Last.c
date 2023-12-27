#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

/*�ǽ�1 ��������
	- �Է� n(����ڷκ��� �Է¹���)
	- ó��: n���� ������ �߻�, n�� �������� �������� �˰��������� ���� ����
	- ���: n�� ���� ��(���� ��), n�� ������(���� ��)
*/

//MAX ã�� last�� �����ϴ� ���
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
	for (int last = n - 1; last >= 1; last--) {	//�� �����ʿ� ������ �� �����ϴ� for����
		int max = 0;
		for (int i = 0; i < last; i++) {
			if (rand[max] < rand[i+1])
				max = i+1;
		}
		tmp = rand[last];
		rand[last] = rand[max];
		rand[max] = tmp;
	}
}