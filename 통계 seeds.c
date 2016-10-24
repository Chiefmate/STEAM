#include <stdio.h>
#define R 3 //배열 크기 
#define N 5  // 반복 횟수 
#define Case (1<<(R*R))
/*password: 암호, number: 자연수, key: 창발, temp: 임시저장, st: 통계*/
int password[Case+1][R][R], number[Case], key[N+1][R+2][R+2], temp[R+2][R+2], st[Case];
/*(k,i,j): 반복 , num: 순서*/
int k, i, j, num;
void initialize(void);
void Case_scan(void);
void control(void);
void lifegame(void);
void XOR(void);
void arr_print(int p);
void password_print(void);
void stats(void); 
 
int main(void)
{  
    initialize();
    Case_scan();
    stats();
    return 0;
}
 
/*자연수 데이터 Case개*/
void initialize(void)
{
    for(k=0;k<Case;k++) number[k] = k;
}
 
/*모든 경우의 수 대입*/
void Case_scan(void)
{
     int temp_number,x,y,z;
     for(x=0; x<Case; x++)
     {
        temp_number = number[x];
         for(y=1;y<=R;y++)
         {
            for(z=1; z<=R; z++)
            {
                key[0][y][z] = temp_number & 1;
                temp_number = temp_number >> 1;
            }
        }
        control();
    }
}
 
/*생명게임, XOR연산, 암호 출력*/
void control(void)
{
    lifegame(); 
    XOR();
    password_print();
}
 
/*생명게임*/
void lifegame(void)
{
    /*콘웨이의 생명게임 데이터 저장*/
    for(k = 0; k <= N; k++)    
    {
        for(i = 1; i <= R; i++)
        {
            for(j = 1; j <= R; j++)
            {
                temp[i][j] = key[k][i-1][j-1] + key[k][i-1][j] + key[k][i-1][j+1] + key[k][i][j-1] 
                           + key[k][i][j+1] + key[k][i+1][j-1] + key[k][i+1][j] + key[k][i+1][j+1];
                if(key[k][i][j] == 0)
                    key[k+1][i][j] = temp[i][j] == 2 ? 1 : 0;
                else
                    key[k+1][i][j] = 0;
            }
        }
    }
}
 
/*n번 창발과 n+1번 창발 사이의 XOR연산*/
void XOR(void)
{
    for(k = 0; k <= N; k++)
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
               password[num][i-1][j-1] = key[N+1][i][j];
        }
    }
}
 
/*password 출력*/
void password_print(void)
{
    printf("\nNUMBER : %d\n",num);
    printf("-------------\n");
    for(i=0; i<R; i++)
    {
        for(j=0; j<R; j++)
        {
            printf("%d ",password[num][i][j]);
        }
        printf("\n");
    }
    printf("-------------\n");
    num++;
}
 
/*통계*/
void stats(void)
{
    int result,bi;
    num=0;
    while(num<Case)
    {
        result = 0;
        bi=1;
        /*저장된 패턴을 10진수로 변환*/
        for(i=0;i<R;i++)
        {
            for(j=0;j<R;j++)
            {
                result += bi * password[num][i][j];
                bi *= 2;
            }
        }
        //
        num++;
        st[result]++;
    }
    result = 0;
    /*10진수의 값으로 통계 출력*/
    for(k=0; k<Case; k++)
    {
        if (k % 5 == 0) printf("\n"); // 5개씩 출력 
        result += st[k];
        printf("st%d : %d   ", k, st[k]);
    }
    printf("\nDATA : %d\n",result); // 결과 확인 
}
