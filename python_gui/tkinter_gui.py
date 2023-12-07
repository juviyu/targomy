import tkinter as tk
import customtkinter



window = tk.Tk()
window.state('zoomed')
window.title('Super Yuda')

#customtkinter.set_appearance_mode("dark")
#customtkinter.set_default_color_theme("dark-blue")  

#label1 = tk.Label(master=window, text="Targonel", foreground="white", background="#34A2FE", width=10, height=2)
#def createLabel(label1:tk.Tk(),x:int,y:int):
#text = tk.Label(master=window, text=text1, foreground="white", background="#34A2FE", width=10, height=2) 
#label1.config(font=("Ariel", 10, "bold"))
#label1.place(x, y)




#label1 = tk.Label() 
#a function that gets a placement and creates a button
#def createLabel(text1:str,x:int,y:int):
#text = tk.Label(master=window, text=text1, foreground="white", background="#34A2FE", width=10, height=2) 
#text.config(font=("Ariel", 10, "bold"))
#text.place(x, y)


#createLabel("aa",0,200)
#a function that gets a placement and creates a label


#a function that gets a placement and creates an indication

#label3 = tk.Label(master=window, text="aaaaa", bg="red")




#effects
border_effects = {
   "raised": tk.RAISED,
   "open": tk.RAISED
}

for relief_name, relief in border_effects.items():
    frame = tk.Frame(master=window, relief=relief, borderwidth=5)
    frame.pack(side=tk.LEFT)
    label = tk.Label(master=frame, text=relief_name)
    label.pack()



#Targonel
label = tk.Label(master=window, text="Targonel", foreground="white", background="#34A2FE", width=10, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=0, y=0)

#bochnot-targonel
label = tk.Label(text="Bochnaot", foreground="white", background="#34A2FE", width=10, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=0, y=100)

button = tk.Button(text="Open", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=100, y=100)

button = tk.Button(text="close", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=200, y=100)

#bohnot indication
label = tk.Label(text="Bochna1 indication- ", foreground="white", background="#34A2FE", width=20, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=0, y=170)

label = tk.Label(text="Bochna2 indication- ", foreground="white", background="#34A2FE", width=20, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=0, y=230)

#servo-targonel
label = tk.Label(text="servo", foreground="white", background="#34A2FE", width=10, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=0, y=290)

button = tk.Button(text="Open", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=100, y=290)

button = tk.Button(text="close", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=200, y=290)

#Hasama
label = tk.Label(text="Hasama", foreground="white", background="#34A2FE", width=10, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=750, y=0)

#bochna1
label = tk.Label(text="Bochna1", foreground="white", background="#34A2FE", width=10, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=750, y=100)

button = tk.Button(text="Open", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=900, y=100)

button = tk.Button(text="close", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=1000, y=100)

label = tk.Label(text="Bochna1 indication- ", foreground="white", background="#34A2FE", width=20, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=1150, y=100)

#indication_frame = tk.Frame(window)
#indication_frame.pack(pady=15, padx=10, fill="x")
#tk.Label(indication_frame, text="Name").pack(side="left", padx=5)
#tk.Entry(indication_frame).pack(side="left", fill="x", expand=True, padx=5)

#bochna2
label = tk.Label(text="Bochna2", foreground="white", background="#34A2FE", width=10, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=750, y=150)

button = tk.Button(text="Open", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=900, y=150)

button = tk.Button(text="close", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=1000, y=150)

label = tk.Label(text="Bochna2 indication- ", foreground="white", background="#34A2FE", width=20, height=2) 
label.config(font=("Ariel", 10, "bold"))
label.place(x=1150, y=150)


#button = customtkinter.CTkBUtton
button = tk.Button(text="close", width=10, height=2, bg="blue", fg="yellow")
button.config(font=("Ariel", 10, "bold"))
button.place(x=1000, y=150)




window.mainloop()
