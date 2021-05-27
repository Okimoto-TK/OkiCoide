#include <stdio.h>
#include <string>
using namespace std;
string k;
int p;
string c;
string m;
bool cap[2048];
char inBuf[2048];
bool isCap(char ch){
	return 'A' <= ch && ch <= 'Z';
}
char upper(char ch){
	return (ch > 'Z' ? (ch - 'a' + 'A') : ch);
}
int main(int argc, char const *argv[])
{
	scanf("%s", inBuf);
	k = inBuf;
	scanf("%s", inBuf);
	c = inBuf;
	for(int i = 0; i < (int)c.size(); i ++){
		cap[i] = isCap(c[i]);
	}
	for(int i = 0; i < (int)c.size(); i ++){
		m += ((upper(c[i]) - upper(k[p ++]) + 26) % 26 + (cap[i] ? 'A' : 'a'));
		p %= k.size();
	}
	printf("%s", m.c_str());
	return 0;
}