import tkinter as tk
import math

vertical_spacing = 80
horizontal_spacing = 80

top = 50
down = top+2*vertical_spacing
left = 100
right = left+6*horizontal_spacing

root = tk.Tk()
mycanvas = tk.Canvas(root, width=650, height=300, bg="white")
mycanvas.pack()

def init():
    mycanvas.delete("all")
    for i in range(3):  # horizontal line
        mycanvas.create_line(left, top+i*vertical_spacing, right,
                            top+i*vertical_spacing, fill="black")

    for i in range(7):  # vertical line
        mycanvas.create_line(left+i*horizontal_spacing, top,
                            left+i*horizontal_spacing, down, fill="black")


    for i in range(3):
        mycanvas.create_text(left-30, top+i*vertical_spacing,
                            text=1-i, fill='black', font=('Arial', 18))

    cnt = 0
    for i in range(7):
        mycanvas.create_text(left+i*horizontal_spacing, down+30,
                            text=i, fill='black', font=('Arial', 18))
        cnt += 1

    mycanvas.create_text(30, 130, text='f(n)', fill='black', font=('Arial', 22))
    mycanvas.create_text(340, 280, text='n', fill='black', font=('Arial', 22))

T = 0
f = 0.1


def gety(x):
    y = math.cos(f*x+T)
    return int(top+vertical_spacing+y*vertical_spacing)

def change():
    init()
    global T
    for i in range(left, right, 1):
        y1 = gety(i)
        y2 = gety(i+1)
        mycanvas.create_line(i, y1, i+1, y2, fill="blue")

    T += 1
    root.after(100, change)


root.after(0, change)
root.mainloop()
