#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100000;
int n;
int a[maxn + 1];
int root[maxn + 2], last[maxn + 1];
int tot = 0;
struct node {
    int lc, rc, l, r, sum;
} p[maxn << 6];
int Build(int l, int r) {
    int k = ++tot;
    p[k].l = l;
    p[k].r = r;
    p[k].sum = 0;
    if (l == r) return k;
    p[k].lc = Build(l, (l + r) >> 1);
    p[k].rc = Build(((l + r) >> 1) + 1, r);
    return k;
}
int Insert(int k, int x, int d) {
    int K = ++tot;
    p[K].l = p[k].l;
    p[K].r = p[k].r;
    if (p[k].l == x && x == p[k].r) {
        p[K].sum = p[k].sum + d;
        return K;
    }
    if (x <= p[p[k].lc].r) {
        p[K].lc = Insert(p[k].lc, x, d);
        p[K].rc = p[k].rc;
    } else {
        p[K].lc = p[k].lc;
        p[K].rc = Insert(p[k].rc, x, d);
    }
    p[K].sum = p[p[K].lc].sum + p[p[K].rc].sum;
    return K;
}
int Query(int k, int K) {
    if (p[k].l == p[k].r) return p[k].l;
    if (K <= p[p[k].lc].sum) return Query(p[k].lc, K);
    return Query(p[k].rc, K - p[p[k].lc].sum);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    root[n + 1] = Build(1, n);
    for (int i = n; i; --i) {
        root[i] = root[i + 1];
        if (last[a[i]]) root[i] = Insert(root[i], last[a[i]], -1);
        root[i] = Insert(root[i], last[a[i]] = i, 1);
    }
    for (int i = 1; i <= n; ++i) {
        int cnt = 1;
        for (int j = 1; p[root[j]].sum > i; ++cnt, j = Query(root[j], i + 1));
        printf("%d ", cnt);
    }
    return 0;
}
