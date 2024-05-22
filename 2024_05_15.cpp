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
const int MAXN=1000005;

set<pii> edge;
vector<int> Graph[MAXN];
int dfn[MAXN], up[MAXN], id;
vector<pii> ans;

void tarjan(int now, int fa) {
    dfn[now] = up[now] = ++id;

    for (auto i : Graph[now]) {
        if (!dfn[i]) tarjan(i, now);
        if (i != fa) up[now] = min(up[now], up[i]);
    }

    if (dfn[now] == up[now] && fa != -1) {
        if(!edge.count({now, fa})) ans.pb({fa, now});
        else ans.pb({now, fa});
    }
}


void solve(){
    int n, m;
    cin >> n >> m;
    while(m--){
        int a, b;
        cin >> a >> b;
        Graph[a].pb(b);
        Graph[b].pb(a);
        edge.insert({a, b});
    }
    for (int i = 0; i < n; i++) {
        if (!dfn[i]) tarjan(i, -1);
    }
    sort(all(ans));
    if(ans.size() == 0) cout << "No Critical Road\n";
    else{
        for(auto i:ans) cout << i.F << ' ' << i.S << '\n';
    }
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
