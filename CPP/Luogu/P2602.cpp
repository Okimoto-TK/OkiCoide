#include <stdio.h>
using namespace std;
long long a, b;
long long ans[2][10];
int main()
{
    scanf("%lld", &a);
    a -= 1;
    for(long long x = 0; x <= 9; x++)
    {
        for(long long i = 1; i <= a; i *= 10)
        {
            long long bfr = a / (i * 10);
            long long aft = a % i;
            long long pos = a / i % 10;
            if(x)
            {
                if(x < pos)
                {
                    ans[0][x] += (bfr + 1) * i;
                }
                else if(x == pos)
                {
                    ans[0][x] += bfr * i + aft + 1;
                }
                else
                {
                    ans[0][x] += bfr * i;
                }
            }
            else
            {
                if(pos == 0)
                {
                    ans[0][x] += (bfr - 1) * i + aft + 1;
                }
                else
                {
                    ans[0][x] += bfr * i;
                }
            }
        }
    }
    scanf("%lld", &b);
    for(long long x = 0; x <= 9; x++)
    {
        for(long long i = 1; i <= b; i *= 10)
        {
            long long bfr = b / (i * 10);
            long long aft = b % i;
            long long pos = b / i % 10;
            if(x)
            {
                if(x < pos)
                {
                    ans[1][x] += (bfr + 1) * i;
                }
                else if(x == pos)
                {
                    ans[1][x] += bfr * i + aft + 1;
                }
                else
                {
                    ans[1][x] += bfr * i;
                }
            }
            else
            {
                if(pos == 0)
                {
                    ans[1][x] += (bfr - 1) * i + aft + 1;
                }
                else
                {
                    ans[1][x] += bfr * i;
                }
            }
        }
    }
    for(long long i = 0; i <= 9; i++)
    {
        printf("%lld ", ans[1][i] - ans[0][i]);
    }
    return 0;
}
