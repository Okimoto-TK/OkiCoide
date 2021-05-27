#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> fac[1000007];
char buf[1000007];
unsigned long long power[1000007];
unsigned long long h[1000007];
const int b = 107;
inline bool cmp(int a, int b)
{
    return a < b;
}
int main()
{
    power[0] = 1;
    for(int i = 1; i <= 1000000; i++)
    {
        power[i] = b * power[i - 1];
    }
    for(int i = 1; i <= 1000000; i++)
    {
        int j = 1000000 / i;
        for(int k = 1; k <= j; k++)
        {
            fac[i * k].push_back(i);
        }
    }
    scanf("%s", buf);
    while(buf[0] != '.')
    {
        int len = strlen(buf);
        sort(fac[len].begin(), fac[len].end(), cmp);
        h[0] = 0;
        for(int i = 0; i < len; i++)
        {
            h[i + 1] = h[i] * b + buf[i] - 'a';
        }
        int size = fac[len].size();
        for(int i = 0; i < size; i++)
        {
            int l = fac[len][i];
            unsigned long long spl = h[l];
            bool scs = true;
            for(int j = 1; j * l <= len; j++)
            {
                if(h[j * l] - h[(j - 1) * l] != spl * power[(j - 1) * l])
                {
                    scs = false;
                    break;
                }
            }
            if(scs)
            {
                printf("%d\n", len / l);
                break;
            }
        }
        scanf("%s", buf);
    }
    return 0;
}
