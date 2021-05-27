#include <stdio.h>
#include <map>
#include <queue>
using namespace std;
const int k = 13313;
int n;
int a[200007];
unsigned long long h[200007];
unsigned long long h1[200007];
unsigned long long p[200007];
map<unsigned long long, bool> b;
queue<int> ans;
int _max;
int main()
{
    scanf("%d", &n);
    p[0] = 1;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        p[i] = p[i - 1] * k;
        h[i] = h[i - 1] * k + a[i];
    }
    for(int i = n; i >= 1; i--)
    {
        h1[i] = h1[i + 1] * k + a[i];
    }
    for(int i = 1; i <= n; i++)
    {
        b.clear();
        int c = 0;
        for(int j = 1; j * i <= n; j++)
        {
            unsigned long long hsh = h[i * j] - h[i * (j - 1)] * p[i];
            unsigned long long hsh1 = h1[i * (j - 1) + 1] - h1[i * j + 1] * p[i];
            if(!b[hsh] && !b[hsh1])
            {
                b[hsh] = true;
                b[hsh1] = true;
                c++;
            }
        }
        if(c > _max)
        {
            _max = c;
            while(!ans.empty())
            {
                ans.pop();
            }
            ans.push(i);
        }
        else if(c == _max)
        {
            ans.push(i);
        }
    }
    printf("%d %d\n", _max, (int)ans.size());
    while(!ans.empty())
    {
        printf("%d ", ans.front());
        ans.pop();
    }
}
