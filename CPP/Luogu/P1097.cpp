#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pp;
map <int, int> m;
bool cmp(pp a, pp b){
    return a.first < b.first;
}
int n;
int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i ++){
        int x;
        scanf("%d", &x);
        m[x] += 1;
    }
    vector <pp> v(m.begin(), m.end());
    sort(v.begin(), v.end(), cmp);
    for(auto i : v){
        printf("%d %d\n", i.first, i.second);
    }
    return 0;
}