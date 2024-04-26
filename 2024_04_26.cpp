#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
#define all(a) begin(a), end(a)
#define MAXN 1000005

vector<int> ROC[MAXN];

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        ROC[x].push_back(i);
    }
    vector<int> lis;
    for (int i = 0; i < M; i++) {
        int x;
        cin >> x;
        for (int j = ROC[x].size() - 1; j >= 0; j--) {
            int flight = ROC[x][j];
            auto it = lower_bound(lis.begin(), lis.end(), flight);
            if (it == lis.end()) {
                lis.push_back(flight);
            } else {
                *it = flight;
            }
        }
    }

    cout << lis.size() << endl;
    return 0;
}
