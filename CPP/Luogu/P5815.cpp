#include <cstdio>
#include <algorithm>
int a[60];
int n;
bool check(int x)
{
    long long cnt = 0; // Attention! **cnt** must be declared as a **long long** integer variable
    for(int i = 1; i <= n + 1; i++) cnt += std::max(x - a[i], 0);
    return cnt <= x;
}
int main()
{
    scanf("%d", &n);
    scanf("%d", &a[n + 1]);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int l = 0, r = 1e9;
    while(l + 1 < r)
    {
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid;
        else r = mid;
    }
    printf("%d", l);
    return 0;
}
