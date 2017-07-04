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
> 给你一个有向图的点数 n，所有加边方式的数量 q 和源点 s (1 ≤ n, q ≤ 10<sup>5</sup>, 1 ≤ s ≤ n)。有3种加边方式，1 u v w：点 u 到点 v 的边权为 w 的边；2 u l r w：点 u 到点 v ∈ [l, r] 的边权为 w 的边；2 u l r w：点 v ∈ [l, r] 到点 u 的边权为 w 的边 (1 ≤ w ≤ 10<sup>9</sup>)。求源点 s 到每个点的最短路径。

> Time Limit: 2000 ms  Memory Limit：262144 kB

### Solution
> 我们以图中的点为下表建两棵线段树，一棵都是父节点连向子节点权为0的边，一棵都是子节点连向父节点权为0的边。我们对于第一种加边方式直接加边；第二种：将点 u 连向在第一棵线段树上可以覆盖 [l, r] 的线段树节点，边权为 w（点 u 可以通过这些线段树节点一直向下，到达 [l, r] 上的点，代价为 w）；第三种：将在第二棵线段树上可以覆盖 [l, r] 的线段树节点连向点 u，边权为 w（ [l, r] 上的点可以一直向上，通过这些线段树节点，到达点 u ，代价为 w）。建以后有O(n)个点，O(nlog<sub>2</sub>n)条边，跑一个Dijkstra + 堆优化或 set 优化，时间复杂度O(nlog<sup>2</sup>n)。我是用SPFA，这个复杂度O(knlog<sub>2</sub>n)（SPFA复杂度到底是多少我也不知道）。

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
> 有一个长度为 n (1 ≤ n ≤ 10<sup>5</sup>) 的序列 a<sub>1</sub>, a<sub>2</sub>, ..., a<sub>n</sub> (1 ≤ a<sub>i</sub> ≤ n)。每个 a<sub>i</sub> 代表一种颜色，询问当每段内的最大颜色种类为 k (k 从 1 到 n)，原序列最少分成几段。

> Time Limit: 2000 ms  Memory Limit：262144 kB

### Solution
> 首先我们可以贪心，每次选择最长的颜色种类为 k （或者分完了）的段。我们知道这至少可以选择长度为 k 的段，所以计算 k = 1 - n 的段的总数量为 O(n / 1 + n / 2 + ... + n / n) = O(n * (1 + 1 / 2 + ... + 1 / n)) = O(nlog<sub>2</sub>n)。当前位置为 i，从 i 到 n，如果 a<sub>j</sub>(i ≤ j ≤ n)，是第一次出现的某种颜色，贡献为 1，否则为 0。

> 1) 我们考录建主席树，第 i 个版本为原序列 i - n 的数在相应位置上的贡献。第 i 个版本是从第 i + 1 个版本在第 i 个位置的贡献 + 1，若存在 a<sub>j</sub> = a<sub>i</sub>(i ≤ j ≤ n，j 是满足前面条件的最小的位置)，将第 j 个位置的贡献 - 1 (第 i + 1 个版本此位置的贡献为 1，现将其删除)。查询的话只要在线段树上二分 O(log<sub>2</sub>n)。主席树总时间复杂度为 O(nlog<sup>2</sup>n)。

> 2) 我们也可以用树状数组做，每个位置开一个vector，存此时位于这里的 k。最初先算出整个序列的所有贡献，此时计算在第 i (1 ≤ i ≤ n)位置个位置上的询问，这些询问的答案 + 1，将它们向后放到相应的位置的vector里，此时 i 的位置的贡献 - 1，若存在 a<sub>j</sub> = a<sub>i</sub>(i ≤ j ≤ n，j 是满足前面条件的最小的位置)，将第 j 个位置的贡献 + 1。树状数组总时间复杂度为 O(nlog<sub>2</sub>n)。

> 还有一个复杂度爆炸但是能跑过去的算法。我们知道最后答案的序列的数字的种数为 O(n<sup>0.5</sup>)（前n<sup>1.5</sup>的个数为O(n<sup>1.5</sup>)，后面的个数是小于n<sup>1.5</sup>的），二分答案相同的位置，将这些询问全部赋成相同的值。时间复杂度为 O(n<sup>1.5</sup>log<sup>2</sup>n)。

#### 主席树 O(nlog<sup>2</sup>n)

```cpp
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
```

#### 树状数组 O(nlog<sup>2</sup>n)

```cpp
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
```

#### 二分 O(n<sup>1.5</sup>log<sub>2</sub>n)

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 100000;
int n;
int a[maxn + 1], last[maxn + 1], ans[maxn + 1];
int calc(int k) {
    int cnt = 0, tot = k;
    memset(last, -1, sizeof(last));
    for (int i = 1; i <= n; ++i)
        if (last[a[i]] != cnt) {
            ++tot;
            if (tot > k) {
                ++cnt;
                tot = 1;
            }
            last[a[i]] = cnt;
        }
    return cnt;
}
void Divide(int l, int r) {
    ans[l] = calc(l);
    ans[r] = calc(r);
    if (ans[l] == ans[r]) {
        for (int i = l + 1; i < r; ++i)
            ans[i] = ans[l];
        return;
    }
    int mid = (l + r) >> 1;
    if (l + 1 <= mid) Divide(l + 1, mid);
    if (mid + 1 <= r - 1) Divide(mid + 1, r - 1);
    return;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    Divide(1, n);
    for (int i = 1; i <= n; ++i)
        printf("%d ", ans[i]);
    return 0;
}
```
