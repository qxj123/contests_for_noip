#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int a, b, c, d;
bool p[100];
int main() {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    for (int i = 0; ; ++i) {
        if (a * i + b < d) continue;
        if (!((a * i + b - d) % c)) {
            printf("%d\n", a * i + b);
            return 0;
        }
        if (p[(a * i + b - d) % c]) break;
        p[(a * i + b - d) % c] = 1;
    }
    puts("-1");
    return 0;
} 
