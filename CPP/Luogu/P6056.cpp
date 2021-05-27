#include <stdio.h>
#include <math.h>
using namespace std;
struct day
{
	long long s;
	long long i;
	long long r;
} d[128];
long long n;
double beta;
double gam;
int main(int argc, char const *argv[])
{
	d[0].r = 0;
	scanf("%lld %lld %lld", &d[0].s, &d[0].i, &n);
	scanf("%lf %lf", &beta, &gam);
	for(int i = 1; i <= n; i ++){
		long long trans = ceil(beta * d[i - 1].s * d[i - 1].i);
		int tmp = d[i - 1].s;
		d[i].s = d[i - 1].s - trans;
		if(d[i].s < 0){
			d[i].s = 0;
			d[i].i = d[i - 1].i + tmp;
		}
		else
			d[i].i = d[i - 1].i + trans;
		long long cures = ceil(gam * d[i - 1].i);
		d[i].i -= cures;
		d[i].r = d[i - 1].r + cures;
	}
	printf("%lld %lld %lld", d[n].s, d[n].i, d[n].r);
	return 0;
}