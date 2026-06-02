import tkinter as tk

def on_click():
    lbl.config(text="Clicked!")

root = tk.Tk()

lbl = tk.Label(root, text="Waiting...")
lbl.pack()

btn = tk.Button(
    root,
    text="Click Me",
    command=on_click,  # No parentheses!
    bg="#4CAF50",
    fg="white"
)
btn.pack()

root.mainloop()