#include<stdio.h>
/* 행렬 곱셈 문제
문제: A1:8ⅹ128, A2:128ⅹ64, A3:64ⅹ256, A4:256ⅹ16, A5:16ⅹ8 (행렬의 원소 값은 난수로 채움)
행렬 곱셈 순서 표기
Ex)
최소 곱셈 수 = xxxx
(1,2), (3,4), (1,4), (5,6), (1,6)
*/


int Min(int A, int B); //곱셈 수 중 더 작은 수를 구하는 함수
int matrixChain(int P[], int n); //최소 곱셈 수를 구하는 함수 

int main() //메인 함수 
{
	int P[6] = { 8,128,64,256,16,8 };
	// 문제에서 행렬 5개는 A1=8128, A2=12864, A3=64256, A4=25616, A5=168과 같음.

	printf("최소 곱셈 수 : %d \n", matrixChain(P, 6));
	// 행렬곱 함수를 호출하여 결과값을 출력

	return 0;
}

int matrixChain(int P[], int n)
{
	int i, j; //행렬 곱 i번째부터 j번째까지 구하는 최소 비용을 구한다. 
	int r, k;
	int m[6][6] = { 0 };

	for (i = 1; i < n; i++)
		m[i][i] = 0;  //행렬이 하나뿐인 경우의 비용은 0이다

	for (r = 1; r < n - 1; r++) //r은 문제의 크기를 결정하는 변수. 문제의 크기는 r+1.
		for (i = 1; i < n - r; i++)
		{
			j = i + r;
			m[i][j] = m[i + 1][j] + P[i - 1] * P[i] * P[j];
			for (k = i + 1; k <= j - 1; k++)
			{
				m[i][j] = Min(m[i][j], m[i][k] + m[k + 1][j] + P[i - 1] * P[k] * P[j]); 
				//함수 Min으로 비교 후 더 작은 수를 m[i][j]에 넣는다.
			}
		}
	return m[1][n - 1]; //m[1][n-1]을 리턴한다. 
}
// i번째 행렬부터 j번째까지 행렬을 곱할 때 필요한 최소한의 곱셈 연산 횟수를 m[i][j]로 표현한다.
int Min(int A, int B)
{
	if (A > B) //만약 B가 더 작으면
		return B; //B를 리턴한다.
	else //만약 A가 더 작으면 
		return A; //A를 리턴한다. 
}




