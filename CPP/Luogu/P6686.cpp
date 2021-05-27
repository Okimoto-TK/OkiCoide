#include <stdio.h>
#pragma GCC optimize(2)
using namespace std;
int n;
int max;
int buck[200001];
inline int read(){  
   	int s=0,w=1;  
   	char ch=getchar();  
   	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}  
   	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();  
   	return s*w;  
} 
inline long long c2(long long m){
	return m * (m - 1) / 2;
}
inline long long c3(long long m){
    return m * (m - 1) * (m - 2) / 3 / 2;
}
int main(int argc, char const *argv[])
{
	n = read();
	for(int i = 0; i < n; i ++){
		int tmp;
		tmp = read();
		if(tmp > max)
			max = tmp;
		buck[tmp] ++;
	}
	long long ans = 0;
	for(int i = 1; i <= max; i ++){
		int tmp = 0;
		if(buck[i] <= 1)
			continue;
		for(int j = 1; j <= max; j ++){
			if(i == j)
				continue;
			if(buck[j] == 0)
				continue;
			if(i < j){
				if(2 * i > j)
					tmp += buck[j];
			}
			else
				tmp += buck[j];
		}
		ans += tmp * c2(buck[i]);
		ans %= 998244353;
	}
	for(int i = 1; i <= max; i ++){
		if(buck[i] < 3)
			continue;
		ans += c3(buck[i]) % 998244353;
		ans %= 998244353;
	}
	printf("%lld", ans);
	return 0;
}