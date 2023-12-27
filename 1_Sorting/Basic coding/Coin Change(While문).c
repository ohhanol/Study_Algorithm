#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
//while문 이용
int main() 
{
	int change;
	int n500 = 0;
	int n100 = 0;
	int n50 =0;
	int n10 = 0;
	printf("1000원 미만의 거스름돈을 입력하시오. ");
	scanf_s("%d", &change);

	while (change >= 500)
		change -= 500, n500++;
	while (change >= 100)
		change -= 100, n100++;
	while (change >= 50)
		change -= 50, n50++;
	while (change >= 10)
		change -= 10, n10++;
	
	printf("거스름돈은 500원 %d개, 100원 %d개, 50원 %d개, 10원 %d개 입니다", n500,n100,n50,n10);

}