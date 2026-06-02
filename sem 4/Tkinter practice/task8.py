import tkinter as tk

root = tk.Tk()
root.title("Calculator")

entry = tk.Entry(root, width=35, borderwidth=5, font=("Arial", 18))
entry.grid(row=0, column=0, columnspan=4, padx=10, pady=10)

def button_click(number):
    current = entry.get()
    entry.delete(0, tk.END)
    entry.insert(0, str(current) + str(number))

def button_equal():
    try:
        result = eval(entry.get())
        entry.delete(0, tk.END)
        entry.insert(0, result)
    except:
        entry.delete(0, tk.END)
        entry.insert(0, "Error")

buttons = ['7','8','9','/', '4','5','6','*',
           '1','2','3','-', 'C','0','=','+']

r, c = 1, 0
for txt in buttons:
    cmd = lambda t=txt: button_equal() if t=='=' else (entry.delete(0, tk.END) if t=='C' else button_click(t))
    tk.Button(root, text=txt, padx=40, pady=20, command=cmd).grid(row=r, column=c)
    c += 1
    if c > 3: c, r = 0, r+1

root.mainloop()