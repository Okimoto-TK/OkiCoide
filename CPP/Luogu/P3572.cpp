#include <stdio.h>
#include <deque>
using namespace std;
deque <int> d;
int a[1000007];
int f[1000007];
int n;
int q;
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
	scanf("%d", &q);
	for(int i = 0; i < q; i ++){
		int k;
		scanf("%d", &k);
		f[0] = 0;
		d.push_back(0);
		for(int j = 1; j < n; j ++){
			if(d.front() < j - k)
				d.pop_front();
			f[j] = f[d.front()] + (a[d.front()] <= a[j] ? 1 : 0);
			while(!d.empty() && (f[j] < f[d.back()] || (f[j] == f[d.back()] && a[j] >= a[d.back()])))
				d.pop_back();
			d.push_back(j);
		}
		d.clear();
		printf("%d\n", f[n - 1]);
	}
	return 0;
}