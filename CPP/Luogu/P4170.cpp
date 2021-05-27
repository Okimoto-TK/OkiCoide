#include <stdio.h>
#include <string>
using namespace std;
int f[64][64];
int getMin(int a, int b){
	return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
	char in[64];
	scanf("%s", in);
	string s = in;
	int n = s.size();
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			f[i][j] = 32768;
	for(int l = 0; l < n; l ++){
		for(int i = 0; i < n; i ++){
			int j = i + l;
			if(j >= n)
				break;
			if(i == j)
				f[i][j] = 1;
			else if(s[i] == s[j]){
				if(i - 1 == -1)
					f[i][j] = f[i][j - 1];
				else if(j - 1 == -1)
					f[i][j] = f[i - 1][j];
				else
					f[i][j] = getMin(f[i - 1][j], f[i][j - 1]);
			}
			else{
				for(int k = i; k < j; k ++){
					f[i][j] = getMin(f[i][j], f[i][k] + f[k + 1][j]);
				}
			}
		}
	}
	printf("%d", f[0][n - 1]);
	return 0;
}