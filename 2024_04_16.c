#include <stdio.h>
#include <stdlib.h>
#define int long long
#define MAX_N 100005
const int inf = 1e18;

int people[MAX_N];
int n;

int getID(int val) {
    for (int i = 0; i < n; i++) {
        if (people[i] == val) {
            return i;
        }
    }
    return inf;
}

int ldis(int x,int y){
    if(y < x) return x - y;
    return x + (n - y);
}

int rdis(int x,int y){
    if(y > x) return y - x;
    return y + (n - x);
}

int find_friend(int x, int d, int R, int id) {
    int l = inf, r = inf;
    int l_min_dis = inf, r_min_dis = inf;
    for (int i = 0; i < n; i++) {
        if(i == id) continue;
        if (x - R <= people[i] && people[i] <= x + R) {
            int l_dis = ldis(id, i);
            if (l_dis < l_min_dis) {
                l_min_dis = l_dis;
                l = i;
            }
            int r_dis = rdis(id, i);
            if (r_dis < r_min_dis) {
                r_min_dis = r_dis;
                r = i;
            }
        }
    }
    if (l_min_dis <= r_min_dis) {
        return l;
    } else {
        return r;
    }
}

signed main() {
    scanf("%lld", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &people[i]);
    }

    int x, d, r, rest = n;
    while (scanf("%lld %lld %lld", &x, &d, &r) != EOF) {
        int id = getID(x);
        if (id == inf) continue;

        int friend_index = find_friend(x, d, r, id);
        if (friend_index != inf) {
            for (int i = 0, j = 0; i < n; i++) {
                if (i == id || i == friend_index) continue;
                people[j++] = people[i];
            }
            n -= 2;
        }
    }

    if (n == 0) {
        printf("Wonderful\n");
    } else {
        for (int i = 0; i < n; i++)  printf("%lld ", people[i]);
        printf("\n");
    }

    return 0;
}
