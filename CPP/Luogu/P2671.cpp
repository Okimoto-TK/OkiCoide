#pragma GCC optimize(2)
#include <stdio.h>
#include <vector>
using namespace std;
struct bck
{
    int num;
    int clr;
}b[100010];
int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    vector <long long> v[m + 2];
    for(int i = 1; i <= n; i ++){
        scanf("%d", &b[i].num);
    }
    for(int i = 1; i <= n; i ++){
        scanf("%d", &b[i].clr);
        v[b[i].clr].push_back(i);
    }
    int ans = 0;
    for(int i = 1; i <= m; i ++){
        if(v[i].size() <= 1)
            continue;
        for(int j = 0; j < v[i].size() - 1; j ++){
            for(int k = j + 1; k < v[i].size(); k ++){
                if((v[i][k] - v[i][j]) % 2)
                    continue;
                ans = (ans + (v[i][j] + v[i][k]) * (b[v[i][j]].num + b[v[i][k]].num)) % 10007;
            }
        }
    }
    printf("%d", ans);
    return 0;
}