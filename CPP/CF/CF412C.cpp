#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;
int n;
string s;
string c;
int main()
{
	cin >> n;
	cin >> s;
	for(register in
				s[j] = c[j];t i = 1; i < n; i ++){
		cin >> c;
		for(register int j = 0; j < c.size(); j ++){
			if(s[j] == c[j])
				continue;
			if(s[j] == '!')
				continue;
			if(s[j] == '?')
			else if(c[j] == '?')
				continue;
			else{
				s[j] = '!';
			}
		}
	}
	for(int i = 0; i < s.size(); i ++){
		if(s[i] == '!')
			s[i] = '?';
		else if(s[i] == '?')
			s[i] = 'a';
	}
	printf("%s", s.c_str());
	return 0;
}