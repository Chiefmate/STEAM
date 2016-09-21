#include <stdio.h>
#define R 3 //배열 크기 
#define N 5  // 반복 횟수 
/*key는 창발, temp는 임시저장*/
int password[R][R];
int plaintext[R][R];
int key[N + 1][R + 2][R + 2], temp[R + 2][R + 2], k, i, j;

void lifegame(void);
void XOR(void);
void arr_print(int p);
void password_print(void);

int main(void)
{
	input_plain();
	printf("\n--------키를 입력하십시오-------------------\n");
	lifegame();
	for (k = 1; k <= N; k++) arr_print(k);
	XOR();
	for (k = 1; k <= N; k++) arr_print(k);
	XOR_last();
	password_print();
	return 0;
}

int input_plain(void)
{
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= R; j++){
			scanf_s("%d", &plaintext[i][j]);
		}
	}
}

void lifegame(void)
{
	/*입력*/
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= R; j++)
		{
			scanf_s("%d", &key[0][i][j]);
			temp[i][j] = 0;
		}
	}
	/*key[]에 창발 순서대로 배열*/
	for (k = 0; k <= N; k++)
	{
		for (i = 1; i <= R; i++)
		{
			for (j = 1; j <= R; j++)
			{
				temp[i][j] = key[k][i - 1][j - 1] + key[k][i - 1][j] + key[k][i - 1][j + 1] + key[k][i][j - 1]
					+ key[k][i][j + 1] + key[k][i + 1][j - 1] + key[k][i + 1][j] + key[k][i + 1][j + 1];
				if (key[k][i][j] == 0)
					key[k + 1][i][j] = temp[i][j] == 3 ? 1 : 0;
				else
					key[k + 1][i][j] = (temp[i][j] >= 4 || temp[i][j] <= 1) ? 0 : 1;
			}
		}
	}
}

/*XOR연산*/
void XOR(void)
{
	for (k = 0; k <= N; k++)
	{
		for (i = 1; i <= R; i++)
		{
			for (j = 1; j <= R; j++)
			{
				key[k + 1][i][j] = (key[k + 1][i][j] == key[k][i][j]) ? 0 : 1;
			}
		}
	}
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= R; j++)
		{
			password[i - 1][j - 1] = key[N + 1][i][j];
		}
	}
}

int XOR_last(void){
	for (i = 0; i <= N; i++){
		for (j = 0; j <= N; j++){
			if (password[i][j] != plaintext[i][j]){
				password[i][j] = 1;
			}
			else{
				password[i][j] = 0;
			}
		}
	}
}

/*key배열 출력*/
void arr_print(int p)
{
	printf("---NUMBER %d---\n", p);
	for (i = 1; i <= R; i++)
	{
		for (j = 1; j <= R; j++)
		{
			printf("%d ", key[p][i][j]);
		}
		printf("\n");
	}
	printf("----------------\n");
}

/*password 출력*/
void password_print(void)
{
	printf("\n---password--- \n");
	for (i = 0; i<R; i++)
	{
		for (j = 0; j<R; j++)
		{
			printf("%d ", password[i][j]);
		}
		printf("\n");
	}
	printf("-------------- \n");
}
