n = int(input()) #輸入n

N = n
Edge = [] # 存兩個有關係的節點
while True:
    edge = input()
    if edge == "STOP": #如果讀到STOP就停止
        break
    x, y = map(int, edge.split(','))
    Edge.append([x, y]) # 存入兩個有關係的節點
    if n == 0:  # 如果n是0要取最大值
        N = max(N, x+1)
        N = max(N, y+1)

if n != 0: # 判斷n不是0且超出範圍就要回傳None
    for i in Edge:
        if i[0] >= N or i[1] >= N:
            print("None")
            exit(0)

table = [[0 for _ in range(N)] for _ in range(N)] # 宣告一個二維的鄰接矩陣

for i in Edge: # 更新鄰接矩陣
    table[i[0]][i[1]] = 1
    table[i[1]][i[0]] = 1

# 輸出鄰接矩陣
for i in range(N):
    for j in range(N):
        print(table[i][j], end="")
        if j!=N-1:
            print(',',end="")
    print()
