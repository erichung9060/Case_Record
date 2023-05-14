class Card: # 定義Class
    def __init__(self,suit, rank):
        self.suit=suit
        self.rank=rank


Suit=input().split(',') # 輸入花色
Rank=input().split(',') # 輸入點數

cards=[0]*5
for i in range(5):
    cards[i]=Card(Suit[i],Rank[i]) # 把花色與點數包成Crad放入cards

ans=0
# rule A
for i in range(5):
    if cards[i].rank=='A': # 打出一張A得5分
        ans+=5

# rule B
for i in range(5):
    for j in range(i+1, 5):
        if cards[i].rank == cards[j].rank: # 打出一對得10分
            ans+=10

# rule C
same_suit = True
for i in range(1,5):
    if cards[i-1].suit!=cards[i].suit: # 判斷有沒有同花色
        same_suit = False
if same_suit: # 打出同花得30分
    ans+=30

# rule D
sorted_rank=[0]*5 
for i in range(5):
    if cards[i].rank == 'A': 
        sorted_rank[i]= 1
    elif cards[i].rank == 'J':
        sorted_rank[i]= 11
    elif cards[i].rank == 'Q':
        sorted_rank[i]= 12
    elif cards[i].rank == 'K':
        sorted_rank[i]= 13
    else:
        sorted_rank[i]=int(cards[i].rank)

sorted_rank.sort() # 把所有點數排序
not_consecutive = 0
for i in range(1,5):
    if sorted_rank[i-1]+1 != sorted_rank[i]: # 判斷有沒有連續
        not_consecutive+=1

# 如果都連續或者有兩張不連續但第一張是1且最後一張是K
if not_consecutive==0 or (not_consecutive==1 and sorted_rank[0]==1 and sorted_rank[4]==13):
    ans+=50 # 打出順子得50分

# rule E
if (sorted_rank[0]==sorted_rank[2] and sorted_rank[3]==sorted_rank[4] and sorted_rank[0]!=sorted_rank[4]) or \
   (sorted_rank[0]==sorted_rank[1] and sorted_rank[2]==sorted_rank[4] and sorted_rank[0]!=sorted_rank[4]):
    ans+=80 # 打出葫蘆得80分

# rule F
if sorted_rank[0]==sorted_rank[4]: # 如果5張的點數都一樣
    ans+=100*5 # C5取4
elif sorted_rank[0]==sorted_rank[3] or sorted_rank[1]==sorted_rank[4]:
    ans+=100 # 打四條得100分

# rule G
if same_suit: # 如果桐花
    if not_consecutive==0 or (not_consecutive==1 and sorted_rank[0]==1 and sorted_rank[4]==13): # 且是順子
        ans+=300 # 打出同花順得300分

print(ans) # 印出總分
