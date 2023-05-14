n, m = map(int, input().split(',', 2))

t = [0]*m
need = [0]*n
order = [i for i in range(n)]

def correct(a, b):
    if need[a] != need[b]:
        return need[a] < need[b]

    for i in range(m):
        if t[i][a] != t[i][b]:
            return t[i][a] < t[i][b]

    return a < b


for i in range(m):
    t[i] = list(map(int, input().split(',', n)))

need = [0]*n
for i in range(m):
    for j in range(n):
        need[j] += t[i][j]

for i in range(n):
    for j in range(i+1, n):
        if not correct(order[i], order[j]):
            order[i], order[j] = order[j], order[i]

ans = [0]*n
lastFinish = [0]*m
idle = 0

for i in order:
    curT = 0
    for j in range(m):
        curT = max(curT, lastFinish[j])
        idle += curT-lastFinish[j]
        curT += t[j][i]
        lastFinish[j] = curT
        ans[i] = max(ans[i], curT)

for i in ans:
    print(i, end=',')

print(idle)
