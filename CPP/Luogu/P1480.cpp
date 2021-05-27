#include <stdio.h>
#include <string.h>
using namespace std;
struct BigInt
{
    int num[20007];
    int len;
    BigInt()
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
        for(int i = len - 1; i >= 0; i--)
        {
            printf("%d", num[i]);
        }
    }
};
BigInt move(BigInt a, int x)
{
    for(int i = a.len - 1; i >= 0; i--)
    {
        a.num[i + x] = a.num[i];
    }
    for(int i = x - 1; i >= 0; i--)
    {
        a.num[i] = 0;
    }
    a.len += x;
    return a;
}
int comp(BigInt a, BigInt b)
{
    if(a.len > b.len)
    {
        return 1;
    }
    else if(a.len < b.len)
    {
        return -1;
    }
    else
    {
        for(int i = a.len - 1; i >= 0; i--)
        {
            if(a.num[i] > b.num[i])
            {
                return 1;
            }
            else if(a.num[i] < b.num[i])
            {
                return -1;
            }
        }
        return 0;
    }
}
BigInt minus(BigInt a, BigInt b)
{
    BigInt r = a;
    for(int i = 0; i < a.len; i++)
    {
        r.num[i] -= b.num[i];
        if(r.num[i] < 0)
        {
            r.num[i] += 10;
            r.num[i + 1] -= 1;
        }
    }
    while(r.len && r.num[r.len - 1] == 0)
    {
        r.len--;
    }
    return r;
}
char _a[20007];
char _b[20007];
int ans[20007];
BigInt a;
BigInt b;
int main()
{

    scanf("%s", _a);
    scanf("%s", _b);
    int len = strlen(_a);
    for(int i = 0; i < len; i++)
    {
        a.len++;
        a.num[len - a.len] = _a[i] - '0';
    }
    len = strlen(_b);
    for(int i = 0; i < len; i++)
    {
        b.len++;
        b.num[len - b.len] = _b[i] - '0';
    }
    if(comp(a, b) == -1)
    {
        printf("0");
        return 0;
    }
    for(int i = a.len; i >= 0; i--)
    {
        BigInt t = move(b, i);
        while(comp(a, t) >= 0)
        {
            a = minus(a, t);
            ans[i]++;
        }
    }
    bool zero = true;
    for(int i = 20006; i >= 0; i--)
    {
        if(ans[i] == 0 && !zero)
        {
            printf("0");
        }
        else if(ans[i] != 0)
        {
            printf("%d", ans[i]);
            zero = false;
        }
    }
    return 0;
}
