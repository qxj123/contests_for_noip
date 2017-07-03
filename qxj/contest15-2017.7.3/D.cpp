#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
typedef long long LL;
const int maxn = 100000;
const LL INF = 0x7f7f7f7f7f7f7f7f;
int n, q, s;
int tot = -1, head[maxn << 3 | 1];
struct node1 {
    int p, next, w;
} edge[maxn << 6];
inline void Add(int u, int v, int w) {
    edge[++tot] = (node1) {v, head[u], w};
    head[u] = tot;
    return;
}
int K;
struct node2 {
    int l, r, num1, num2;
} p[maxn << 2 | 1];
void Build(int k, int l, int r) {
    p[k].l = l;
    p[k].r = r;
    if (l == r) {
        p[k].num1 = p[k].num2 = l;
        return;
    }
    p[k].num1 = ++K;
    p[k].num2 = ++K;
    Build(k << 1, l, (l + r) >> 1);
    Build(k << 1 | 1, ((l + r) >> 1) + 1, r);
    Add(p[k].num1, p[k << 1].num1, 0);
    Add(p[k].num1, p[k << 1 | 1].num1, 0);
    Add(p[k << 1].num2, p[k].num2, 0);
    Add(p[k << 1 | 1].num2, p[k].num2, 0);
    return;
}
void Query1(int k, int l, int r, int u, int w) {
    if (l <= p[k].l && p[k].r <= r) {
        Add(u, p[k].num1, w);
        return;
    }
    if (l <= p[k << 1].r) Query1(k << 1, l, r, u, w);
    if (p[k << 1 | 1].l <= r) Query1(k << 1 | 1, l, r, u, w);
    return;
}
void Query2(int k, int l, int r, int u, int w) {
    if (l <= p[k].l && p[k].r <= r) {
        Add(p[k].num2, u, w);
        return;
    }
    if (l <= p[k << 1].r) Query2(k << 1, l, r, u, w);
    if (p[k << 1 | 1].l <= r) Query2(k << 1 | 1, l, r, u, w);
    return;
}
LL d[maxn << 3 | 1];
bool exist[maxn << 3 | 1];
queue<int> Q;
int main() {
    scanf("%d%d%d", &n, &q, &s);
    memset(head, -1, sizeof(head));
    K = n;
    Build(1, 1, n);
    for (int t, u, v, l, r, w; q--; ) {
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d%d", &u, &v, &w);
            Add(u, v, w);
        } else {
            scanf("%d%d%d%d", &u, &l, &r, &w);
            if (t == 2) Query1(1, l, r, u, w);
            else Query2(1, l, r, u, w);
        }
    }
    memset(d, 0x7f, sizeof(d));
    d[s] = 0;
    Q.push(s);
    exist[s] = 1;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        exist[u] = 0;
        for (int i = head[u]; ~i; i = edge[i].next) {
            int v = edge[i].p, w = edge[i].w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (!exist[v]) {
                    Q.push(v);
                    exist[v] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
        if (d[i] != INF) printf("%lld ", d[i]);
        else printf("-1 ");
    return 0;
}
