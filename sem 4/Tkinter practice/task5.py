import tkinter as tk

root = tk.Tk()

selected = tk.StringVar()
selected.set("A")

def update():
    lbl.config(text=f"Selected: {selected.get()}")

r1 = tk.Radiobutton(root, text="Option A", variable=selected, value="A", command=update)
r2 = tk.Radiobutton(root, text="Option B", variable=selected, value="B", command=update)
r3 = tk.Radiobutton(root, text="Option C", variable=selected, value="C", command=update)
r1.pack(); r2.pack(); r3.pack()

lbl = tk.Label(root, text="Selected: A")
lbl.pack()

root.mainloop()