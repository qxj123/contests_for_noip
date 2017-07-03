#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 10000;
int n, m;
bool p[maxn << 1 | 1];
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, k; i <= m; ++i) {
        scanf("%d", &k);
        memset(p, 0, sizeof(p));
        for (int j = 1, v; j <= k; ++j) {
            scanf("%d", &v);
            p[v + n] = 1;
        }
        bool flag = 1;
        for (int j = 1; j <= n; ++j)
            if (p[j + n] && p[-j + n]) {
                flag = 0;
                break;
            }
        if (flag) {
            puts("YES");
            return 0;
        }
    }
    puts("NO");
    return 0;
}
