#include <stdio.h>
#include <map>
#include <vector>
using namespace std;
int m, n, cnt;
int f[1007][1007];
vector <int> w[1007];
vector <int> p[1007];
map <int, int> mp;
int getMax(int a, int b){ return a > b ? a : b; }
int main()
{
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= n; ++i)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        mp[c] = mp[c] == 0 ? ++cnt : mp[c];
        int _c = mp[c];
        w[_c].push_back(a);
        p[_c].push_back(b);
    }
    for(int i = 1; i <= cnt; ++i)
    {
        for(int v = 1; v <= m; ++v)
        {
            f[i][v] = f[i - 1][v];
            for(int j = 0; j < w[i].size(); ++j)
            {
                if(v - w[i][j] >= 0)
                {
                    f[i][v] = getMax(f[i][v], f[i - 1][v - w[i][j]] + p[i][j]);
                }
            }
        }
    }
    printf("%d", f[cnt][m]);
    return 0;
}
