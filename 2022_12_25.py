import pygame
import tkinter as tk

colors = [
    (0,0,0),  #白色
    (211,211,211), #dim gray
    (103,106,106) #light gray
]

class Figure:
    x = 0 #圖形的x座標
    y = 0 #圖形的y座標

    figures = [
        [[1, 5, 9], [4, 5, 6]],  #長方形方塊和他的旋轉方塊
        [[0,1,2,5,8,9,10],[0,2,4,5,6,8,10]] #I行方塊和他的選轉方塊
    ]

    def __init__(self, x, y, figure_type):  #初始化方塊的參數
        self.x = x
        self.y = y
        self.type = figure_type
        self.color = figure_type + 1
        self.rotation = 0

    def image(self):  #拿方塊
        return self.figures[self.type][self.rotation]

    def rotate(self): #旋轉方塊
        self.rotation = (self.rotation + 1) % len(self.figures[self.type])


class Tetris:
    
    state = "start"
    field = []
    height = 0
    width = 0
    x = 100
    y = 60
    zoom = 20
    figure = None
    figure_type = 0

    def __init__(self, height, width): #初始化存取方塊的list
        self.height = height
        self.width = width
        #宣告2維list
        for i in range(height):
            new_line = []
            for j in range(width):
                new_line.append(0) #一開始都初始化為0 代表沒有方塊
            self.field.append(new_line)

    def new_figure(self):  #宣告一個方塊
        self.figure = Figure(Width//2-1, 0, self.figure_type) #初始位置為最上層的中間

    def intersects(self):  #判斷正在下落的方塊有沒有碰到其他方塊
        intersection = False
        for i in range(4):
            for j in range(4):
                if i * 4 + j in self.figure.image():  
                    if i + self.figure.y > self.height - 1 or \
                            j + self.figure.x > self.width - 1 or \
                            j + self.figure.x < 0 or \
                            self.field[i + self.figure.y][j + self.figure.x] > 0: #檢查下落方塊的該位置有沒有和其他方塊碰撞
                        intersection = True
        return intersection #回傳偵測結果

    def go_space(self):  #直接移到最下層
        while not self.intersects(): #一直往下直到碰到其他方塊
            self.figure.y += 1
        self.figure.y -= 1
        self.freeze()

    def go_down(self):  #往下走一格
        self.figure.y += 1
        if self.intersects():
            self.figure.y -= 1
            self.freeze()

    def freeze(self): #走到最下面就不動了
        for i in range(4):
            for j in range(4):
                if i * 4 + j in self.figure.image():
                    self.field[i + self.figure.y][j + self.figure.x] = self.figure.color #把該方塊加到不會動的方塊中
        self.new_figure() #生成新方塊
        if self.intersects(): #檢查新生成的方塊有沒有和其他方塊碰撞
            game.state = "gameover" #有的話就遊戲結束了

    def go_side(self, dx): #往旁邊走一格
        old_x = self.figure.x #記錄初始方塊狀態
        self.figure.x += dx #移動
        if self.intersects(): #如果有碰到其他方塊就不移動
            self.figure.x = old_x

    def rotate(self): #旋轉一次
        old_rotation = self.figure.rotation #記錄初始方塊狀態
        self.figure.rotate() #旋轉方塊
        if self.intersects(): #如果有碰到其他方塊就不旋轉
            self.figure.rotation = old_rotation

Height=20
Width=20

#宣告gui
window = tk.Tk()
window.title('Tetris')
window.geometry('410x300')
window.resizable(False, False) 
window.config(bg="white")

def StartFunc():
    global Height,Width
    #設定使用者輸入進來的長跟寬
    Height=int(Height_Value.get())
    Width=int(Width_Value.get())
    window.destroy() #關閉gui

# 宣告gui上的物件
label = tk.Label(text="俄羅斯方塊遊戲",fg="black",bg="white",font=("Arial", 30, "bold"))
label.place(x=90,y=50)
Height_Label = tk.Label(text="高度:",fg="black",bg="white",font=("Arial", 20, "bold"))
Height_Label.place(x=90,y=150)
Height_Value = tk.Entry(width=5, font=("Arial", 15, "bold"), bg="white", fg="black")
Height_Value.place(x=140,y=150)
Weight_Label = tk.Label(text="寬度:",fg="black",bg="white",font=("Arial", 20, "bold"))
Weight_Label.place(x=200,y=150)
Width_Value = tk.Entry(width=5, font=("Arial", 15, "bold"), bg="white", fg="black")
Width_Value.place(x=250,y=150)
button = tk.Button(window, text = 'Start', command = StartFunc,width=20,height=2,borderwidth=0) 
button.place(x=100,y=220)

window.mainloop() #顯示gui

# 初始化遊戲引擎
pygame.init()

# 定義一些顏色
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (128, 128, 128)

size = (Width*20+200, Height*20+150)  #遊戲視窗的大小
screen = pygame.display.set_mode(size) #宣告遊戲式窗
pygame.display.set_caption("Tetris")  #設定式窗標題

#設定一些參數
finished = False
clock = pygame.time.Clock()
game = Tetris(Height, Width)
Time = 0
pressing_down = False
moveTime=0

while not finished:  #還沒結束就一直跑
    if game.figure is None: #如果沒有方塊就生成一個方塊
        game.new_figure() 

    Time += 1 #計算跑了幾次回圈
    if Time % (100) == 0 or (pressing_down and Time-moveTime>50): #到達下墜時間或按著下鍵
        if game.state == "start": #如果還在遊戲中
            game.go_down() #往下移動一格
            moveTime=Time #記錄移動時的時間

    for event in pygame.event.get(): #讀取鍵盤輸入
        if event.type == pygame.QUIT:  #按叉叉要退出遊戲
            finished = True
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:  #按上要選轉
                game.rotate()
            if event.key == pygame.K_DOWN: #按下要加速下墜
                pressing_down = True
            if event.key == pygame.K_LEFT: #按左要往左移動一格
                game.go_side(-1)
            if event.key == pygame.K_RIGHT: #按又要往右移動一格
                game.go_side(1)
            if event.key == pygame.K_SPACE: #按空白鍵要直接移動到底
                game.go_space()
            if event.key == pygame.K_q: #按q要退出遊戲
                finished=True
            if event.key == pygame.K_c: #按c要切換I行方塊跟長方形方塊
                game.figure_type = not game.figure_type
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_DOWN: #結束加速下墜
                pressing_down = False

    screen.fill(WHITE) #把螢幕填成白色

    #畫不會動的方塊
    for i in range(game.height):
        for j in range(game.width):
            pygame.draw.rect(screen, GRAY, [game.x + game.zoom * j, game.y + game.zoom * i, game.zoom, game.zoom], 1) #畫外誆
            if game.field[i][j] > 0: #如果該格子有方塊就畫方塊
                pygame.draw.rect(screen, colors[game.field[i][j]],[game.x + game.zoom * j + 1, game.y + game.zoom * i + 1, game.zoom - 2, game.zoom - 1]) #話方塊

    #畫正在下落的方塊
    for i in range(4):
        for j in range(4):
            p = i * 4 + j
            if p in game.figure.image(): #如果這格是圖形的組成方塊之一就畫在視窗上
                pygame.draw.rect(screen, colors[game.figure.color],
                                    [game.x + game.zoom * (j + game.figure.x) + 1,
                                    game.y + game.zoom * (i + game.figure.y) + 1,
                                    game.zoom - 2, game.zoom - 2]) #畫方塊

    
    if game.state == "gameover": #如果遊戲狀態是結束就要印出game over字樣
        font1 = pygame.font.SysFont('Calibri', (Width*20+200)//10, True, False) #設定pygame的字體
        text_game_over = font1.render("Game Over", True, (255, 0, 0)) #設定要印出的文字及顏色
        screen.blit(text_game_over, [(Width*20+200)//2-text_game_over.get_width()//2,(Height*20+150)//2-text_game_over.get_height()//2])  #把game over字樣畫到螢幕上

    pygame.display.flip()  #把上面要顯示的物件都更新到螢幕上

pygame.quit() #關閉視窗
