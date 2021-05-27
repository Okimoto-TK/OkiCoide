#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <map>
using namespace std;
int n, m, p, s;
int a[40007];
int _a[40007];
int b[207][207][2];
int tmp[40007];
int L[207];
int R[207];
int pos[40007];
map <int, int> to;
map <int, int> bk;
vector <int> vec[40007];
int query(int l, int r)
{
    int p = pos[l];
    int q = pos[r];
    if(p == q)
    {
        int mx = 0;
        int ans = 0;
        for(int i = l; i <= r; i++)
        {
            int t = (upper_bound(vec[a[i]].begin(), vec[a[i]].end(), r) - lower_bound(vec[a[i]].begin(), vec[a[i]].end(), l));
            if(t > mx || (t == mx && a[i] < ans))
            {
                ans = a[i];
                mx = t;
            }
        }
        return ans;
    }
    int ans = b[p + 1][q - 1][0];
    int mx = b[p + 1][q - 1][1];
    for(int i = l; i <= R[p]; i++)
    {
        int t = (upper_bound(vec[a[i]].begin(), vec[a[i]].end(), r) - lower_bound(vec[a[i]].begin(), vec[a[i]].end(), l));
        if(t > mx || (t == mx && a[i] < ans))
        {
            ans = a[i];
            mx = t;
        }
    }
    for(int i = L[q]; i <= r; i++)
    {
        int t = (upper_bound(vec[a[i]].begin(), vec[a[i]].end(), r) - lower_bound(vec[a[i]].begin(), vec[a[i]].end(), l));
        if(t > mx || (t == mx && a[i] < ans))
        {
            ans = a[i];
            mx = t;
        }
    }
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        _a[i] = a[i];
    }
    sort(_a + 1, _a + 1 + n);
    for(int i = 1; i <= n; i++)
    {
        int v = _a[i];
        if(to[v] == 0)
        {
            to[v] = ++p;
            bk[p] = v;
        }
    }
    for(int i = 1; i <= n; i++)
    {
        a[i] = to[a[i]];
        vec[a[i]].push_back(i);
    }
    for(int i = 1; i <= p; i++)
    {
        vec[p].push_back(n + 1);
    }
    s = sqrt(n);
    for(int i = 1; i <= s; i++)
    {
        L[i] = (i - 1) * s + 1;
        R[i] = i * s;
        for(int j = L[i]; j <= R[i]; j++)
        {
            pos[j] = i;
        }
    }
    while(R[s] < n)
    {
        s++;
        L[s] = R[s - 1] + 1;
        R[s] = n;
        for(int j = L[s]; j <= R[s]; j++)
        {
            pos[j] = s;
        }
    }
    for(int i = 1; i <= s; i++)
    {
        int mx = 0;
        memset(tmp, 0, sizeof(tmp));
        for(int j = i; j <= s; j++)
        {
            for(int k = L[j]; k <= R[j]; k++)
            {
                tmp[a[k]]++;
                if(tmp[a[k]] > tmp[mx] || (tmp[a[k]] == tmp[mx] && a[k] < mx))
                {
                    mx = a[k];
                }
            }
            b[i][j][0] = mx;
            b[i][j][1] = tmp[mx];
        }
    }
    int x = 0;
    for(int i = 1; i <= m; i++)
    {
        int l0, r0;
        scanf("%d%d", &l0, &r0);
        int l = ((l0 + x - 1) % n) + 1;
        int r = ((r0 + x - 1) % n) + 1;
        if(l > r)
        {
            int t = l;
            l = r;
            r = t;
        }
        x = bk[query(l, r)];
        printf("%d\n", x);
    }
    return 0;
}
