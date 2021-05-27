#include <stdio.h>
#include <string>
#include <stack>
using namespace std;
int n;
bool check(const string a){
	char last = '0';
	int cnt = 0;
	for(int i = 0; i < a.size(); i ++){
		if((last <= '9' && last >= '0') ^ (a[i] >= '0' && a[i] <= '9')){
			last = a[i];
			cnt ++;
		}
	}
	return cnt == 2;
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		char a[64];
		scanf("%s", a);
		string str = a;
		if(check(str)){
			int c = 0;
			int j;
			for(j = 0; j < str.size() && !(str[j] <= '9' && str[j] >= '0'); j ++){
				c *= 26;
				c += str[j] - 'A' + 1;
			}
			int r = 0;
			for(; j < str.size(); j ++){
				r *= 10;
				r += str[j] - '0';
			}
			printf("R%dC%d\n", r, c);
		}
		else{
			int j;
			int r = 0;
			for(j = 1; j < str.size() && str[j] != 'C'; j ++){
				r *= 10;
				r += str[j] - '0';
			}
			int c = 0;
			j ++;
			for(; j < str.size(); j ++){
				c*= 10;
				c += str[j] - '0';
			}
			stack <char> _c;
			while(c != 0){
				if(c % 26 + 'A' - 1 >= 'A'){
					_c.push(char(c % 26 + 'A' - 1));
					c /= 26;
				}
				else{
					_c.push(char((c - 1) % 26 + 'A'));
					c /= 26;
					c --;
				}
			}
			while(!_c.empty()){
				printf("%c", _c.top());
				_c.pop();
			}
			printf("%d\n", r);
		}
	}
	return 0;
}