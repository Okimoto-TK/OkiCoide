#include <stdio.h>
#include <bitset>
#include <algorithm>
#include <vector>
using namespace std;
int k, n, ans = -1;
int total;
int val[(1 << 16) + 7];
int a[20];
int b[100007];
int f[(1 << 16) + 7];
int pre[100007];
vector <int> e[20];
int count(int bin)
{
    int r;
    for(r = 0; bin; r++)
    {
        bin &= (bin - 1);
    }
    return r;
}
int getSum(int bin)
{
    int sum = 0;
    for(int x = 1, l = 1; x < 1 << k; x <<= 1, l++)
    {
        sum += (bin & x) ? a[l] : 0;
    }
    return sum;
}
int half(int x, int l, int r, int y)
{
    int ans = l;
    while(l <= r)
    {
        int mid = (l + r) / 2;
        if(pre[mid] - y <= x)
        {
            l = mid + 1;
            ans = mid;
        }
        else
        {
            r = mid - 1;
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d", &k, &n);
    for(int i = 1; i <= k; i++)
    {
        scanf("%d", &a[i]);
        total += a[i];
    }
    f[0] = 0;
    for(int bin = 0; bin < 1 << k; bin++)
    {
        e[count(bin)].push_back(bin);
        val[bin] = getSum(bin);
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
        pre[i] = pre[i - 1] + b[i];
    }
    for(int i = 1; i <= k; i++)
    {
        int len = e[i].size();
        for(int j = 0; j < len; j++)
        {
            int bin = e[i][j];
            for(int l = 0, x = 1; x < 1 << k; x <<= 1, l++)
            {
                if((bin & x) == 0)
                {
                    continue;
                }
                int _bin = bin ^ x;
                int end = half(a[l + 1], f[_bin], n, pre[f[_bin]]);
                f[bin] = max(f[bin], end);
                if(end >= n)
                {
                    ans = max(total - val[bin], ans);
                }
            }
        }
    }
    printf("%d", ans);
    return 0;
}
