#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using pii = pair<int, int>;
vector<pii> flights;

int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    int N, M, R;
    cin >> N >> M >> R;

    for (int i = 0; i < R; ++i) {
        int u, v;
        cin >> u >> v;
        flights.push_back({u, v});
    }

    sort(flights.begin(), flights.end(), [](const pii& a, const pii& b) {
        return a.first < b.first || (a.first == b.first && a.second > b.second);
    });

    vector<int> lis;
    for (auto flight : flights) {
        auto it = lower_bound(lis.begin(), lis.end(), flight.second);
        if (it == lis.end()) {
            lis.push_back(flight.second);
        } else {
            *it = flight.second;
        }
    }

    cout << lis.size() << endl;
    return 0;
}
