from tkinter import ttk
import tkinter as tk, time

root = tk.Tk()

pb = ttk.Progressbar(root, orient="horizontal", length=200, mode="determinate")
pb.pack(pady=20)

def bar():
    pb['value'] = 0
    for i in range(101):
        pb['value'] = i
        root.update_idletasks()
        time.sleep(0.01)

tk.Button(root, text="Start", command=bar).pack()

root.mainloop()