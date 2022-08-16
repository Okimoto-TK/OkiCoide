#include <cstdio>
#include <cstring>
#include <stack>
#define int long long
char a[100005];
int n, pool, p, m;
struct val
{
	bool t;
	int k, b;
	char op;
	val()
	{
		t = k = b = op = 0;
	}
	val operator+ (const val & x) const
	{
		val res;
		(res.k = k + x.k) %= m;
		(res.b = b + x.b) %= m;
		return res;
	}
	val operator- (const val & x) const
	{
		val res;
		(res.k = k - x.k) %= m;
		(res.b = b - x.b) %= m;
		return res;
	}
	val operator* (const val & x) const
	{
		val res;
		(res.k = k * x.b % m + b * x.k % m) %= m;
		res.b = b * x.b % m;
		return res;
	}
} v[100005];
char op[100005];
int ref[200];
char to[10];
val dg[100005];
int top;
val stk[100005];
inline bool digit(int i)
{
	return a[i] >= '0' && a[i] <= '9';	
}
int gcd(int a1, int b1)
{
	if(b1 == 0) return a1;
	return gcd(b1, a1 % b1);
}
int lcm(int a1, int b1)
{
	return a1 * b1 / gcd(a1, b1);
}
signed main()
{
	ref['+'] = ref['-'] = 1;
	ref['*'] = 2;
	ref['('] = 0;
	ref[')'] = 0;
	memset(op, 0, sizeof(op));
	scanf("%s", a + 1);
	scanf("%lld%lld", &p, &m);
	n = strlen(a + 1);
	int num = 0;
	for(int i = 1; i <= n + 1; i++)
	{
		//printf("%d", i);
		if(digit(i))
		{
			(num *= 10) %= m;
			(num += a[i] - '0') %= m;
			if(i == n || !digit(i + 1))
			{
				dg[++pool].b = num;
				num = 0;
			}
		}
		else if(a[i] == 'x')
		{
			dg[++pool].k = 1;
		}
		else if(a[i] == '+' || a[i] == '-' || a[i] == '*')
		{
			int o = ref[a[i]];
			if(o > ref[op[top]])
			{
				op[++top] = a[i];
			}
			else
			{
				while(o <= ref[op[top]])
				{
					dg[++pool].op = op[top--];
				}
				op[++top] = a[i];
			}
		}
		else if(a[i] == '(')
		{
			op[++top] = '(';
		}
		else if(a[i] == ')')
		{
			while(op[top] != '(')
			{
				dg[++pool].op = op[top];
				top--;
			}
			top--;
		}
		else if(a[i] == '\0')
		{
			while(top >= 1)
			{
				dg[++pool].op = op[top];
				top--;
			}
		}
		/*
		printf("%d: ", i);
		for(int i = 1; i <= top; i++)
		{
			printf("%c ", op[i]);
		}
		printf("\n");
		*/
	}
	top = 0;
	for(int i = 1; i <= pool; i++)
	{
		if(dg[i].op)
		{
			//printf("%c ", dg[i].op);
			val z;
			if(dg[i].op == '*')
			{
				z = stk[top] * stk[top - 1];
			}
			else if(dg[i].op == '+')
			{
				z = stk[top] + stk[top - 1];
			}
			else
			{
				z = stk[top - 1] - stk[top];
			}
			stk[--top] = z;
		}
		else
		{
			//printf("[%d %d] ", dg[i].k, dg[i].b);
			stk[++top] = dg[i];
		}
	}
//	printf("%d %d\n", stk[1].k, stk[1].b);
	for(int i = 0; i <= 1e7; i++)
	{
		if(((stk[1].k * i + stk[1].b) % m + m) % m == p)
		{
			printf("%lld", i);
			return 0;
		}
	}
	return 0;	
}
