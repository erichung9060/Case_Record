#include <bits/stdc++.h>
using namespace std;
#define all(a) begin(a), end(a)
#define pb push_back
#define MAXN 30

struct DSU {
    vector<int> dsu, dsusz;
    int group;

    DSU(int n) {
        dsu.resize(n + 1);
        dsusz.resize(n + 1);
        group = n;
        for (int i = 1; i <= n; i++) {
            dsu[i] = i;
            dsusz[i] = 1;
        }
    }
    bool isRoot(int x) {
        return dsu[x] == x;
    }
    int fa(int x) {
        if (isRoot(x)) return x;
        return dsu[x] = fa(dsu[x]);
    }
    bool uni(int a, int b) {
        a = fa(a), b = fa(b);
        if (a == b) return false;
        dsu[b] = a;
        dsusz[a] += dsusz[b];
        dsusz[b] = 0;
        group--;
        return true;
    }
};

vector<int> connect[MAXN];  // adjacency list

int main() {
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        connect[u].pb(v);
        connect[v].pb(u);
        dsu.uni(u, v);
    }
    cout << dsu.group << '\n';

    vector<bool> is_circle(n + 1, true);
    int ans = 0;
    set<int> knot;
    for (int i = 1; i <= n; i++) {
        if (connect[i].size() != 2) is_circle[dsu.fa(i)] = false;
        if (connect[i].size() > 2) {
            ans++;
            knot.insert(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        if (dsu.isRoot(i) && is_circle[i]) {
            ans++;
        }
    }
    cout << max(dsu.group - 1, ans) << '\n';

    int x;
    vector<bool> open_circle(n + 1, false);
    set<int> input;
    while (cin >> x) {
        open_circle[dsu.fa(x)] = true;
        input.insert(x);
    }
    bool suc = true;
    if (!includes(all(input), all(knot))) suc = false;
    for (int i = 1; i <= n; i++) {
        if (dsu.isRoot(i) && is_circle[i]) {
            if (!open_circle[i]) suc = false;
        }
    }
    if (suc) cout << "Yes\n";
    else cout << "No\n";
}
