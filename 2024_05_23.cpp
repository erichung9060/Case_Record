// #define Many_SubTask
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(a) begin(a), end(a)
#define pb push_back
#define pii pair<int, int>
#define F first
#define S second
#define mp make_pair
const int mod = 998244353;
const int inf = 1e18;
const int MAXN = 1000005;

int conflict[MAXN], a[MAXN], n, m;
unordered_set<int> cur_group;
int Group[MAXN];
int last_group = 1;

void solve() {
    cin >> n >> m;
    int pre = inf;
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        if (pre < x) {
            conflict[x] = pre;
        }
        pre = x;
        a[i] = x;
    }
    for (int i = 1; i <= n; i++) {
        if (conflict[i]) {
            if (cur_group.count(conflict[i])) {
                last_group++;
                cur_group.clear();
            }
        }
        cur_group.insert(i);
        Group[i] = last_group;
    }
    
    for (int i = 2; i <= m; i++) {
        if (a[i - 1] > a[i]) {
            if (Group[a[i]] == Group[a[i - 1]]) last_group++;
        }
    }

    cout << last_group;
}

signed main() {
    cin.sync_with_stdio(0), cin.tie(0);
    int N = 1;
#ifdef Many_SubTask
    cin >> N;
#endif
    for (int i = 1; i <= N; i++) {
        solve();
    }
}
