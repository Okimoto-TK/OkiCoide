#include <cstdio>
#include <cstring>
#include <vector>
int n, di, dj;
bool vis[64];
std::vector<int> base[7];
int h() {
    bool _vis[64];
    memcpy(_vis, vis, sizeof(_vis));
    int cnt = 0;
    for(int l = 1; l <= n; l++) {
        for(int i = 1; i + l - 1 <= n; i++) {
            for(int j = 1; j + l - 1 <= n; j++) {
                int d = (i - 1) * di + (j - 1) * dj;
                bool count = true;
                for(auto x : base[l]) {
                    if(_vis[x + d]) {
                        count = false;
                        break;
                    }
                }
                if(count) {
                    cnt++;
                    for(auto x : base[l]) {
                        _vis[x + d] = true;
                    }
                }
            }
        }
    }
    return cnt;
}
bool Dfs(int limit, int x) {
    if(x + h() > limit) return false;
    for(int l = 1; l <= n; l++) {
        for(int i = 1; i + l - 1 <= n; i++) {
            for(int j = 1; j + l - 1 <= n; j++) {
                int d = (i - 1) * di + (j - 1) * dj;
                bool count = true;
                for(auto y : base[l]) {
                    if(vis[y + d]) {
                        count = false;
                        break;
                    }
                }
                if(!count) continue;
                for(auto y : base[l])
                {
                    vis[y + d] = true;
                    if(Dfs(limit, x + 1)) {
                        return true;
                    }
                    vis[y + d] = false;
                }
                return false;
            }
        }
    }
    return true;
}
int main() {
    int t;
    for(scanf("%d", &t); t != 0; t--) {
        memset(vis, 0, sizeof(vis));
        scanf("%d", &n);
        di = 1;
        dj = 2 * n + 1;
        for(int i = 1; i <= n; i++)
        {
            base[i].clear();
            for(int j = 1; j <= i; j++) {
                base[i].push_back(j + i * dj);
                base[i].push_back(j);
                base[i].push_back(n + 1 + (j - 1) * dj);
                base[i].push_back(n + 1 + i + (j - 1) * dj);
            }
        }
        int k;
        scanf("%d", &k);
        for(int i = 1; i <= k; i++) {
            int a;
            scanf("%d", &a);
            vis[a] = true;
        }
        int limit = h();
        while(!Dfs(limit, 0)) {
            limit++;
        }
        printf("%d\n", limit);
    }
    return 0;
}
