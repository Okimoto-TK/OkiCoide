#include <stdio.h>
using namespace std;
int n, m;
bool mp[101][101];
int ans;
void dfs(int h, int v){
    if(!mp[h][v])
        return;
    mp[h][v] = false;
    if(h != 0 && v != 0)
        dfs(h - 1, v - 1);
    if(h != 0)
        dfs(h - 1, v);
    if(v != 0)
        dfs(h, v - 1);
    if(h + 1 != n && v + 1 != m)
        dfs(h + 1, v + 1);
    if(h + 1 != n)
        dfs(h + 1, v);
    if(v + 1 != m)
        dfs(h, v + 1);
    if(h + 1 != n && v - 1 != m)
        dfs(h + 1, v - 1);
    if(h - 1 != n && v + 1 != m)
        dfs(h - 1, v + 1);
}
int main(int argc, char const *argv[])
{
    freopen("tab.txt", "r", stdin);
    scanf("%d %d", &n, &m);
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            char c;
            scanf("%c", &c);
            if(c != '.' && c != 'W')
                scanf("%c", &c);
            if(c != '.' && c != 'W')
                scanf("%c", &c);
            if(c == '.')
                mp[i][j] = false;
            else
                mp[i][j] = true;
        }
    }
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            if(mp[i][j]){
                ans ++;
                dfs(i, j);
            }
    printf("%d", ans);
    return 0;
}