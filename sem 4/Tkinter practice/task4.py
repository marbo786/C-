import tkinter as tk

def draw():
    c.create_rectangle(10, 10, 90, 90, fill="red")
    c.create_oval(110, 10, 190, 90, fill="blue")
    c.create_line(10, 110, 190, 110, fill="green", width=5)

root = tk.Tk()
c = tk.Canvas(root, width=200, height=120, bg="white")
c.pack()

btn = tk.Button(root, text="Draw", command=draw)
btn.pack()

root.mainloop()