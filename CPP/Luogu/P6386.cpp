#include <stdio.h>
#include <string>
using namespace std;
int a, b, c, d, p, m, g;
string vau(int x)
{
    bool s, t;
    if(x % (a + b) == 0 || x % (a + b) > a){ s = false; }
    else{ s = true; }
    if(x % (c + d) == 0 || x % (c + d) > c){ t = false; }
    else{ t = true; }
    if(s & t){ return "both"; }
    else if(s | t){ return "one"; }
    return "none";
}
int main()
{
    scanf("%d%d%d%d%d%d%d", &a, &b, &c, &d, &p, &m, &g);
    printf("%s\n", vau(p).c_str());
    printf("%s\n", vau(m).c_str());
    printf("%s\n", vau(g).c_str());
    return 0;
}
