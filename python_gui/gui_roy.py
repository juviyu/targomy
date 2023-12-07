import tkinter as tk
import customtkinter as ctk
import socket
from threading import Thread
from time import sleep
import select

HOST = "100.22.13.59"
PORT = 1234

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
while True:
    try:
        client_socket.settimeout(5)
        client_socket.connect((HOST, PORT))
        break
    except:
        print("Connection Failed to ", HOST)
        sleep(1)
sleep(1)
print(f"Connection to :{HOST} has Been succesful!")




ctk.set_appearance_mode("Dark")
appWidth, appHeight = 300, 400

class App(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("Mashmet")
        self.geometry(f"{appWidth}x{appHeight}")
        self.state('zoomed')
        self.title('Super Yuda')
        # self.grid_columnconfigure(0, weight=1)
        # self.grid_rowconfigure((0, 1), weight=1)
        self.button = ctk.CTkButton(self, text="Move Actuators Out",
                                     command=lambda: self.moveActuators("3"))
        self.button.grid(row=1, column=0, padx=10, pady=10, sticky="ew")

        self.button = ctk.CTkButton(self, text="Move Actuators In",
                                     command=lambda: self.moveActuators("2"))
        self.button.grid(row=1, column=1, padx=10, pady=10, sticky="ew")

        self.actuator1Label = ctk.CTkLabel(self, text="Actuator 1 Position: ") # TODO: finish
        Thread(target=self.listener,daemon=True).start()


    def listener(self):
        while True:
            try:
                data = client_socket.recv(1024)
                self.parseString(data.decode())
            except:
                print("Data Recieve Failed")

    def parseString(self, data):
        data.split(' ')
        print(data)
        
    def moveActuators(self, message):
        print("Sending to Teensy: ", message)
        client_socket.sendall(message.encode())
        sleep(0.1)
        # data = client_socket.recv(1024)
        # self.parseString(data.decode())
        # print("Recv unsucceful")




    
app = App()
app.mainloop()
client_socket.close()

