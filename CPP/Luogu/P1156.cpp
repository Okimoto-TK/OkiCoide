#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int d, g;
struct Item
{
    int time;
    int pwr;
    int hgt;
} item[1007];
bool cmp(Item a, Item b)
{
    return a.time < b.time;
}
int f[1007][11037];
int main()
{
    scanf("%d %d", &d, &g);
    for(int i = 1; i <= g; i++)
    {
        scanf("%d %d %d", &item[i].time, &item[i].pwr, &item[i].hgt);
    }
    sort(item + 1, item + 1 + g, cmp);
    memset(f, ~0x3f, sizeof(f));
    f[0][10] = 0;
    int last = 0;
    for(int i = 1; i <= g; i++)
    {
        for(int j = item[i].time - last; j - item[i].time + last <= 10000; j++)
        {
            f[i][j - item[i].time + last + item[i].pwr] = std::max(f[i][j - item[i].time + last + item[i].pwr], f[i - 1][j]);
            f[i][j - item[i].time + last] = std::max(f[i][j - item[i].time + last], f[i - 1][j] + item[i].hgt);
        }
        last = item[i].time;
    }
    int ans = 10;
    for(int i = 1; i <= g; i++)
    {
        for(int j = 0; j <= 10000; j++)
        {
            if(f[i][j] >= d)
            {
                printf("%d", item[i].time);
                return 0;
            }
            if(f[i][j] >= 0)
            {
                ans = max(ans, item[i].time + j);
            }
        }
    }
    printf("%d", ans);
    return 0;
}
