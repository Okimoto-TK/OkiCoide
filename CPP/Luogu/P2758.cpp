#include <stdio.h>
#include <string>
using namespace std;
int f[2048][2048];
int getMin(int a, int b){
	return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
	char in1[2048];
	char in2[2048];
	scanf("%s", in1);
	scanf("%s", in2);
	string a = in1;
	string b = in2;
	int lenb = b.size();
	int len = a.size();
	if(len > lenb)
		for(int i = lenb; i < len; i ++)
			b += '*';
	else
		for(int i = len; i < lenb; i ++)
			a += '*';
	for(int i = 0; i < 2048; i ++){
		f[i][0] = i;
		f[0][i] = i;
	}
	for(int i = 1; i <= len; i ++){
		for(int j = 1; j <= lenb; j ++){
			if(a[i - 1] != b[j - 1])
				f[i][j] = getMin(f[i - 1][j - 1], getMin(f[i - 1][j], f[i][j - 1])) + 1;
			else
				f[i][j] = f[i - 1][j - 1];
		}
	}
	printf("%d", f[len][lenb]);
}