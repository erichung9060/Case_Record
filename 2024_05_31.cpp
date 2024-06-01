// #define Many_SubTask
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(a) begin(a), end(a)
#define pb push_back
#define pdi pair<double, int>
#define val first
#define idx second
#define mp make_pair
const int mod = 998244353;
const int inf = 1e18;
const int MAXN = 100005;

int n, m;
vector<pdi> Map[MAXN];
priority_queue<pdi> pq;

double Dijkstra(int s, int e) {
    pq.push({1, s});

    vector<double> dis(n, 0);
    dis[s] = 1;
    
    while (!pq.empty()) {
        pdi cur = pq.top();
        pq.pop();
        if (dis[cur.idx] > cur.val) continue;
        
        for (auto i : Map[cur.idx]) {
            if (dis[cur.idx] * i.val > dis[i.idx]) {
                dis[i.idx] = dis[cur.idx] * i.val;
                pq.push({dis[i.idx], i.idx});
            }
        }
    }
    return dis[e];
}

void solve() {
    cin >> n >> m;
    while (m--) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        Map[u].pb({w, v});
        Map[v].pb({w, u});
    }
    int s, e;
    cin >> s >> e;
    cout << fixed << setprecision(3) << Dijkstra(s, e) << '\n';
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
