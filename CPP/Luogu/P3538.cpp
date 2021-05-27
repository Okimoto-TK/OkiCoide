#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
int n;
char buf[500007];
int q;
int a, b;
const int base = 37;
unsigned int power[500007];
unsigned int h[500007];
vector<int> fac[500007];
inline bool cmp(int a, int b)
{
    return a < b;
}
inline int read()
{
    int s=0;
    char c=getchar();
    while (c<'0' || c>'9') c=getchar();
    while (c>='0' && c<='9') s=s*10+c-'0',c=getchar();
    return s;
}
#define I_int int
char F[ 200 ] ;
inline void write( I_int x )
{
    I_int tmp = x > 0 ? x : -x ;
    if( x < 0 ) putchar( '-' ) ;
    int cnt = 0 ;
    while( tmp > 0 )
    {
        F[ cnt ++ ] = tmp % 10 + '0' ;
        tmp /= 10 ;
    }
    while( cnt > 0 ) putchar( F[ -- cnt ] ) ;
}
#undef I_int
int main()
{
    scanf("%d", &n);
    power[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        power[i] = power[i - 1] * base;
    }
    for(int i = 1; i <= n; i++)
    {
        int j = n / i;
        for(int k = 1; k <= j; k++)
        {
            fac[i * k].push_back(i);
        }
    }
    scanf("%s", buf);
    h[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        h[i] = h[i - 1] * base + buf[i - 1] - 'a';
    }
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        a = read();
        b = read();
        a--;
        b--;
        int len = b - a + 1;
        int siz = fac[len].size();
        for(int j = 0; j < siz; j++)
        {
            int l = fac[len][j];
            bool scs = true;
            unsigned int spl = h[a + l] - h[a];
            for(int k = 1; l * k <= len; k++)
            {
                if(h[a + l * k] - h[a + l * (k - 1)] != spl * power[(k - 1) * l])
                {
                    scs = false;
                    break;
                }
            }
            if(scs)
            {
                write(l);
                putchar('\n');
                break;
            }
        }
    }
    return 0;
}
