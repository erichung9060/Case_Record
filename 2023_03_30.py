n = int(input())
m = 2 

t = [0]*m
for i in range(m):
    t[i] = list(map(int, input().split(',', n)))  # 讀取每一條生產線生產禮物的時間


order = [i for i in range(n)]  # 每個禮物的編號
# 氣泡排序法
for k in range(n):
    for i in range(n-k-1):
        # ---------判斷第i個和第i+1個的順序是否正確----------
        correct = False
        a, b = order[i], order[i+1]

        if t[0][a]+t[1][a] != t[0][b]+t[1][b]:  # 用總時間排序
            correct = t[0][a]+t[1][a] < t[0][b]+t[1][b]

        elif t[0][a] != t[0][b]:  # 用組裝時間排序
            correct = t[0][a] < t[0][b]
        else: # 用id排序
            correct = a < b
        # ----------------------------------

        if not correct:  # 如果順序不對就要交換
            order[i], order[i+1] = order[i+1], order[i]

ans = [0]*n  # 儲存每一個禮物製作完的時間
lastFinish = [0]*m  # 記錄每一條生產線最快能用的時間
idle = 0  # 記錄總閒置時間

for i in order:  # 依照我們剛排好的順序依序製作禮物
    curT = 0  # 當前的時間
    for j in range(m):  # 遍歷每一條生產線
        
        curT = max(curT, lastFinish[j]) # 當前的時間要和該生產線最快能用的時間取max，要等前一個做完後才能接著換我做
        idle += curT-lastFinish[j] # 閒置時間要加上當前的時間剪掉該生產線快能用的時間(生產線快能用的時間=前一個任務做完的時間)
        curT += t[j][i]  # 製作禮物，時間要加上當前生產線做作禮物的時間
        lastFinish[j] = curT  # 更新這條生產線最快能用的時間
        ans[i] = curT  # 更新當前禮物的製作時間

# 輸出答案
for i in ans:
    print(i, end=',')
print(idle)
