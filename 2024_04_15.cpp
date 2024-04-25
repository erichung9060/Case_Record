#include <bits/stdc++.h>
using namespace std;
#define MAXN 505

int V = 505;
bool adj[MAXN][MAXN];
deque<int> p[MAXN];
int m[MAXN];
int d[MAXN];
int q[MAXN], *qf, *qb;

void label_one_side(int x, int y, int b) {
    for (int i = b + 1; i < p[x].size(); ++i) {
        int z = p[x][i];
        if (d[z] == 1) {
            p[z] = p[y];
            p[z].insert(p[z].end(), p[x].rbegin(), p[x].rend() - i);

            d[z] = 0;
            *qb++ = z;
        }
    }
}

bool BFS(int r) {
    for (int i = 0; i < V; ++i) p[i].clear();
    p[r].push_back(r);

    memset(d, -1, sizeof(d));
    d[r] = 0;

    qf = qb = q;
    *qb++ = r;

    while (qf < qb){
        for (int x = *qf++, y = 0; y < V; ++y){
            if (adj[x][y] && m[y] != y){
                if (d[y] == -1){
                    if (m[y] == -1) {
                        for (int i = 0; i + 1 < p[x].size(); i += 2) {
                            m[p[x][i]] = p[x][i + 1];
                            m[p[x][i + 1]] = p[x][i];
                        }
                        m[x] = y;
                        m[y] = x;
                        return true;
                    } else {
                        int z = m[y];

                        p[z] = p[x];
                        p[z].push_back(y);
                        p[z].push_back(z);

                        d[y] = 1;
                        d[z] = 0;
                        *qb++ = z;
                    }
                }else if (d[y] == 0) {
                    int b = 0;
                    while (b < p[x].size() && b < p[y].size() && p[x][b] == p[y][b]) b++;
                    b--;

                    label_one_side(x, y, b);
                    label_one_side(y, x, b);
                }
            }
        }
    }
    return false;
}

int matching() {
    memset(m, -1, sizeof(m));

    int c = 0;
    for (int i = 0; i < V; ++i){
        if (m[i] == -1){
            if (BFS(i)) c++;
            else m[i] = i;
        }
    }
    return c;
}

int main() {
    int M;
    cin >> V >> M;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = 1;
    }

    cout << matching() << '\n';
    for (int i = 0; i < V; ++i) {
        if (i < m[i]) {
            cout << i << ' ' << m[i] << endl;
        }
    }
}
