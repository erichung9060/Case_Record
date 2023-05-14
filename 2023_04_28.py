path=input()
f=open(path,'r') #字典路徑

CNS={}
CHAR={}
total=set()

for line in f:
    if line in total: #重複了就略過
        continue

    total.add(line) # 加到total這個set中

    a,b=line.split()
    b=chr(int('0x'+b,16)) # 轉成國字

    if a in CNS: # 如果已經被匹配過了就違法
        print("MAPPING_TABLE_ERROR")
        exit(0)
    else:
        CNS[a]=b # 匹配

    if b in CHAR: # 如果有匹配過
        CHAR[b].add(a) # 就直接加進去set
    else: 
        sa={a} # 否則宣告一個set
        CHAR[b]=sa # 再把set拿去匹配
        

line=input()
Type, Target=line.split(':')

print(len(total)) # 輸出總共有幾個匹配
if(Type=="CNS"):
    if Target in CNS: # 查詢得到資料
        print(CNS[Target])
    else: # 查詢不到資料
        print("NO_DATA_FOUND")
else:
    if Target in CHAR: # 查詢的到資料 
        for i in sorted(CHAR[Target]): # 排序
            print(i)
    else: # 查詢不到資料
        print("NO_DATA_FOUND")
