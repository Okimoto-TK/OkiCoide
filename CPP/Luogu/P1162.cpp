#include <stdio.h>
using namespace std;
int n;
int mp[32][32];
void dfs(int h, int v){
    if(mp[h][v] == 0)
        return;
    if(mp[h][v] == 1)
        return;
    mp[h][v] = 0;
    if(h - 1 >= 0)
        dfs(h - 1, v);
    if(h + 1 <= n + 1)
        dfs(h + 1, v);
    if(v - 1 >= 0)
        dfs(h, v - 1);
    if(v + 1 <= n + 1)
        dfs(h, v + 1);
}
int main(int argc, char const *argv[])
{
    scanf("%d", &n);
    for(int i = 0; i <= n + 1; i ++)
        for(int j = 0; j <= n + 1; j ++)
            mp[i][j] = 2;
    for(int i = 1; i <= n; i ++)
        for(int j = 1; j <= n; j ++){
            int t;
            scanf("%d", &t);
            mp[i][j] = t == 0 ? 2 : 1;
        }
    dfs(0, 0);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++)
            printf("%d ", mp[i][j]);
        printf("\n");
    }
    return 0;
}