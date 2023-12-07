import tkinter as tk
import customtkinter

class App(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        self.title("my app")
        self.geometry("400x180")
        #self.state('zoomed')
        #self.title('Super Yuda')
        self.grid_columnconfigure(0, weight=1)
        self.grid_rowconfigure((0, 1), weight=1)

        self.button = customtkinter.CTkButton(self, text="my button")
        self.button.grid(row=3, column=0, padx=10, pady=10, sticky="ew")

    
app = App()
app.mainloop()