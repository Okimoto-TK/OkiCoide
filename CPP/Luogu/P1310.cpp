#include <stdio.h>
#include <stack>
#include <queue>
#include <string>
#include <map>
using namespace std;
const int p = 10007;
struct stt
{
	int zero;
	int one;
	stt(int a, int b)
	{
		zero = a;
		one = b;
	}
};
int n;
stack <int> stk_i;
stack <stt> stk_s;
queue <int> que_s;
map <char, int> pri_o;
char buf[100007];
bool ptx[100007];
int main()
{
	pri_o['*'] = 2;
	pri_o['+'] = 1;
	scanf("%d", &n);
	scanf("%s", buf);
	string str;
	for(int i = 0; i <= n; i++)
	{
		if((i == n || buf[i] != '(') && (i == 0 || buf[i - 1] != ')'))
		{
			str += 'x';
		}
		if(buf[i] != '\0') str += buf[i];
	}
	for(int i = 0; i < str.size(); i++)
	{
		char c = str[i];
		if(c == 'x')
		{
			que_s.push('x');
		}
		else if(c == '(')
		{
			stk_i.push(c);
		}
		else if(c == ')')
		{
			while(!stk_i.empty() && stk_i.top() != '(')
			{
				que_s.push(stk_i.top());
				stk_i.pop();
			}
			stk_i.pop();
		}
		else
		{
			while(!stk_i.empty() && pri_o[stk_i.top()] >= pri_o[c])
			{
				que_s.push(stk_i.top());
				stk_i.pop();
			}
			stk_i.push(c);
		}
	}
	while(!stk_i.empty())
	{
		que_s.push(stk_i.top());
		stk_i.pop();
	}
	while(!que_s.empty())
	{
		char c = que_s.front();
		que_s.pop();
		if(c == 'x')
		{
			stk_s.push(stt(1, 1));
		}
		else if(c == '+')
		{
			stt a = stk_s.top();
			stk_s.pop();
			stt b = stk_s.top();
			stk_s.pop();
			stk_s.push(stt(a.zero * b.zero % p, (a.zero * b.one % p + a.one * b.zero % p + a.one * b.one % p) % p));
		}
		else
		{
			stt a = stk_s.top();
			stk_s.pop();
			stt b = stk_s.top();
			stk_s.pop();
			stk_s.push(stt((a.zero * b.zero % p + a.zero * b.one % p + a.one * b.zero % p) % p, a.one * b.one % p));
		}
	}
	printf("%d", stk_s.top().zero % p);
	return 0;
}
