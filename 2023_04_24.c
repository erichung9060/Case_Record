#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define int long long
#define MAXN 1000005

typedef struct pair pair;
struct pair {
    int pri, end;
    pair *nxt;
};

typedef struct node node;
struct node {
    int val;
    node *nxt;
};

pair *price[MAXN];
node *graph[MAXN];
int inv[MAXN], child[MAXN], queue[MAXN], Q[MAXN], graph_len[MAXN], ttl[MAXN], child_done[MAXN], Tail;

void get_child(int now) {
    for (node *i = graph[now]; i; i = i->nxt) {
        get_child(i->val);
        child[now] += child[i->val];
    }
    child[now]++;
}

int min(int a, int b) {
    if (a < b)
        return a;
    else
        return b;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

typedef struct {
    int value;
    int priority;
} pq_node;

typedef struct {
    pq_node *nodes;
    int len;
    int size;
} priority_queue;

void pq_init(priority_queue *pq, int size) {
    pq->nodes = (pq_node *)malloc(sizeof(pq_node) * size);
    pq->len = 0;
    pq->size = size;
}

void pq_insert(priority_queue *pq, int value, int priority) {
    pq_node node = {value, priority};
    int i = pq->len;
    pq->len++;

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (node.priority >= pq->nodes[parent].priority) {
            break;
        }

        pq->nodes[i] = pq->nodes[parent];
        i = parent;
    }

    pq->nodes[i] = node;
}

int pq_delete(priority_queue *pq) {
    int max_value = pq->nodes[0].value;
    pq->len--;
    pq_node last_node = pq->nodes[pq->len];

    int i = 0;
    int child = 1;

    while (child < pq->len) {
        if (child + 1 < pq->len && pq->nodes[child + 1].priority < pq->nodes[child].priority) {
            child++;
        }

        if (last_node.priority <= pq->nodes[child].priority) {
            break;
        }

        pq->nodes[i] = pq->nodes[child];
        i = child;
        child = 2 * i + 1;
    }

    pq->nodes[i] = last_node;

    return max_value;
}
priority_queue pq[MAXN];

signed main() {
    int n, m, C;
    scanf("%lld %lld %lld", &n, &m, &C);
    for (int i = 2; i <= n; i++) {
        int x;
        scanf("%lld", &x);
        inv[i] = x;

        node *newNode = malloc(sizeof(node));
        newNode->val = i;
        newNode->nxt = graph[x];
        graph[x] = newNode;
        graph_len[x]++;
    }
    get_child(1);

    for (int i = 1; i <= n; i++)
        if (child[i] == 1) Q[Tail++] = i;

    for (int i = 1; i <= n; i++) pq_init(&pq[i], m + 5);

    for (int t = 0; t < m; t++) {
        for (int i = 1; i <= n; i++) {
            int pri, end;
            scanf("%lld %lld", &pri, &end);
            pq_insert(&pq[i], end + t, pri);
            while (pq[i].nodes[0].value < t) pq_delete(&pq[i]);
            child_done[i] = ttl[i] = 0;
        }
        int head = 0, tail = 0;
        for (int i = 0; i < Tail; i++) queue[tail++] = Q[i];
        int ans = 0;
        while (head != tail) {
            int i = queue[head++];

            ttl[i] += pq[i].nodes[0].priority;
            if (ttl[i] <= C) ans = max(ans, child[i]);

            ttl[inv[i]] += ttl[i];
            if (++child_done[inv[i]] == graph_len[inv[i]] && ttl[inv[i]] <= C) queue[tail++] = inv[i];
        }
        printf("%lld\n", ans);
    }
}
