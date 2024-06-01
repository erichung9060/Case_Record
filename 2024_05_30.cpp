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
const int inf = 1e9;
const int MAXN = 1000005;

unordered_map<string, int> name_to_index;
int idx = 0;

int get_index(string name) {
    if (!name_to_index.count(name)) {
        name_to_index[name] = idx++;
    }
    return name_to_index[name];
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> dis(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) dis[i][i] = 0;

    for (int i = 0, w; i < m; i++) {
        string u, v;
        cin >> u >> v >> w;
        int index_u = get_index(u);
        int index_v = get_index(v);
        if (w < dis[index_u][index_v]) {
            dis[index_u][index_v] = w;
            dis[index_v][index_u] = w;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    int pre = -1, ans = 0;
    while(k--){
        string des;
        cin >> des;
        int index_des = get_index(des);
        
        if(pre != -1){
            ans+=dis[pre][index_des];
        }
        pre = index_des;
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
