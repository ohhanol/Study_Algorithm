#include <stdio.h>
//for문 사용해 거스름돈 알고리즘 구현
int main() {
	int change;
	int coin[5] = { 500,100,50,10 };
	int coinnum[5];
	printf("1000원 미만의 거스름돈을 입력하시오.");
	scanf_s("%d", &change);	//ex. 720원

	printf("거스름돈은");
	for (int i = 0; i <= 4; i++) {
		coinnum[i] = change / coin[i];	//coinnum[0] <- 720/500 == 500원짜리 1개!
		change = change % coin[i];
		printf("%d원 %d개 ", coin[i], coinnum[i]);
	}
	printf("입니다");
	};