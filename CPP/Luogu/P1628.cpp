#include <stdio.h>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
int n;
string str[100001];
string tar;
queue <string> ans;
bool cmp(string a, string b){
	return a < b;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		char temp[128];
		scanf("%s", temp);
		str[i] = temp;
	}
	sort(str, str + n, cmp);
	char temp[128];
	scanf("%s", temp);
	tar = temp;
	bool flg = false;
	for(int i = 0; i < n; i ++){
		if(str[i].size() < tar.size())
			continue;
		if(str[i].substr(0, tar.size()) == tar){
			ans.push(str[i]);
			flg = true;
		}
		else{
			if(flg)
				break;
		}
	}
	while(!ans.empty()){
		printf("%s\n", ans.front().c_str());
		ans.pop();
	}
	return 0;
}