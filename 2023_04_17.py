string = input()
string += '\n' # 在最後一個字元加上換行會比較好判斷段落

curNum=False # 判斷當前遍歷到的是不是數字
for i in range(len(string)): # 遍歷字串的每一個字元
    if string[i].isdigit() and not curNum: # 如果該字元為數字且當前不是在遍歷數字代表此為輸字開頭
        print("<<",end='') # 輸出左括號
        curNum=True
    elif not string[i].isdigit() and curNum and string[i]!='.' and string[i]!=',' and string[i]!='%': # 如果該字元不是數字且不是逗號或百分比代表結束了數字的遍歷
        print(">>",end='') # 輸出右括號
        curNum=False
    print(string[i],end='') # 輸出該字元
