#include <stdio.h>
#include <string>
using namespace std;
int cun[21][21];
int len[21];
string str[21];
int used[21];
int n;
char c;
int count(int x, int y){
    int minLn = str[x].size() < str[y].size() ? str[x].size() : str[y].size();
    for(int i = 1; i <= minLn; i ++){
        for(int j = 0; j < i; j ++){
            if(str[y][j] != str[x][str[x].size() - i + j]){
                goto next;
            }
        }
        return i;
        next:
            continue;
    }
    return 0;
}
int dfs(int sum, int lst){
    int rtn = sum;
    for(int i = 0; i < n; i ++){
        if(cun[lst][i] == 0)
            continue;
        if(used[i] >= 2)
            continue;
        if(cun[lst][i] == len[lst] || cun[lst][i] == len[i])
            continue;
        used[i] ++;
        int rst = dfs(sum + len[i] - cun[lst][i], i);
        used[i] --;
        if(rst > rtn)
            rtn = rst;
    }
    return rtn;
}
int main(){
    scanf("%d\n", &n);
    for(int i = 0; i < n; i ++){
        char temp[64];
        scanf("%s\n", temp);
        str[i] = temp;
        len[i] = str[i].size();
    }
    scanf("%c", &c);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < n; j ++)
            cun[i][j] = count(i, j);
    int ans = 0;
    for(int i = 0; i < n; i ++){
        if(str[i][0] == c){
            used[i] ++;
            int rst = dfs(len[i], i);
            used[i] --;
            if(rst > ans)
                ans = rst;
        }
    }
    printf("%d", ans);
    return 0;
}