n, m = map(int, input().split(',', 2))  # 讀取n跟m

t = [0]*m
for i in range(m):
    t[i] = list(map(int, input().split(',', n)))  # 讀取每一條生產線生產禮物的時間

# 計算生產禮物的總時間
need = [0]*n
for j in range(n):
    for i in range(m):
        need[j] += t[i][j]  # 計算第j個禮物生產的時間

order = [i for i in range(n)]  # 每個禮物的編號
# 氣泡排序法
for k in range(n):
    for i in range(n-k-1):
        # ---------判斷第i個和第i+1個的順序是否正確----------
        correct = False
        a, b = order[i], order[i+1]

        if need[a] != need[b]:  # 總時間不一樣就優先用總時間排序
            correct = need[a] < need[b]
            # 記錄用總時間比較的順序，左邊的總時間小於右邊的總時間 correct會等於true，代表此順序是對的
        else:  # 否則就要比較生產線上的時間
            done = False
            for j in range(m):
                if t[j][a] != t[j][b]:  # 找到第一個不一樣的時間
                    correct = t[j][a] < t[j][b]  # 記錄用生產線上的時間比較的順序
                    done = True  # 紀錄已找到第一個生產線上不一樣的時間

                if done:  # 如果找到了就不用繼續往下比
                    break

            if not done:  # 如果都沒有找到代表生產線上的時間都一樣，那就要用編號去比
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
