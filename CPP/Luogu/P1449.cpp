#include <stack>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
stack <int> s;
int main(int argc, char const *argv[])
{
	char c = '"';
	int num = 0;
	while(c != '@'){
		if(c != '"'){
			if('0' <= c && c <= '9'){
				num *= 10;
				num += c - '0';
			}
			else if(c == '.'){
				s.push(num);
				num = 0;
			}
			else{
				int b = s.top();
				s.pop();
				int a = s.top();
				s.pop();
				if(c == '+')
					s.push(a + b);
				else if(c == '-')
					s.push(a - b);
				else if(c == '*')
					s.push(a * b);
				else if(c == '/')
					s.push(a / b);
			}
			scanf("%c", &c);
		}
		else{
			scanf("%c", &c);
		}
	}
	printf("%d", s.top());
	return 0;
}