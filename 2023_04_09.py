
def find_closet(adj_mat, k):
    Cnt = 0
    neighbor = 0

    for i in range(N):
        if i == k: # 如果要找的節點是主要節點就continue
            continue
        cnt = 0
        for j in range(N): # 枚舉鄰居節點
            if adj_mat[k][j] and adj_mat[j][i]: # 如果是鄰居就把鄰居數+1
                cnt += 1
        
        if cnt > Cnt: # 如果鄰居數比當前最大的鄰居數大就更新此節點
            Cnt = cnt
            neighbor = i

    return neighbor, Cnt # 回傳最接近的節點編號以及節點數量


n = int(input())  # 輸入n
k = int(input())  # 輸入k

N = n
Edge = []  # 存兩個有關係的節點
while True:
    edge = input()
    if edge == "STOP":  # 如果讀到STOP就停止
        break
    x, y = map(int, edge.split(','))
    Edge.append([x, y])  # 存入兩個有關係的節點
    if n == 0:  # 如果n是0要取最大值
        N = max(N, x+1)
        N = max(N, y+1)

if n != 0:  # 判斷n不是0且超出範圍就要回傳None
    for i in Edge:
        if i[0] >= N or i[1] >= N:
            print("None")
            exit(0)

if k >= N:  # 如果主角節點超出範圍就輸出None
    print("None")
    exit(0)

adj_mat = [[0 for _ in range(N)] for _ in range(N)]  # 宣告一個二維的鄰接矩陣

for i in Edge:  # 更新鄰接矩陣
    adj_mat[i[0]][i[1]] = 1
    adj_mat[i[1]][i[0]] = 1

neighbor, Cnt = find_closet(adj_mat, k)

# 輸出結果
print(neighbor)
print(Cnt)
