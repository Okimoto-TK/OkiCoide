#include <cstdio>
#include <unordered_map>
#include <vector>
#include <algorithm>
int n;
long long m;
long long a[42];
long long cnt;
std::unordered_map<long long, int> map1;
std::unordered_map<long long, int> map2;
std::vector<std::pair<long long, int> > vec1;
std::vector<std::pair<long long, int> > vec2;
void Dfs1(int cur, long long sum)
{
    if(sum > m) return;
    if(cur == n / 2 + 1)
    {
        cnt++;
        map1[sum]++;
        return;
    }
    Dfs1(cur + 1, sum + a[cur]);
    Dfs1(cur + 1, sum);
}
void Dfs2(int cur, long long sum)
{
    if(sum > m) return;
    if(cur == n / 2)
    {
        map2[sum]++;
        return;
    }
    Dfs2(cur - 1, sum + a[cur]);
    Dfs2(cur - 1, sum);
}
bool cmp(std::pair<long long, int> a, std::pair<long long, int> b)
{
    return a.first > b.first;
}
bool _cmp(std::pair<long long, int> a, std::pair<long long, int> b)
{
    return a.first < b.first;
}
int main()
{
    scanf("%d%lld", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    Dfs1(1, 0);
    Dfs2(n, 0);
    for(auto x : map1)
    {
        vec1.push_back(x);
    }
    for(auto x : map2)
    {
        vec2.push_back(x);
    }
    std::sort(vec1.begin(), vec1.end(), cmp);
    std::sort(vec2.begin(), vec2.end(), _cmp);
    int ptr = 0;
    int len = vec1.size();
    int _len = vec2.size();
    long long ans = 0;
    for(int _ptr = 0; _ptr != _len; _ptr++)
    {
        while(ptr != len && vec1[ptr].first + vec2[_ptr].first > m) cnt -= vec1[ptr++].second;
        if(ptr == len) break;
        ans += vec2[_ptr].second * cnt;
    }
    printf("%lld", ans);
    return 0;
}
