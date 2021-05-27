#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
int n[5];
int s[207];
bool f[207][207][5];
char buf[207];
vector <pair<int, int> > v[5];
int getInt(char x)
{
    if(x == 'W')
    {
        return 1;
    }
    else if(x == 'I')
    {
        return 2;
    }
    else if(x == 'N')
    {
        return 3;
    }
    else
    {
        return 4;
    }
}
int main()
{
    scanf("%d%d%d%d", &n[1], &n[2], &n[3], &n[4]);
    for(int j = 1; j <= 4; j++)
    {
        for(int i = 1; i <= n[j]; i++)
        {
            char a[3];
            scanf("%s", a);
            v[j].push_back(make_pair(getInt(a[0]), getInt(a[1])));
        }
    }
    scanf("%s", buf);
    int len = strlen(buf);
    for(int i = 0; i < len; i++)
    {
        s[i + 1] = getInt(buf[i]);
    }
    for(int i = 1; i <= len; i++)
    {
        f[i][i][s[i]] = true;
    }
    for(int k = 2; k <= len; k++)
    {
        for(int i = 1; i + k - 1 <= len; i++)
        {
            int j = i + k - 1;
            for(int l = 1; l <= 4; l++)
            {
                int _len = v[l].size();
                for(int rec = 0; rec < _len; rec++)
                {
                    int fst = v[l][rec].first;
                    int scd = v[l][rec].second;
                    for(int mid = i; mid < j; mid++)
                    {
                        f[i][j][l] |= f[i][mid][fst] & f[mid + 1][j][scd];
                    }
                }
            }
        }
    }
    bool wrong = true;
    if(f[1][len][1])
    {
        wrong = false;
        printf("W");
    }
    if(f[1][len][2])
    {
        wrong = false;
        printf("I");
    }
    if(f[1][len][3])
    {
        wrong = false;
        printf("N");
    }
    if(f[1][len][4])
    {
        wrong = false;
        printf("G");
    }
    if(wrong)
    {
        printf("The name is wrong!");
    }
    return 0;
}
