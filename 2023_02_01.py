import tkinter as tk

root = tk.Tk()
mycanvas = tk.Canvas(root, width=300, height=300)
mycanvas.pack()

color='white'
def change():
    global color
    for i in range(5):
        for j in range(5):
            mycanvas.create_rectangle(i*60, j*60, i*60+60, j*60+60, fill=color)
            if color=='white' :
                color='black'
            else :
                color='white'
    root.after(1000,change)
    
root.after(0,change)
root.mainloop()
