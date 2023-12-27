#include<stdio.h>
#include<malloc.h>
/* ��� ��� ����
�Ʒ� ����� �ִ밪�� �׶��� ��θ� ����ϴ� ���α׷�
 6	7	12	5
 5	3	11	18
 7	17	3	3
 8	10	14	9
 ���: 6 �� 9�� ���� ���

(��) ��� ����
Max = 66
(1,1),(1,2),(2,2),(3,2),(4,2),(4,3),(4,4)
*/


int matrixPath(int a, int b, int m[4][4]);
int MAX(int a, int b);
void printPath(int** c, int a, int b);

int main() // ���� �Լ�
{
	// ��θ� ������ matrix �迭 ����
	int matrix[4][4] = { {6,7,12,5},{5,3,11,18},{7,17,3,3},{8,10,14,9} };
	int MAX = matrixPath(3, 3, matrix);


	printf("Max = ");
	printf("%d\n", MAX);

}
/* DP������ �� �ܰ��� ������ ������ �����ϰ� �� ������ ���踦 �����Ѵ�.
* �� �ܰ��� ������ ������ ���� ���̺��� ����� �ܰ踦 �÷� ������ ����ϰ� �����Ѵ�.
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

int MAX(int a, int b)	//max �Լ��� x, y�� �μ��� ���� 
{
	/* ���� ������ ����ϴ� ���
	* return (a>b) ? a:b;  
	* a�� b�� ���Ͽ� �� ū ���� a�̸� b�� ��ȯ, 	������ �����̸� b�� ��ȯ
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