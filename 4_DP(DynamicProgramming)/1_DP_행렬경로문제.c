#include<stdio.h>
#include<malloc.h>
/* 행렬 경로 문제
아래 행렬의 최대값과 그때의 경로를 출력하는 프로그램
 6	7	12	5
 5	3	11	18
 7	17	3	3
 8	10	14	9
 경로: 6 → 9로 가는 경로

(예) 출력 형태
Max = 66
(1,1),(1,2),(2,2),(3,2),(4,2),(4,3),(4,4)
*/


int matrixPath(int a, int b, int m[4][4]);
int MAX(int a, int b);
void printPath(int** c, int a, int b);

int main() // 메인 함수
{
	// 경로를 저장할 matrix 배열 선언
	int matrix[4][4] = { {6,7,12,5},{5,3,11,18},{7,17,3,3},{8,10,14,9} };
	int MAX = matrixPath(3, 3, matrix);


	printf("Max = ");
	printf("%d\n", MAX);

}
/* DP에서는 각 단계의 최적해 변수를 정의하고 그 변수의 관계를 정의한다.
* 각 단계의 최적해 변수에 대한 테이블을 만들어 단계를 늘려 나가며 계산하고 저장한다.
*/
int matrixPath(int a, int b, int m[4][4])
{
	int i, j;

	int** c = (int**)malloc(sizeof(int*) * (a + 1));
	for (i = 0; i < a + 1; i++)
		c[i] = (int*)malloc(sizeof(int) * (b + 1));

	c[0][0] = m[0][0];

	for (i = 1; i <= a; i++)
		c[i][0] = m[i][0] + c[i - 1][0];

	for (j = 1; j <= b; j++)
		c[0][j] = m[0][j] + c[0][j - 1];

	for (i = 1; i <= a; i++)
		for (j = 1; j <= b; j++)
			c[i][j] = m[i][j] + MAX(c[i - 1][j], c[i][j - 1]);

	for (int i = 0; i <= a; i++) {
		for (int j = 0; j <= b; j++) {
			printf(" %d ", c[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printPath(c, a, b);

	return c[a][b];
}

int MAX(int a, int b)	//max 함수는 x, y를 인수로 받음 
{
	/* 조건 연산자 사용하는 방법
	* return (a>b) ? a:b;  
	* a와 b를 비교하여 더 큰 값이 a이면 b를 반환, 	조건이 거짓이면 b를 반환
	*/

	if (a > b)
		return a;
	else
		return b;
}

void printPath(int** c, int a, int b)
{
	int i = 0, j = 0;
	printf("(1,1) ");

	while (1)
	{
		if (c[i + 1][j] > c[i][j + 1])
			i = i + 1;
		else
			j = j + 1;

		printf(" (%d,%d) ", i + 1, j + 1);

		if (i == (a) && j == (b))
			break;
	}
	printf("\n");
}