#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
string s[100007];
int sp;
string t[100007];
char buf[1000007];
int tp;
int cnt;
int tme;
int getMin(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
    //freopen("in.in", "r", stdin);
    gets(buf);
    if(buf[strlen(buf) - 1] == '\r')
    {
        buf[strlen(buf) - 1] = '\0';
    }
    while(strcmp(buf, "EOF") != 0)
    {
        s[sp] = buf;
        sp ++;
        gets(buf);
        if(buf[strlen(buf) - 1] == '\r')
        {
            buf[strlen(buf) - 1] = '\0';
        }
    }
    gets(buf);
    if(buf[strlen(buf) - 1] == '\r')
    {
        buf[strlen(buf) - 1] = '\0';
    }
    while(strcmp(buf, "EOF") != 0)
    {
        t[tp ++] = buf;
        gets(buf);
        if(buf[strlen(buf) - 1] == '\r')
        {
            buf[strlen(buf) - 1] = '\0';
        }
    }
    scanf("%d", &tme);
    for(int i = 0; i < getMin(sp, tp); i ++)
    {
        int p = 0;
        for(int j = 0; j < s[i].size(); j ++, p ++)
        {
            if(j != 0 && s[i][j] == '<')
            {
                s[i].erase(j - 1, 2);
                j -= 2;
            }
            else if(s[i][j] == '<')
            {
                s[i].erase(s[i].begin());
                j -= 1;
            }
        }
        for(int j = 0; j < t[i].size(); j ++)
        {
            if(j != 0 && t[i][j] == '<')
            {
                t[i].erase(j - 1, 2);
                j -= 2;
            }
            else if(t[i][j] == '<')
            {
                t[i].erase(t[i].begin());
                j -= 1;
            }
        }
        for(int j = 0; j < getMin(t[i].size(), s[i].size()); j ++)
        {
            if(t[i][j] == s[i][j])
            {
                cnt ++;
            }
        }
    }
    printf("%d", (int)round(double(cnt) * 60.0 / double(tme)));
    return 0;
}
