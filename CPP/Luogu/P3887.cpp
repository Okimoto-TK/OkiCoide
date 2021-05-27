#include <cstdio>
#include <queue>
int k, d, m, f, q;
std::priority_queue<int, std::vector<int>, std::less<int> > h[4];
int main()
{
    scanf("%d%d%d%d", &k, &d, &m, &f);
    for(int i = 1; i <= k; i++)
    {
        int x;
        scanf("%d", &x);
        h[0].push(x);
    }
    for(int i = 1; i <= d; i++)
    {
        int x;
        scanf("%d", &x);
        h[1].push(x);
    }
    for(int i = 1; i <= m; i++)
    {
        int x;
        scanf("%d", &x);
        h[2].push(x);
    }
    for(int i = 1; i <= f; i++)
    {
        int x;
        scanf("%d", &x);
        h[3].push(x);
    }
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
        int a, b, c;
        double sum = h[0].top();
        h[0].pop();
        scanf("%d%d%d", &a, &b, &c);
        for(int j = 1; j <= a; j++)
        {
            sum += h[1].top();
            h[1].pop();
        }
        for(int j = 1; j <= b; j++)
        {
            sum += h[2].top();
            h[2].pop();
        }
        for(int j = 1; j <= c; j++)
        {
            sum += h[3].top();
            h[3].pop();
        }
        printf("%.2lf\n", sum / (a + b + c + 1));
    }
    return 0;
}
