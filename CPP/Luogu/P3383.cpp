#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include <stdio.h>
#include <bitset>
#include <vector>
using namespace std;
bitset <100000010> p;
vector <int> pm;
vector <int> qs;
int n, q;
int main(int argc, char const *argv[])
{
	scanf("%d %d", &n, &q);
	int mx = 0;
	for(int i = 0; i < q; i ++){
		int t;
		scanf("%d", &t);
		mx = mx > t ? mx : t;
		qs.push_back(t);
	}
	for(int i = 2; i <= n; i ++){
		if(i % 2 == 0 && i != 2)
			continue;
		if(!p[i])
			pm.push_back(i);
		for(int j = 0; j < pm.size() && i * pm[j] <= n; j ++){
			p[i * pm[j]] = true;
		}
		if(pm.size() >= mx)
			break;
	}
	for(int i = 0; i < qs.size(); i ++)
		printf("%d\n", pm[qs[i] - 1]);
	return 0;
}