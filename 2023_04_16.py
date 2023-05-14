# 所有的標點符號
sepChar = "。，、；：「」『』（）─？！─…﹏《》〈〉．～　,.; !\"#$%&'()*+,-./:;<=>?@[\]^_`{¦}~\n"

string = input()
string += '\n' # 在最後一個字元加上換行會比較好判斷段落

# 找標點符號在字串中的索引號
sepIdx = [-1]
for i in range(len(string)): # 遍歷字串
    isSep = False
    for j in range(len(sepChar)): # 遍歷所有標點符號
        if string[i] == sepChar[j]: # 如果該字元是標點符號
            isSep = True # 把isSep設成True
            break

    if isSep:
        sepIdx.append(i) # 如果是標點符號就把索引號加進sepIdx

for i in range(1, len(sepIdx)): # 遍歷所有標點符號
    l = sepIdx[i-1]+1 # 文字片段的左邊界
    r = sepIdx[i]-1 # 文字片段的右邊界
    if l <= r:
        substring = string[l:r+1] # 文字片段就是標點符號和標點符號之間的字串
        if '大' in substring or '蛇' in substring or '丸' in substring: # 如果'大' '蛇' '丸'有出現在文字片段中
            print('!'.join(list(substring)), end='') # 輸出中間插入驚嘆號的字串
        else:
            print(substring, end='') # 輸出原本的字串

    print(string[sepIdx[i]], end='') # 輸出該標點符號
