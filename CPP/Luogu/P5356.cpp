#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#define N 100007
#define INF 2000000000
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9') {
        if (c == '-')f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
struct item
{
    int i;
    int v;
} _a[N];
int n, m, blocksize;
int a[N];
int L[N];
int R[N];
int B[N];
int T[N];
vector<int> vec[N];
bool cmp(item a, item b)
{
    return a.v < b.v;
}
bool _cmp(int a, int b)
{
    return a < b;
}
vector<int> :: iterator it;
void add(int l, int r, int v)
{
    int LB = B[l];
    int RB = B[r];
    if(RB - LB <= 1)
    {
        for(int i = l; i <= r; i++)
        {
            a[i] += v;
        }
        vec[LB].clear();
        for(int i = L[LB]; i <= R[LB]; i++)
        {
            vec[LB].push_back(a[i]);
        }
        sort(vec[LB].begin(), vec[LB].end(), _cmp);
        vec[RB].clear();
        for(int i = L[RB]; i <= R[RB]; i++)
        {
            vec[RB].push_back(a[i]);
        }
        sort(vec[RB].begin(), vec[RB].end(), _cmp);
        return;
    }
    for(int i = LB + 1; i < RB; i++)
    {
        T[i] += v;
    }
    for(int i = l; i <= R[LB]; i++)
    {
        a[i] += v;
    }
    vec[LB].clear();
    for(int i = L[LB]; i <= R[LB]; i++)
    {
        vec[LB].push_back(a[i]);
    }
    sort(vec[LB].begin(), vec[LB].end(), _cmp);
    for(int i = L[RB]; i <= r; i++)
    {
        a[i] += v;
    }
    vec[RB].clear();
    for(int i = L[RB]; i <= R[RB]; i++)
    {
        vec[RB].push_back(a[i]);
    }
    sort(vec[RB].begin(), vec[RB].end(), _cmp);
}
bool check(int l, int r, int v, int k)
{
    int LB = B[l];
    int RB = B[r];
    int cnt = 0;
    if(RB - LB <= 1)
    {
        for(int i = l; i <= r; i++)
        {
            if(a[i] + T[B[i]] < v)
            {
                cnt++;
            }
        }
        return cnt < k;
    }
    for(int i = LB + 1; i < RB; i++)
    {
        if(*(vec[i].end() - 1) < v - T[i])
        {
            cnt += (vec[i].end() - vec[i].begin());
            continue;
        }
        if(*vec[i].begin() > v - T[i])
        {
            continue;
        }
        cnt += (lower_bound(vec[i].begin(), vec[i].end(), v - T[i]) - vec[i].begin());
    }
    for(int i = l; i <= R[LB]; i++)
    {
        if(a[i] + T[B[i]] < v)
        {
            cnt++;
        }
    }
    for(int i = L[RB]; i <= r; i++)
    {
        if(a[i] + T[B[i]] < v)
        {
            cnt++;
        }
    }
    //printf("%d: %d\n", v, cnt);
    return cnt < k;
}
int query(int l, int r, int k)
{
    if(k < 1 || k > r - l + 1)
    {
        return -1;
    }
    int LB = B[l];
    int RB = B[r];
    int lp = INF;
    int rp = -INF;
    for(int i = LB; i <= RB; i++)
    {
        lp = min(lp, vec[i][0] - 2 + T[i]);
        rp = max(rp, vec[i][vec[i].size() - 1] + 2 + T[i]);
    }
    int ans = -INF;
    while(lp + 1 < rp)
    {
        int mid = 1ll * (1ll * lp + 1ll * rp) / 2;
        if(check(l, r, mid, k))
        {
            ans = mid;
            lp = mid;
        }
        else
        {
            rp = mid;
        }
    }
    return ans;
}
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d", &n, &m);
    blocksize = 120;
    int i;
    for(i = 1; i * blocksize < n; i++)
    {
        L[i] = R[i - 1] + 1;
        R[i] = i * blocksize;
    }
    L[i] = R[i - 1] + 1;
    R[i] = n;
    for(i = 1; i <= n; i++)
    {
        _a[i].v = a[i] = read();
        _a[i].i = i;
        B[i] = (i - 1) / blocksize + 1;
    }
    sort(_a + 1, _a + n + 1, cmp);
    for(i = 1; i <= n; i++)
    {
        vec[B[_a[i].i]].push_back(_a[i].v);
    }
    for(i = 1; i <= m; i++)
    {
        int opt = read(), l = read(), r = read(), k = read();
        if(opt == 1)
        {
            printf("%d\n", query(l, r, k));
        }
        else
        {
            add(l, r, k);
        }
    }
    return 0;
}
