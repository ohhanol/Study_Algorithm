#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
/*
 Counting Sort ���� �� �м�
�Է�: n, k
����: �ִ� k������ �ڿ��� n�� ���� �߻�, n�� ���� �� ��������
���: n�� ���� ��(���� ��), n�� ���� ��(���� ��)
*/

int partition(int arr[], int p, int r);
int select(int arr[], int p, int r, int i);
void print(int arr[], int n);

int main(void) {
	int n; int i;
	printf("n: ");	scanf_s("%d", &n);			//�߻���ų ������ �Է�
	printf("i: ");	scanf_s("%d", &i);			//���° ���� �� ã������ �Է�

	srand((unsigned int)time(NULL));			//�������� �ʱ�ȭ
	int* randnum;								//������ ���� ����
	randnum = (int*)malloc(sizeof(int) * n);	//������ ���� �迭 ũ�� �����Ҵ�

	for (int i = 0; i < n; i++) {
		randnum[i] = (int)(rand() / (double)RAND_MAX * 1000);
	}

	print(randnum, n);		
	printf("\n");

	int x = select(randnum, 0, n - 1, i);	//���þ˰��� �Լ� ȣ��
	printf("\n%d���� ������ �߻�, %d��° ���� ��: %d \n", n, i, x);

	free(randnum);			//�����Ҵ�� �迭 ����
}

int select(int arr[], int p, int r, int i) {	//arr�迭���� i��° ���� ���Ҹ� ã�´�
	if (p == r)								//���Ұ� �ϳ����� ��� i�� �ݵ�� 1
		return arr[p];
	int q = partition(arr, p, r);			//�������� ��Ƽ�� �Լ��� ����
	int k = q - p + 1;						//���ؿ��� q�� arr[]���� k��° ���� �������� �ǹ�
	if (i < k)								//���� �׷����� ������ ����
		return select(arr, p, q - 1, i);
	else if (i == k)						//���� ���Ұ� �ٷ� ã�� ������ ��
		return arr[q];
	else									//������ �׷����� ������ ����
		return select(arr, q + 1, r, i - k);
}

int partition(int arr[], int p, int r) {
	int pivot = arr[r];						//�Ǻ�
	int tmp;
	int i = p - 1;							//i�� 1����(�Ǻ����� ����)�� ������
	for (int j = p; j <= r - 1; j++) {		//j�� 3����(���� ���� ��)�� ������
		if (arr[j] <= pivot) {				//�����ϰ��� �ϴ� ���� < �Ǻ� �̸�
			tmp = arr[++i];					//1���� ������ �ε����� �ϳ� ���� ��
			arr[i] = arr[j];				//�����ϰ��� �ϴ� ���ҿ� ��ȯ
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


