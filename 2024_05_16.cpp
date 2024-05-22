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
const int MAXN = 200005;

int w[MAXN], scc_w[MAXN];

vector<pii> edge;
vector<int> Graph[MAXN];
vector<int> SCC_Graph[MAXN];
stack<int> stk;
bool instk[MAXN];
int dfn[MAXN], up[MAXN], sccId[MAXN], sccRoot[MAXN], id, sccCnt;

void tarjan(int now) {
    dfn[now] = up[now] = ++id;

    stk.push(now);
    instk[now] = true;

    for (auto i : Graph[now]) {
        if (!instk[i] && dfn[i]) continue;

        if (!dfn[i]) tarjan(i);
        up[now] = min(up[now], up[i]);
    }

    if (dfn[now] == up[now]) {
        sccRoot[++sccCnt] = now;
        while (true) {
            int x = stk.top();
            stk.pop();
            instk[x] = false;
            sccId[x] = sccCnt;
            if (x == now) break;
        }
    }
}

bool used[MAXN];
int max_w[MAXN];
int dfs(int now) {
    if(used[now]) return max_w[now];
    used[now] = true;
    for (auto i : SCC_Graph[now]) {
        max_w[now] = max(max_w[now], dfs(i));
    }
    max_w[now] += scc_w[now];
    return max_w[now];
}

void solve() {
    int n, m, e, s;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> w[i];
    while (m--) {
        int a, b;
        cin >> a >> b;
        Graph[a].pb(b);
        edge.pb({a, b});
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= n; i++) {
        scc_w[sccId[i]] += w[i];
    }
    for (auto i : edge) {
        if (sccId[i.F] != sccId[i.S]) {
            SCC_Graph[sccId[i.F]].pb(sccId[i.S]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= sccCnt; i++) {
        ans = max(ans, dfs(i));
    }
    cout << ans << '\n';
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
