import tkinter as tk
import json
import os
import csv
import random

def begin_param():
    height = 400 #int(input('Height px (int): '))
    width = 400 #int(input('Width px (int): '))
    print("loading into the simulation")
    #assert type(height) == "<class 'int'>" and type(width) == "<class 'int'>", "Enter 2 int please."
    #besoin de

    file = open('./data/CharacterData.csv','w',  newline='')
    char = open('./data/TempChar.csv','w',  newline='')
    csvwriter, csvwriter2 = csv.writer(file), csv.writer(char)
    # writing the fields
    fields = ['id',"age", 'genealogy', 'health', 'happiness', 'stress', 'mentalHealth', 'desire',
     'loneliness', 'boredom', 'anger', 'hygiene']
    csvwriter.writerow(fields)
    csvwriter2.writerow(['id', 'xposition', 'yposition'])
        
    file.close()
    char.close()    
    

    c = Simulation(width, height, 'white')
    c.mainloop()




class Simulation(tk.Tk):
    def __init__(self, height, width, color):
        super().__init__()
        self.title("DebugVersion0.0.1")
        self.resizable(False, False)
        
        # Create a canvas widget
        self.canvas = tk.Canvas(self, height=height, width=width, bg=color)
        self.canvas.pack(fill=tk.BOTH, expand=True)
        
        # Bind the configure event to the create_grid method
        self.bind('<Configure>', self.create_grid)
        self.edit()
        
        # Example of creating a new character (rectangle)
        #self.bind('<Button-1>', self.create_new_character(40, 40))
        #self.bind('<Button-1>', self.create_new_character(60, 40))
        #self.bind('<Button-1>', self.create_new_character(40, 60))


    def create_new_character(self,posx, posy, event=None):
        self.canvas.create_oval(posx, posy, posx+15, posy+15, fill="black", outline="red")
        print("Character artifiaclly created")
    
    
    def randmId(self):
        letters = "abcdefghijklmnopqrstuvwxyz"
        num = "0123456789"
        id = ""
        for i in range(8): 
            if i in [0, 6, 7]:
                id += num[random.randint(0, 9)]
            id += letters[random.randint(0, 25)]
        return id

    
    def CreateCharStasts(self, id, values=None):
        #values est une liste
        stats = {'age': 0, 'genealogy': "X", 'health': 150, 'happiness': 80, 'stress': 12, 
        'mentalHealth':100, 'desire':0, 'loneliness': 7, 'boredom': 25, 'anger':10, 'hygiene':100}
        with open('./data/CharacterData.csv', "a", newline='') as file:
            newVal = [id]
            print('Creating a new character, id: ', newVal)            
            for kay, val in stats.items():
                try:
                    newVal.append(values[i])
                except:
                    newVal.append(val)
            
            print(newVal)
            csvwriter = csv.writer(file)     
        
            csvwriter.writerow(newVal)
        print("a New character has been added")



    
    def CreateTempPosition(self, id, x, y):
        with open('./data/TempChar.csv', 'a', newline='') as fileTemp:
            csvwriter = csv.writer(fileTemp)
            csvwriter.writerow([id, x, y])
        



    def get_info_Id(self, id):
        csv_file = csv.reader(open('./data/CharacterData.csv', "r"), delimiter=",")
        for row in csv_file:
        #if current rows 2nd value is equal to input, print that row
            if id == row[0]:
                print(row)
        

    def get_all_Info(self):
        csv_file = csv.reader(open('./data/CharacterData.csv', "r"), delimiter=",")
        for row in csv_file:
            print(row)
    

        

    def create_grid(self, event=None):
        w = self.canvas.winfo_width()  # Get current width of canvas
        h = self.canvas.winfo_height()  # Get current height of canvas
        self.canvas.delete('grid_line')  # Will only remove the grid_line
        
        # Creates all vertical lines at intervals of 20
        for i in range(0, w, 20):
            self.canvas.create_line([(i, 0), (i, h)], tag='grid_line', fill="grey")
        
        # Creates all horizontal lines at intervals of 20
        for i in range(0, h, 20):
            self.canvas.create_line([(0, i), (w, i)], tag='grid_line', fill="grey")
    

    def delete_grid(self, event=None):
        self.canvas.delete('grid_line')  # Will only remove the grid_line
    


    def edit(self):
        while 1:
            command = input('>')
            if command == 'nc' or command == "newcharacter":
                #creation d'un nouveau char artificiellement
                x = int(input ("X position(px: int): "))
                y = int(input ("Y position(px: int): "))
                if x < 0 or x > self.canvas.winfo_width() or y < 0 or y > self.canvas.winfo_height():
                    print("Error: Out of Bounds -> x", (0, self.canvas.winfo_width()), " y", (0, self.canvas.winfo_height()))
                else:
                    self.create_new_character(x, y)
                    id = self.randmId()
                    self.CreateTempPosition(id, x, y)
                    self.CreateCharStasts(id)
            
            elif command == 'd' or command == 'data':
                type = input('type of data (referer help data): ')
                if type == 'all' or type == 'a':
                    self.get_all_Info()
                if type == 'id' :
                    id = input('enter character id: ')
                    self.get_info_Id(id)
                
            elif command == "exit":
                confirmation = input("Are you sure you want to quit (nothing will be saved) (Y/N): ")
                if confirmation == "Y" or confirmation == "y":
                    os.system('exit')
                pass
            
            else:
                print("print wrong command, please refer to help for command")
    


if __name__ == "__main__":
    begin_param()
