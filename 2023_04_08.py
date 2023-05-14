n = int(input())

N = n
Edge = []
while True:
    edge = input()
    if edge == "STOP":
        break
    x, y = map(int, edge.split(','))
    Edge.append([x, y])
    if n == 0:
        N = max(N, x+1)
        N = max(N, y+1)

if n != 0:
    for i in Edge:
        if i[0] >= N or i[1] >= N:
            print("None")
            exit(0)
k=0
if k >= N:
    print("None")
    exit(0)

table = [[0 for _ in range(N)] for _ in range(N)]

for i in Edge:
    table[i[0]][i[1]] = 1
    table[i[1]][i[0]] = 1

for i in range(N):
    for j in range(N):
        print(table[i][j], end="")
        if j!=N-1:
            print(',',end="")
    print()
