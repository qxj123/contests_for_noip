#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> PI;
const int maxn = 7000;
int n;
int k[2], s[2][maxn];
int win[2][maxn], lose[2][maxn];
bool p[2][maxn], v[2][maxn];
queue<PI> Q;
int main() {
    scanf("%d", &n);
    for (int i = 0; i < 2; ++i) {
        scanf("%d", &k[i]);
        for (int j = 0; j < k[i]; ++j)
            scanf("%d", &s[i][j]);
    }
    p[0][0] = p[1][0] = 0;
    v[0][0] = v[1][0] = 1;
    Q.push(make_pair(0, 0));
    Q.push(make_pair(1, 0));
    while (!Q.empty()) {
        PI cur = Q.front();
        Q.pop();
        int x = cur.first, l = cur.second, X = x ^ 1;
        for (int i = 0; i < k[X]; ++i) {
            int L = (l - s[X][i] + n) % n;
            if (v[X][L]) continue;
            if (p[x][l]) ++lose[X][L];
            else ++win[X][L];
            if (win[X][L]) {
                p[X][L] = 1;
                v[X][L] = 1;
                Q.push(make_pair(X, L));
            } else {
                if (lose[X][L] == k[X]) {
                    p[X][L] = 0;
                    v[X][L] = 1;
                    Q.push(make_pair(X, L));
                }
            }
        }
    }
    for (int i = 0; i < 2; putchar('\n'), ++i)
        for (int j = 1; j < n; ++j)
            if (v[i][j]) {
                if (p[i][j]) printf("Win ");
                else printf("Lose ");
            } else printf("Loop ");
    return 0;
}
