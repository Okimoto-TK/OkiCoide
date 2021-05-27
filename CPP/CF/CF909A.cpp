#include <stdio.h>
#include <string>
using namespace std;
char a[16];
char b[16];
string ans = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
string s1;
string s2;
string getMin(string a, string b){
	return a < b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%s", a);
	scanf("%s", b);
	s1 = a;
	s2 = b;
	for(int i = 1; i <= s1.size(); i ++){
		string t1 = s1.substr(0, i);
		for(int j = 1; j <= s2.size(); j ++){
			string t2 = s2.substr(0, j);
			string t = t1 + t2;
			ans = getMin(t, ans);
		}
	}
	printf("%s", ans.c_str());
	return 0;
}