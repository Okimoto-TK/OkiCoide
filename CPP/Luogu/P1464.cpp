#include <stdio.h>
#include <string>
using namespace std;
long long x, y, z;
long long tab[22][22][22];
bool hit[22][22][22];
string out = "";
long long w(long long a, long long b, long long c){
	if(a >= 0 && b >= 0 && c >= 0 && a <= 20 && b <= 20 && c <= 20 && hit[a][b][c]){
		return tab[a][b][c];
	}
	if(a <= 0 || b <= 0 || c <= 0){
		return 1;
	}
	else if(a > 20 || b > 20 || c > 20){
		return w(20, 20, 20);
	}
	else if(a < b && b < c){
		int val = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
		hit[a][b][c] = true;
		tab[a][b][c] = val;
		return val;
	}
	else{
		int val = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);
		hit[a][b][c] = true;
		tab[a][b][c] = val;
		return val;
	}
}
int main(){
	scanf("%lld %lld %lld", &x, &y, &z);
	while(x != -1 || y != -1 || z != -1){
		long long ans = w(x, y, z);
		out += "w(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ") = " + to_string(ans) + "\n";
		scanf("%lld %lld %lld", &x, &y, &z);
	}
	printf("%s", out.c_str());
	return 0;
}