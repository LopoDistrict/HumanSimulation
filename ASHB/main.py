import tkinter as tk
import json
import os
import csv
import random
from colorama import init, Fore, Back, Style
import os.path
import datetime
import time

#def settings():




def begin_param():
    init(autoreset = True)
    height = int(input('Height px: '))
    width  = int(input('Width px: '))
    print('loading...')
    time.sleep(1)
    print('loading parameters')
    time.sleep(1)
    print('tropical (hot), arid (hot+dry), oceanic (fresh), continental (cold + freezing)')
    climateCondition = input('Climate Condition: ')
    
    # tropical (hot), arid (hot+dry), oceanic (fresh), continental (cold + freezing)

    
    print('v0.0.6-ASHB Build test')
    print(Fore.GREEN + "loading into the simulation...")
    print(' ')
    print('Parameters')
    print('Map Height = ', height )
    print('Map Width = ', width)
    print('Climate = ', climateCondition)

    print(' ')


    file = ('./data/temp/presence.asb', './data/temp/tempSeparation.asb', './data/memory/char_mem.mem',
    './data/memory/couple.mem', './data/memory/temp.mem', './data/memory/gen.mem')

    cal_file = ('./calculation_software/cal.so', './calculation_software/rand.cpp',
     './calculation_software/calculation.cpp', './calculation_software/a.exe', './data/linked.cpp',
     './data/linked.py', './data/gen_tree.py', './data/gen_tree.cpp', './calculation.dll', './mesh.exe',
     './Data.py', './Data.cpp', './calculation_software/rand.h', './calculation_software/rand.h',
     './Data.h', './clock.cpp','./calculation_software/reinforcment_intelligence/model.h', './calculation_software/reinforcment_intelligence/model.cpp',
      './data/logs/logs.txt', './prog_clock.exe', ''
     )
    #assert type(height) == "<class 'int'>" and type(width) == "<class 'int'>", "Enter 2 int please."
    #besoin de
    print(' ')
    time.sleep(0.5)
    print(Fore.GREEN + 'loading files: ')
    try:        
        for i in file:
            time.sleep(0.08)
            print(i)
            open(i, 'w').close()

        for j in cal_file:
            time.sleep(0.08)
            os.path.exists(j)
            print(j)        
        print(Fore.GREEN + 'Good file integrity')
    
    except:
        print(Fore.RED + 'Error: bad file integrity')
        print(Fore.GREEN + 'Quitting simulation')


    file = open('./data/CharacterData.csv','w',  newline='')
    print('./data/CharacterData.csv')
    genFile = open('./data/temp/GenTempModule.asb', 'w', encoding='utf-8',  newline='')
    print('./data/temp/GenTempModule.asb')

    genFile.write(str(height) + "\n")
    genFile.write(str(width) + "\n")
    genFile.write(str(climateCondition) + "\n")

    char = open('./data/TempChar.csv','w',  newline='')
    print('./data/TempChar.csv')
    csvwriter, csvwriter2 = csv.writer(file), csv.writer(char)
    # writing the fields



    fields = ['id',"age", 'health', 'happiness', 'stress', 'mentalHealth', 'desire',
     'loneliness', 'boredom', 'anger', 'hygiene', 'sex', 'bday', 'couple']
    print('stats fields: ', fields)
    csvwriter.writerow(fields)
    csvwriter2.writerow(['id', 'xposition', 'yposition', 'gen'])
        
    file.close()
    genFile.close()
    char.close()    
    c = Simulation(width+25, height+25, 'black')
    c.mainloop()
    



class Simulation(tk.Tk):
    def __init__(self, height, width, color):
        super().__init__()
        self.title("DebugVersion0.0.7")
        self.resizable(False, False)
        
        self.day = 0
        self.time = 1 
        #0.5: slow, 1: normal, 2: fast, 4: fast_forward
        #8: ultra fast
        #gerer avec clock.py
        
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
        try:
            self.canvas.create_oval(posx, posy, posx+10, posy+10, fill="white", outline="red")
            print("[", Fore.GREEN + "+","] ", "Character artifiaclly created sucessfully")
            write_logs(f"GUI created char: {posx, posy, posx+10, posy+10}")
        
        except:
            print(Fore.RED + 'Error', ': Artificial char. creation failed')
    
    def randmId(self):
        letters = "abcdefghijklmnopqrstuvwxyz"
        num = "0123456789"
        id = ""
        for i in range(8): 
            if i in [0, 6, 7]:
                id += num[random.randint(0, 9)]
            else:
                id += letters[random.randint(0, 25)]
        return id



    def movement(self):
        #pour l'instant je n'ai pas de solution viable 
        #pour faire en sorte de bouger toute les entités
        #donc nous sommes obligés de tous les enlever et lrécupérer le fichier modifié
        #pour les replacés
        self.canvas.delete('all') 
        self.create_grid()
        try:
            with open("data/TempChar.csv", "r") as file:
                file_get_pos = csv.reader(file)
                next(file_get_pos)
                for line in file_get_pos:
                    self.create_new_character(int(line[1])+10, int(line[2])+10)
            print("[", Fore.GREEN + "+","]",'all entity was moved sucessfully')
        except Exception as e:
            print('there was an error in moving all the entities')
            print(Fore.RED + 'Error: ', e)


    def CreateCharStasts(self, id, values=None):
        #values est une liste
        s = ['M', 'F']
        stats = {'age': 0, 'health': 150, 'happiness': 80, 'stress': 12, 
        'mentalHealth':100, 'desire':0, 'loneliness': 7, 'boredom': 25, 'anger':10, 'hygiene':100, 
        'sex': s[random.randint(0,1)], 'bday': self.day, 'couple': 'no'}
        model = open('./data/memory/model/'+id+'.dmem', 'w')
        print('./data/memory/model/'+id+'.dmem')
        model.write('id=' + id + "\n")
        model.write('disease=null' + "\n")
        model.write('mvt=1' + "\n")
        model.write('ir_target=hap++' + '\n')
        model.write('mem_actions=null' + '\n')
        #si il ya diff val dans une ligne on les sépare par _
         
        model.close()

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
        print("[", Fore.GREEN + "+","] ","New character has been added")
        write_logs(f"new character added {id}")
        print(' ')


    def write_logs(self, val):
        with open('./data/logs/logs.txt') as logsFile:
            logsFile.write(f"<{datetime.datetime.now()}> {value}")
    
    def CreateTempPosition(self, id, x, y, gen):
        with open('./data/TempChar.csv', 'a', newline='') as fileTemp:
            csvwriter = csv.writer(fileTemp)
            csvwriter.writerow([id, x, y, gen])
        


    def time(self):
        self.day += self.time


    def get_info_Id(self, id):
        csv_file = csv.reader(open('./data/CharacterData.csv', "r"), delimiter=",")
        for row in csv_file:
        #if current rows 2nd value is equal to input, print that row
            if id == row[0]:
                print(row)
        
        

    def get_all_Info(self):
        csv_file = csv.reader(open('./data/CharacterData.csv', "r"), delimiter=",")
        entity = 0
        print('./data/CharacterData.csv')
        for row in csv_file:
            print(row)
            entity+=1

        print( )
        print('Parameters:')
        print(f"Entity(Character)={entity}")
        files = ['./data/temp/presence.asb', './data/temp/presence.asb'] 
        for i in range(len(files)):
            with open(files[i]) as file:
                for line in file:
                    print(line.rstrip())
    

        

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
                    print(Fore.RED + "Error",": Out of Bounds -> x in ", (0, self.canvas.winfo_width()), "y in", (0, self.canvas.winfo_height()))
                else:
                    self.create_new_character(x, y)
                    id = self.randmId()
                    self.CreateTempPosition(id, x, y, 'x')
                    self.CreateCharStasts(id)

            
            elif command == 'd' or command == 'data':
                type = input('type of data (referer help data): ')
                if type == 'all' or type == 'a':
                    self.get_all_Info()

                if type == 'id' :
                    id = input('enter character id: ')
                    self.get_info_Id(id)

            elif command == 'mvt' : #debug
                self.movement()

                
            elif command == "exit":
                confirmation = input("Are you sure you want to quit (nothing will be saved) (Y/N): ")
                if confirmation == "Y" or confirmation == "y":
                    os.system('exit')
                pass
            
            else:
                print(Fore.RED + "Error:", "Wrong command, please refer to help for command")
    


if __name__ == "__main__":
    os.system('cls')    
    print('@Author: Komodo')
    time.sleep(0.2)
    print('Artificial Simulation')
    time.sleep(0.2)
    print('client version: 0.0.7')
    time.sleep(0.2)
    print('https://github.com/LopoDistrict/HumanSimulation')
    begin_param()
