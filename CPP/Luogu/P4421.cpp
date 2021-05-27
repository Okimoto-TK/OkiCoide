#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
int n;
char buf[200007][11];
int ans;
unsigned long long h[200007][12];
map<unsigned long long, int> mp;
map<unsigned long long, int> bl;
int main()
{
    mp.clear();
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%s", buf[i]);
        int l = strlen(buf[i]);
        bl.clear();
        for(int j = 0; j < l; j++)
        {
            for(int k = j; k < l; k++)
            {
                unsigned long long hsh = 0;
                for(int p = j; p <= k; p++)
                {
                    (hsh *= 1331) += buf[i][p];
                }
                if(bl[hsh] == 1)
                {
                    continue;
                }
                mp[hsh]++;
                bl[hsh] = 1;
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        unsigned long long hsh = 0;
        int len = strlen(buf[i]);
        for(int p = 0; p < len; p++)
        {
            (hsh *= 1331) += buf[i][p];
        }
        ans += mp[hsh] - 1;
    }
    printf("%d", ans);
    return 0;
}
