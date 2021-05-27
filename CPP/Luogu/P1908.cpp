#include <stdio.h>
using namespace std;
int num[500007];
int temp[500007];
int n;
long long ans;
void merge(int l, int r)
{
    if(l == r)
    {
        return;
    }
    int mid = (l + r) >> 1;
    merge(l, mid);
    merge(mid + 1, r);
    int x = l;
    int y = mid + 1;
    for(int i = l; i <= r; i++)
    {
        if(x <= mid && (y > r || num[x] <= num[y]))
        {
            temp[i] = num[x++];
        }
        else
        {
            temp[i] = num[y++];
            ans += mid - x + 1;
        }
    }
    for(int i = l; i <= r; i++)
    {
        num[i] = temp[i];
    }
}
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &num[i]);
    }
    merge(0, n - 1);
    printf("%lld", ans);
    return 0;
}
