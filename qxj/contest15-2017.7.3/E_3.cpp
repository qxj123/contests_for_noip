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
