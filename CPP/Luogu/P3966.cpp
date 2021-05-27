#include<bits/stdc++.h>
using namespace std;
int n,pos;
string s[209];
int ans[209];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int len=s[j].length();
			for(int k=0;k<len&&(pos=s[j].find(s[i],k))!=s[j].npos;k++){
				k=pos;
				ans[i]++;
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}
