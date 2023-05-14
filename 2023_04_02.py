n, m = map(int, input().split(',', 2))  # 讀取n跟m

P = list(map(int, input().split(',', n)))  # 服務時間
R = list(map(int, input().split(',', n)))  # 預約時間
B = list(map(int, input().split(',', n)))  # 營收

order = [i for i in range(n)]  # 每個禮物的編號
# 氣泡排序法
for k in range(n):
    for i in range(n-k-1):
        # ---------判斷第i個和第i+1個的順序是否正確----------
        correct = False
        a, b = order[i], order[i+1]

        if P[a] != P[b]:  # 服務時間不同就用服務時間排序
            correct = P[a] < P[b]
        else:
            if R[a] != R[b]:  # 服務時間相同，預約時間不同就用預約時間排序
                correct = R[a] < R[b]
            else:  # 以上都相同則用編號排序
                correct = a < b
        # ----------------------------------
        if not correct:  # 如果順序不對就要交換
            order[i], order[i+1] = order[i+1], order[i]



isReserve = [[0 for _ in range(360)] for _ in range(m)] # 預約表，isReverse[j][t]=1代表按摩師j在時間t有預約，0則是沒有預約
Customer = 0  # 總共可服務幾個客人
Revenue = 0  # 總營收

for i in order:  # 依照剛排好的順序依序安排按摩師與服務的時間
    waitTime = 1e9  # 最短等待時間
    masseurID = -1  # 最短等待時間的按摩師

    for j in range(m):  # 遍歷每一個按摩師
        for t in range(R[i], R[i]+31):  # 客人只會等30分鐘
            if t+P[i] > 360:
                break
            if sum(isReserve[j][t:t+P[i]]) == 0:  # 檢查按摩師在時間t到t+P[i]是否有預約，=0代表都沒有預約
                if t-R[i] < waitTime:  # 如果這位按摩師能讓客人等更少的時間就安排給這位按摩師
                    waitTime = t-R[i]
                    masseurID = j
                    break

    if masseurID != -1:  # 有可用的按摩師
        StartServiceTime = R[i]+waitTime # 開始服務的時間是預約時間加上等待時間
        for t in range(StartServiceTime, StartServiceTime+P[i]): # 把該時段預約起來
            isReserve[masseurID][t] = 1

        Customer += 1 
        Revenue += B[i]
        

print(Customer, Revenue, sep=',')
