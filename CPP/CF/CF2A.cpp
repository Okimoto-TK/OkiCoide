#include <stdio.h>
#include <string>
#include <map>
using namespace std;
struct ord
{
	string s;
	int sc;
};
map <string, int> m;
map <string, int> _m;
int n;
int mx = 0;
ord s[1001];
int getMax(int a, int b){
	return a > b ? a : b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		char c[64];
		int sc;
		scanf("%s%d", c, &sc);
		s[i].s = c;
		s[i].sc = sc;
		string t = c;
		if(m.find(t) == m.end()){
			m.insert(pair <string, int> (t, sc));
		}
		else
			m[t] += sc;
	}
	for(auto i : m){
		if(i.second >= mx){
			mx = i.second;
		}
	}
	for(int i = 0; i < n; i ++){
		string t = s[i].s;
		int sc = s[i].sc;
		if(_m.find(t) == _m.end()){
			_m.insert(pair <string, int> (t, sc));
		}
		else
			_m[t] += sc;
		if(_m[t] >= mx && m[t] == mx){
			printf("%s", t.c_str());
			return 0;
		}
	}
	return 0;
}