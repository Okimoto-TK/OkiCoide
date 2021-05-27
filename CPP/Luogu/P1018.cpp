#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct bigint
{
    int num[107];
    int len;
    bigint()
    {
        memset(num, 0, sizeof(num));
        len = 0;
    }
    void print()
    {
        if(len == 0)
        {
            printf("0");
            return;
        }
        bool zero = false;
        for(int i = len - 1; i >= 0; i--)
        {
            if(zero)
            {
                if(num[i] < 1000 && num[i] >= 100)
                {
                    printf("0");
                }
                else if(num[i] < 100 && num[i] >= 10)
                {
                    printf("00");
                }
                else if(num[i] < 10)
                {
                    printf("000");
                }
            }
            if(num[i] != 0)
            {
                zero = true;
            }
            printf("%d", num[i]);
        }
        if(!zero)
        {
            printf("0");
        }
    }
};
bool comp(bigint a, bigint b)
{
    if(a.len != b.len)
    {
        return a.len > b.len;
    }
    for(int i = a.len - 1; i >= 0; i--)
    {
        if(a.num[i] != b.num[i])
        {
            return a.num[i] > b.num[i];
        }
    }
    return true;
}
bigint add(bigint a, bigint b)
{
    int x = 0;
    bigint c;
    c.len = max(a.len, b.len);
    for(int i = 0; i < c.len; i++)
    {
        c.num[i] = a.num[i] + b.num[i] + x;
        x = 0;
        if(c.num[i] >= 10000)
        {
            x = 1;
            c.num[i] -= 10000;
        }
    }
    if(x == 1)
    {
        c.num[c.len++] = 1;
    }
    return c;
}
bigint ten(bigint x, int y)
{
    for(int i = x.len - 1; i >= 0; i--)
    {
        x.num[i + y] = x.num[i];
    }
    for(int i = 0; i < y; i++)
    {
        x.num[i] = 0;
    }
    x.len += y;
    return x;
}
bigint max(bigint a, bigint b)
{
    if(comp(a, b))
    {
        return a;
    }
    return b;
}
bigint tobig(long long x)
{
    bigint r;
    while(x)
    {
        r.num[r.len++] = x % 10000;
        x /= 10000;
    }
    return r;
}
bigint multi(bigint a, bigint b)
{
    if(a.len == 0 || b.len == 0)
    {
        return bigint();
    }
    bigint c;
    for(int i = 0; i < a.len; i++)
    {
        for(int j = 0; j < b.len; j++)
        {
            long long t = a.num[i] * b.num[j];
            bigint _t = tobig(t);
            _t = ten(_t, i + j);
            c = add(c, _t);
        }
    }
    return c;
}
int n, k;
int a[50];
bigint f[50][50][10];
int getNum(int i, int j)
{
    int num = 0;
    bool zero = false;
    for(int x = i; x <= j; x++)
    {
        if(a[x] == 0 && !zero)
        {
            continue;
        }
        zero = true;
        num *= 10;
        num += a[x];
    }
    return num;
}
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        scanf("%1d", &a[i]);
    }
    for(int len = 1; len <= n; len++)
    {
        for(int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for(int k = j; k >= i; k -= 4)
            {
                int _k = max(i, k - 4 + 1);
                f[i][j][0].num[f[i][j][0].len++] = getNum(_k, k);
            }
        }
    }
    for(int len = 2; len <= n; len++)
    {
        for(int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for(int use = 1; use <= k; use++)
            {
                for(int k = 0; use - k - 1 >= 0; k++)
                {
                    for(int m = i; m < j; m++)
                    {
                        f[i][j][use] = max(f[i][j][use], multi(f[i][m][k], f[m + 1][j][use - k - 1]));
                    }
                }
            }
        }
    }
    f[1][n][k].print();
    return 0;
}
