#include <cstdio>
#include <cmath>
#define N1 500005
#define N2 205
#define M 1005
int r, c, m, pool;
int p1[N1];
struct Node
{
    int lch;
    int rch;
    int cnt;
} t1[12000000];
int rt1[N1];
int build1(int l, int r)
{
    int k = ++pool;
    if(l == r) return k;
    int mid = (l + r) >> 1;
    t1[k].lch = build1(l, mid);
    t1[k].rch = build1(mid + 1, r);
    return k;
}
int insert1(int _k, int l, int r, int x)
{
    int k = ++pool;
    if(l == r)
    {
        t1[k].cnt = t1[_k].cnt + 1;
        return k;
    }
    int mid = (l + r) >> 1;
    t1[k].lch = t1[_k].lch;
    t1[k].rch = t1[_k].rch;
    if(x <= mid) t1[k].lch = insert1(t1[k].lch, l, mid, x);
    else t1[k].rch = insert1(t1[k].rch, mid + 1, r, x);
    t1[k].cnt = t1[t1[k].lch].cnt + t1[t1[k].rch].cnt;
    return k;
}
int query(int k1, int k2, int l, int r, int x)
{
    if(l == r) return t1[k2].cnt - t1[k1].cnt;
    int mid = (l + r) >> 1;
    if(x <= mid) return query(t1[k1].lch, t1[k2].lch, l, mid, x);
    else return query(t1[k1].rch, t1[k2].rch, mid + 1, r, x);
}
void solve1()
{
    rt1[0] = build1(1, M);
    for(int i = 1; i <= c; i++)
    {
        scanf("%d", &p1[i]);
        rt1[i] = insert1(rt1[i - 1], 1, M, p1[i]);
    }
    for(int i = 1; i <= m; i++)
    {
        int x1, y1, x2, y2, h;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
        int ans = 0;
        int sum = 0;
        int ptr = 1000;
        while(sum < h && ptr >= 1)
        {
            int cnt = query(rt1[y1 - 1], rt1[y2], 1, M, ptr);
            if(cnt * ptr + sum > h)
            {
                int tmp = ceil(double(h - sum) / double(ptr));
                ans += tmp;
                sum += tmp * ptr;
            }
            else
            {
                sum += cnt * ptr;
                ans += cnt;
            }
            ptr--;
        }
        if(sum < h) printf("Poor QLW\n");
        else printf("%d\n", ans);
    }
}
int p2[N2][N2];
int buk[N2][N2][1005];
int sum[N2][N2][1005];
bool check(int x1, int y1, int x2, int y2, int h, int x)
{
    return sum[x2][y2][x] - sum[x2][y1 - 1][x] - sum[x1 - 1][y2][x] + sum[x1 - 1][y1 - 1][x] >= h;
}
void solve2()
{
    for(int i = 1; i <= r; i++)
    {
        for(int j = 1; j <= c; j++)
        {
            scanf("%d", &p2[i][j]);
            for(int k = 0; k <= 1000; k++)
            {
                buk[i][j][k] = buk[i][j - 1][k] + buk[i - 1][j][k] - buk[i - 1][j - 1][k];
                sum[i][j][k] = sum[i][j - 1][k] + sum[i - 1][j][k] - sum[i - 1][j - 1][k];
                if(p2[i][j] >= k)
                {
                    buk[i][j][k] += 1;
                    sum[i][j][k] += p2[i][j];
                }
            }
        }
    }
    for(int i = 1; i <= m; i++)
    {
        int x1, y1, x2, y2, h;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
        int l = 0;
        int ans = -1;
        int r = 1001;
        while(l + 1 < r)
        {
            int mid = (l + r) >> 1;
            if(check(x1, y1, x2, y2, h, mid))
            {
                ans = l = mid;
            }
            else
            {
                r = mid;
            }
        }
        if(ans == -1) printf("Poor QLW\n");
        else
        {
            int tmp = sum[x2][y2][ans] - sum[x2][y1 - 1][ans] - sum[x1 - 1][y2][ans] + sum[x1 - 1][y1 - 1][ans];
            int out = buk[x2][y2][ans] - buk[x2][y1 - 1][ans] - buk[x1 - 1][y2][ans] + buk[x1 - 1][y1 - 1][ans];
            out -= (tmp - h) / ans;
            printf("%d\n", out);
        }
    }
}
int main()
{
    //freopen("in.in", "r", stdin);
    scanf("%d%d%d", &r, &c, &m);
    if(r == 1) solve1();
    else solve2();
    return 0;
}
