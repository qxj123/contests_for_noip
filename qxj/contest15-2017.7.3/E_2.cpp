#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 100000;
int n;
int a[maxn + 1], head[maxn + 1], Next[maxn + 1];
int c[maxn + 1], ans[maxn + 1];
vector<int> v[maxn + 2];
inline int lowbit(int x) {
    return (x) & (-x);
}
inline void Add(int x, int k) {
    for (; x <= n; x += lowbit(x))
        c[x] += k;
    return;
}
inline int Query(int k) {
    int x = 0;
    for (int i = 16; i >= 0; --i)
        if (x + (1 << i) <= n && c[x + (1 << i)] <= k)
            k -= c[x += 1 << i];
    return x + 1;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++i)
        head[i] = Next[i] = n + 1;
    for (int i = n; i; --i) {
        Next[i] = head[a[i]];
        head[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        if (head[i] <= n) Add(head[i], 1);
    for (int i = 1; i <= n; ++i)
        v[1].push_back(i);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0, t = v[i].size(); j < t; ++j) {
            int k = v[i][j];
            v[Query(k)].push_back(k);
            ++ans[k];
        }
        Add(i, -1);
        Add(Next[i], 1);
    }
    for (int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    return 0;
}
