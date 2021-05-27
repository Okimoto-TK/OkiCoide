#include <stdio.h>
#include <string>
#include <queue>
using namespace std;
const string S = "sos";
queue <string> q;
int m;
int n;
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        int cnt = 0;
        char tmp[256];
        scanf("%s", tmp);
        string name = tmp;
        scanf("%s", tmp);
        string str = tmp;
        for(int j = 0; j + 2 < str.size(); j++)
        {
            bool is = true;
            for(int k = 0; k < 3; k++){ if(str[j + k] != S[k]){ is = false; }}
            cnt += is ? 1 : 0;
        }
        if(cnt == m)
        {
            q.push(name);
        }
        else if(cnt > m)
        {
            while(!q.empty()){ q.pop(); }
            q.push(name);
            m = cnt;
        }
    }
    while(!q.empty())
    {
        printf("%s ", q.front().c_str());
        q.pop();
    }
    printf("\n%d", m);
    return 0;
}
