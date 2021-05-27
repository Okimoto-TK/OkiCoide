#include <stdio.h>
using namespace std;
int n, p;
int x, y, t;
int num;
char ch[16];
inline void exgcd(int a, int b){
    if(a % b == 0){
        x = 0;
        y = 1;
    }
    else{
        exgcd(b, a % b);
        t = x;
        x = y;
        y = t - (a / b) * y;
    }
}
int main()
{
    scanf("%d%d", &n, &p);
    for(register int i = 1; i <= n; ++ i){
        exgcd(i, p);
        if(x < 0)
            x += p;
        num = 0;
        while(x) ch[++num]=x%10+'0',x/=10;
        while(num) putchar(ch[num--]);
        putchar('\n');
    }
    return 0;
}