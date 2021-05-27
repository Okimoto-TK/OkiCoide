#include <stdio.h>
#include <string>
#include <map>
using namespace std;
int p;
map<string, int> getIdx;
map<int, string> getNme;
char buf[10];
char tmp[10];
int set[50007];
void init()
{
    for(int i = 1; i <= 50006; i++)
    {
        set[i] = i;
    }
}
int find(int x)
{
    if(set[x] == x)
    {
        return x;
    }
    set[x] = find(set[x]);
    return set[x];
}
int main()
{
    init();
    for(scanf("%s", buf); buf[0] != '$';)
    {
        string str1 = buf;
        if(str1[0] == '#')
        {
            string name1 = str1.substr(1, str1.size() - 1);
            scanf("%s", buf);
            while(buf[0] == '+')
            {
                string str2 = buf;
                string name2 = str2.substr(1, str2.size() - 1);
                if(getIdx[name1] == 0)
                {
                    getIdx[name1] = ++p;
                    getNme[p] = name1;
                }
                if(getIdx[name2] == 0)
                {
                    getIdx[name2] = ++p;
                    getNme[p] = name2;
                }
                int a = getIdx[name1];
                int b = getIdx[name2];
                if(find(a) != find(b))
                {
                    set[find(b)] = find(a);
                }
                scanf("%s", buf);
            }
        }
        else if(buf[0] == '?')
        {
            string name = str1.substr(1, str1.size() - 1);
            printf("%s ", name.c_str());
            printf("%s\n", getNme[find(getIdx[name])].c_str());
            scanf("%s", buf);
        }
    }
    return 0;
}
