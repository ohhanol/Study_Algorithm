#include <stdio.h>
//for�� ����� �Ž����� �˰��� ����
int main() {
	int change;
	int coin[5] = { 500,100,50,10 };
	int coinnum[5];
	printf("1000�� �̸��� �Ž������� �Է��Ͻÿ�.");
	scanf_s("%d", &change);	//ex. 720��

	printf("�Ž�������");
	for (int i = 0; i <= 4; i++) {
		coinnum[i] = change / coin[i];	//coinnum[0] <- 720/500 == 500��¥�� 1��!
		change = change % coin[i];
		printf("%d�� %d�� ", coin[i], coinnum[i]);
	}
	printf("�Դϴ�");
	};