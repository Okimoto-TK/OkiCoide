#include <stdio.h>
#include <queue>
#define N 100007
using namespace std;
int n, k;
long long a[N];
long long V[N];
int L[N];
int R[N];
long long ans;
struct cmp1{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b){
            return a.first > b.first;
    }
};
priority_queue<pair<long long, int>, vector<pair<long long, int> >, cmp1> heap;
bool vis[5 * N];
int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    for(int i = 1; i < n; i++)
    {
        V[i] = a[i + 1] - a[i];
        L[i] = i - 1;
        R[i] = i + 1;
        heap.push(pair<long long, int>(V[i], i));
    }
    V[0] = V[n] = 1e9 + 7;
    for(int i = 1; i <= k; i++)
    {
        while(!heap.empty() && vis[heap.top().second])
        {
            heap.pop();
        }
        long long vl = heap.top().first;
        int id = heap.top().second;
        ans += vl;
        heap.pop();
        V[id] = vl = V[L[id]] + V[R[id]] - vl;
        vis[L[id]] = vis[R[id]] = true;
        L[id] = L[L[id]];
        R[id] = R[R[id]];
        L[R[id]] = id;
        R[L[id]] = id;
        heap.push(pair<long long, int>(vl, id));
    }
    // Windows: printf("%I64d", ans);
    printf("%lld\n", ans);
    return 0;
}
