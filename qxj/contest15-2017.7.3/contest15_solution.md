# Contest15

[Div. 2](http://codeforces.com/contest/787)

# Before

## Div2. A

### Problem Description
>  给你4个正整数 a,b,c,d (1 ≤ a,b,c,d ≤ 100)。求当 a * k1 + b = c * k2 + d 时，它的值。不可能输出 -1。

> Time Limit: 1000 ms  Memory Limit：262144 kB

### Solution
> 直接暴力枚举 k1, 算出 k2 是否为非负整数。k1 不会很大，因为 (a * k1 + b - d) % c 的值在 [0, c - 1]，所以 (a * k1 + b - d) % c 一旦重复，接下来就会重复。时间复杂度 O(c)。

```cpp
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
```

## Div2. B

### Problem Description
> 有 n 对 Ricks,Mortys 和 m 个队伍 (1 ≤ n, m ≤ 10<sup>4</sup>)。每对 Ricks,Mortys 中有一个为叛徒。给你这 m 个队伍所包含的人，一个人可能多次出现在一些队伍中。若存在一个队伍，它可能全部为叛徒，那这次活动就该取消，输出 "YES"，否则输出 "NO"。v<sub>i,j</sub> 为第 i 个队伍，第 j 个人的编号。若 v<sub>i,j</sub> > 0，它为第 v<sub>i,j</sub> 对的 Rick，否则为第 |v<sub>i,j</sub>| 对的 Morty。

> Time Limit: 2000 ms  Memory Limit：262144 kB

### Solution
> 若每个队伍，存在一对互为相反数的值，那么这个队伍至少有一个人不是叛徒，否则该队伍肯能全为叛徒。时间复杂度 O(nm)。

```cpp
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
```

----------------------------------- 我是一条神奇的分割线 -----------------------------------

# After

## Div2. C

### Problem Description
> 有 n (2 ≤ n ≤ 7000) 个物体围成一圈，编号为1的物体为黑洞，其它为星球。有一个怪物在某个星球上，Rick 有 k1 种操作，s<sub>1,i</sub>，他可以使怪物顺时针移动s<sub>1,i</sub>个，Morty 有 k2 种操作，s<sub>2,i</sub>，他可以使怪物顺时针移动s<sub>2,i</sub>个。把怪物移到黑洞的人获胜。对于每一种情况（Rick 或 Morty先手，怪物初始时在第 i 个星球(2 ≤ i ≤ n)）。

> Time Limit: 4000 ms  Memory Limit：262144 kB

### Solution
> 从终止点开始 BFS，若当前点为必败态(Lose)，那么可以到达它的点为必胜态(Win)。若某个点到达的所有点都为必胜态(Win)，那么它为必败态(Lose)。为 BFS 到的都为可循环态(Loop)。时间复杂度为 O(n<sup>2</sup>)。

```cpp
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
```

## Div2. D

### Problem Description
> 给你点数 n，加边方式 q 和源点 s (1 ≤ n, q ≤ 10<sup>5</sup>, 1 ≤ s ≤ n)。有3种加边方式，1 u v w：点 u 到点 v 的边权为 w 的边；2 u l r w：点 u 到点 v ∈ [l, r] 的边权为 w 的边；2 u l r w：点 v ∈ [l, r] 到点 u 的边权为 w 的边。求源点 s 到每个点的最短路径。

> Time Limit: 2000 ms  Memory Limit：262144 kB

### Solution
> 时间复杂度O(nlog<sup>2</sup>n)。

```cpp
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
```

## Div2. E

### Problem Description
> 

> Time Limit: 2000 ms  Memory Limit：262144 kB

### Solution
> 

```cpp

```
