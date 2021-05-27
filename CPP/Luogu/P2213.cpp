#include <cstdio>
#include <algorithm>
#define N 407
int n, k;
int a[N][N];
int _sum[N][N];
int sum_[N][N];
int max;
int get_Sum(int len, int end, int layer) { return _sum[layer][end] - _sum[layer][end - len < 0 ? 0 : end - len]; }
int getSum_(int len, int begin, int layer) { return sum_[layer][begin] - sum_[layer][begin + len > n + 1 ? n + 1 : begin + len]; }
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
            _sum[i][j] = _sum[i][j - 1] + a[i][j];
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = n; j >= 1; j--) sum_[i][j] = sum_[i][j + 1] + a[i][j];
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            int tmp = 0;
            for(int x = std::max(1, j - k); x <= std::min(n, j + k); x++)
            {
                tmp += a[i][x];
            }
            for(int l = i - 1, c = 1; c <= k && l >= 1; c++, l--)
            {
                tmp += a[l][j];
                tmp += get_Sum(k - c, j - 1, l);
                tmp += getSum_(k - c, j + 1, l);
            }
            for(int l = i + 1, c = 1; c <= k && l <= n; c++, l++)
            {
                tmp += a[l][j];
                tmp += get_Sum(k - c, j - 1, l);
                tmp += getSum_(k - c, j + 1, l);
            }
            max = std::max(max, tmp);
        }
    }
    printf("%d", max);
    return 0;
}
