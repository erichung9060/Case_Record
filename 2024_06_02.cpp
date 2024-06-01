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
const int MAXN = 105;

int rest[MAXN][MAXN], from[MAXN], mi[MAXN], n, m;
int a[MAXN], b[MAXN];

bool bfs(int s, int e) {
    queue<int> q;
    memset(from, -1, sizeof(from));

    q.push(s);
    from[s] = s;
    mi[s] = INT_MAX;

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i <= n + 1; i++) {
            if (from[i] == -1 && rest[now][i]) {
                from[i] = now;
                mi[i] = min(mi[now], rest[now][i]);

                if (i == e) return true;
                q.push(i);
            }
        }
    }
    return false;
}

int max_flow(int s, int e) {
    int sum_flow = 0;
    while (bfs(s, e)) {
        int increase_flow = mi[e];
        sum_flow += increase_flow;

        int now = e;
        while (now != s) {
            rest[from[now]][now] -= increase_flow;
            rest[now][from[now]] += increase_flow;
            now = from[now];
        }
    }
    return sum_flow;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    int need = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > b[i]) rest[0][i] += a[i] - b[i];
        else rest[i][n + 1] += b[i] - a[i], need += b[i] - a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1, x; j <= n; j++) {
            cin >> x;
            rest[i][j] += x;
        }
    }
    cout << need - max_flow(0, n + 1) << '\n';
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
