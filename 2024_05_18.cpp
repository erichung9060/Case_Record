// #define Many_SubTask
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(a) begin(a),end(a)
#define pb push_back
#define pii pair<int,int>
#define F first
#define S second
#define mp make_pair
const int mod=998244353;
const int inf=1e18;
const int MAXN=200005;

vector<int> dsu;
struct DSU {
    DSU(int n) {
        dsu.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            dsu[i] = i;
        }
    }
    bool same(int a, int b) {
        return fa(a) == fa(b);
    }
    int fa(int x) {
        if (dsu[x] == x) return x;
        return dsu[x] = fa(dsu[x]);
    }
    bool uni(int a, int b) {
        a = fa(a), b = fa(b);
        if (a == b) return false;
        dsu[b] = a;
        return true;
    }
};

vector<pii> G[MAXN];
vector<array<int,3>> edges;
bool used[MAXN];
queue<pii> q;

int shortest_path(int s,int e,int mi){
    used[s] = true;
    q.push({s, 0});
    while(!q.empty()){
        pii now = q.front(); q.pop();
        if(now.F == e) return now.S;
        for(auto i:G[now.F]){
            if(!used[i.F] && i.S >= mi) {
                q.push({i.F, now.S + 1});
                used[i.F] = true;
            }
        }
    }
}

void solve(){
    int n,m,s,e;
    cin >> n >> m >> s >> e;
    while(m--){
        int u,v,w;
        cin >> u >> v >> w;
        G[u].pb({v,w});
        G[v].pb({u,w});
        edges.pb({-w, u, v});
    }
    sort(all(edges));
    DSU dsu(n);
    for(auto [w,u,v]:edges){
        dsu.uni(u, v);
        if(dsu.same(s, e)){
            cout << -w << ' ' << shortest_path(s, e, -w) << '\n';
            return;
        }
    }
    cout << "-1\n";
}


signed main(){
    cin.sync_with_stdio(0),cin.tie(0);
    int N=1;
    #ifdef Many_SubTask
    cin >> N;
    #endif
    for(int i=1;i<=N;i++){
        solve();
    }
}
