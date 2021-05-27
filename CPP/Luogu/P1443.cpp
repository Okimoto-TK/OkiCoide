#include <stdio.h>
using namespace std;
int n, m, x, y;
int tab[402][402];
int getLen(int num){
    int ans = 0;
    if(num == 0)
        return 1;
    while(num != 0){
        ans ++;
        num /= 10;
    }
    return ans;
}
void init(){
    for(int i = 0; i < 402; i ++)
        for(int j = 0; j < 402; j ++)
            tab[i][j] = 10000;
}
inline void write(int x)        
{        
    if(x < 0) {        
        putchar('-');        
        x = -x;        
    }        
    if(x > 9)        
        write(x/10);        
    putchar(x % 10 + '0');        
    return;        
}
inline void write(){
    putchar(' ');
    return;
}
inline void dfs(int x_, int y_, int sum){
    if(sum >= tab[x_][y_])
        return;
    else
        tab[x_][y_] = sum;
    if(x_ - 1 >= 1 && y_ + 2 <= m)
        dfs(x_ - 1, y_ + 2, sum + 1);
    if(x_ - 2 >= 1 && y_ - 1 >= 1)
        dfs(x_ - 2, y_ - 1, sum + 1);
    if(x_ + 1 <= n && y_ - 2 >= 1)
        dfs(x_ + 1, y_ - 2, sum + 1);
    if(x_ + 1 <= n && y_ + 2 <= m)
        dfs(x_ + 1, y_ + 2, sum + 1);
    if(x_ - 1 >= 1 && y_ - 2 >= 1)
        dfs(x_ - 1, y_ - 2, sum + 1);
    if(x_ - 2 >= 1 && y_ + 1 <= m)
        dfs(x_ - 2, y_ + 1, sum + 1);
    if(x_ + 2 <= n && y_ - 1 >= 1)
        dfs(x_ + 2, y_ - 1, sum + 1);
    if(x_ + 2 <= n && y_ + 1 <= m)
        dfs(x_ + 2, y_ + 1, sum + 1);
}
int main(int argc, char const *argv[])
{
    init();
    scanf("%d %d %d %d", &n, &m, &x, &y);
    dfs(x, y, 0);
    for(register int i = 1; i <= n; i ++){
        for(register int j = 1; j <= m; j ++){
            if(tab[i][j] != 10000){
                write(tab[i][j]);
                for(int k = 0; k < 5 - getLen(tab[i][j]); k ++)
                    write();
            }
            else{
                write(-1);
                write();
                write();
                write();
            }
        }
        printf("\n");
    }
    return 0;
}