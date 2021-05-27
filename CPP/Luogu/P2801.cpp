#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define N 2000007
#define SQR 2007
int n, q, blocksize;
int L[SQR];
int R[SQR];
int B[N];
int H[N];
int T[SQR];
std::vector<int> V[SQR];
void update(int x)
{
    V[x].clear();
    for(int i = L[x]; i <= R[x]; i++)
    {
        V[x].push_back(H[i]);
    }
    std::sort(V[x].begin(), V[x].end());
}
void change(int l, int r, int v)
{
    int LB = B[l];
    int RB = B[r];
    for(int i = LB + 1; i < RB; i++) T[i] += v;
    for(int i = l; i <= r; i++) H[i] += v;
    update(LB);
    update(RB);
}
int query(int l, int r, int c)
{
    int LB = B[l];
    int RB = B[r];
    int res = 0;
    for(int i = LB + 1; i < RB; i++) res += V[i].end() - std::lower_bound(V[i].begin(), V[i].end(), c - T[i]);
    for(int i = l; i <= R[LB]; i++)
    {
        if(H[i] + T[LB] >= c) res++;
    }
    for(int i = L[RB]; i <= r; i++)
    {
        if(H[i] + T[RB] >= c) res++;
    }
    return res;
}
int main()
{
    scanf("%d%d", &n, &q);
    blocksize = sqrt(n) / 2;
    int i;
    for(i = 1; i * blocksize < n; i++)
    {
        L[i] = R[i - 1] + 1;
        R[i] = i * blocksize;
    }
    L[i] = R[i - 1] + 1;
    R[i] = n;
    for(int j = 1; j <= n; j++)
    {
        B[j] = (j - 1) / blocksize + 1;
        scanf("%d", &H[j]);
    }
    for(int j = 1; j <= i; j++) update(j);
    for(i = 1; i <= q; i++)
    {
        char opt[2];
        int l, r;
        scanf("%s%d%d", opt, &l, &r);
        if(opt[0] == 'M')
        {
            int w;
            scanf("%d", &w);
            change(l, r, w);
        }
        else
        {
            int c;
            scanf("%d", &c);
            printf("%d\n", query(l, r, c));
        }
    }
    return 0;
}
