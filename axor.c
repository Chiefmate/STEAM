#include <stdio.h>
#define R 16 //배열 크기 
#define N 5  // 반복 횟수 
/*key는 창발, temp는 임시저장*/
int password[R][R];
int key[N+1][R+2][R+2], temp[R+2][R+2],k,i,j,z;
 
void lifegame(void);
void XOR_1(void);
void XOR_n(void);
void arr_print(int p);
void password_print(void);
 
int main(void)
{
    int pt_x;
    lifegame();
    for(z=1;z<=N; z++) arr_print(z);
    
    for(i = 0; i < R; i++)
    {
        for(j = 0; j < R; j++)
        {
            scanf("%d",&password[i][j]);
           }
    }
    XOR_1();
    XOR_n();
    
    for(z=1;z<=N; z++) arr_print(z);
    
    printf("\n password is ... \n");
    password_print();
    return 0;
}
 
void lifegame(void)
{
    /*입력*/
    for(i = 1; i <= R; i++)
    {
        for(j = 1 ;j <= R; j++)
        {
               scanf("%d", &key[0][i][j]); 
               temp[i][j] = 0;
        }
    }
    /*key[]에 창발 순서대로 배열*/
    for(k = 0; k <= N; k++)    
    {
        for(i = 1; i <= R; i++)
        {
            for(j = 1; j <= R; j++)
            {
                temp[i][j] = key[k][i-1][j-1] + key[k][i-1][j] + key[k][i-1][j+1] + key[k][i][j-1] 
                           + key[k][i][j+1] + key[k][i+1][j-1] + key[k][i+1][j] + key[k][i+1][j+1];
                if(key[k][i][j] == 0)
                    key[k+1][i][j] = temp[i][j] == 3 ? 1 : 0;
                else
                    key[k+1][i][j] = (temp[i][j] >= 4 || temp[i][j] <= 1) ? 0 : 1;
            }
        }
    }
}
 
/*1번 창발과 평문x -> XOR연산*/
void XOR_1(void)
{
    for(i = 1; i <= R; i++)
    {
        for(j = 1; j <= R; j++)
        {
         key[1][i][j] = (key[1][i][j] == password[i-1][j-1]) ? 0 : 1;
        }    
    }
}
/*배열사이의 XOR연산*/
void XOR_n(void)
{
    for(k = 1; k <= N; k++)
    {
        for(i = 1; i <= R; i++)
        {
            for(j = 1; j <= R; j++)
            {
             key[k+1][i][j] = (key[k+1][i][j] == key[k][i][j]) ? 0 : 1;
            }    
        }
    }
    for(i=1; i<=R; i++)
    {
        for(j=1; j<=R; j++)
        {
            password[i-1][j-1] = key[N+1][i][j];
        }
    }
}
 
/*key배열 출력*/
void arr_print(int p)
{
    printf("---NUMBER %d---\n",p);
    for(i = 1; i <= R; i++)
    {
        for(j = 1; j <= R; j++)
        {
            printf("%d ", key[p][i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
}
 
/*password 출력*/
void password_print(void)
{
for(i=0; i<R; i++)
    {
        for(j=0; j<R; j++)
        {
            printf("%d ",password[i][j]);
        }
        printf("\n");
    }
}

