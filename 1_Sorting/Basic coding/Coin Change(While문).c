#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
//while�� �̿�
int main() 
{
	int change;
	int n500 = 0;
	int n100 = 0;
	int n50 =0;
	int n10 = 0;
	printf("1000�� �̸��� �Ž������� �Է��Ͻÿ�. ");
	scanf_s("%d", &change);

	while (change >= 500)
		change -= 500, n500++;
	while (change >= 100)
		change -= 100, n100++;
	while (change >= 50)
		change -= 50, n50++;
	while (change >= 10)
		change -= 10, n10++;
	
	printf("�Ž������� 500�� %d��, 100�� %d��, 50�� %d��, 10�� %d�� �Դϴ�", n500,n100,n50,n10);

}