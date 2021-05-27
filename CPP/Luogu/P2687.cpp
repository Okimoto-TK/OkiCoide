#include <cstdio>
#define N 5002
struct Node
{
    int lis;
    double cnt;
    Node()
    {
        lis = 1;
        cnt = 1;
    }
} f[N];
int n;
int a[N];
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 2; i <= n; i++)
    {
        for(int j = 1; j < i; j++)
        {
            if(a[j] > a[i])
            {
                if(f[j].lis + 1 == f[i].lis) f[i].cnt += f[j].cnt;
                else if(f[j].lis + 1 > f[i].lis)
                {
                    f[i].lis = f[j].lis + 1;
                    f[i].cnt = f[j].cnt;
                }
            }
        }
        for(int j = 1; j < i; j++)
        {
            if(a[j] == a[i])
            {
                if(f[j].lis == f[i].lis)
                {
                    f[j].cnt = f[j].lis = 0;
                }
            }
        }
    }
    int lis = 0;
    double cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(f[i].lis > lis)
        {
            lis = f[i].lis;
            cnt = f[i].cnt;
        }
        else if(f[i].lis == lis) cnt += f[i].cnt;
    }
    if(cnt >= 1) printf("%d %.f", lis, cnt);
    else printf("%d %.f", lis, cnt);
    return 0;
}
