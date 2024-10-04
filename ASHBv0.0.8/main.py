import tkinter as tk
import json
import os
import csv
import random
from colorama import init, Fore, Back, Style
import os.path
import datetime
import time
from subprocess import Popen, CREATE_NEW_CONSOLE
from data_ui_manager import *
#from sync_clock import *
import shutil
import threading
from multiprocessing import Process


#tout est un bon sauf que le mouvement ne s'update pas sur le GUI a corrigé



def begin_param():
    init(autoreset = True)
    height = int(input('Height px: '))
    width  = int(input('Width px: '))
    print('loading...')
    time.sleep(1)
    print('loading parameters')
    time.sleep(1)

    print('tropical (hot), arid (hot+dry), oceanic (fresh), continental (cold + freezing)')

    climateCondition = input('Climate Condition : ')

    while climateCondition not in ['tropical', 'arid', 'oceanic', 'continental']:
        print('tropical (hot), arid (hot+dry), oceanic (fresh), continental (cold + freezing)')
        climateCondition = input('Climate Condition (respect the proposition): ')
    
    # tropical (hot), arid (hot+dry), oceanic (fresh), continental (cold + freezing)

    
    print('v0.0.8-ASHB Build test')
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
    genFile.write("0" + "\n")#days

    char = open('./data/TempChar.csv','w',  newline='')
    print('./data/TempChar.csv')
    csvwriter, csvwriter2 = csv.writer(file), csv.writer(char)
    # writing the fields



    fields = ['id',"age", 'health', 'happiness', 'stress', 'mentalHealth', 'desire',
     'loneliness', 'boredom', 'anger', 'hygiene', 'sex', 'bday', 'couple']
    print('stats fields: ', fields)    
    csvwriter.writerow(fields)
    csvwriter2.writerow(['id', 'xposition', 'yposition', 'gen'])
    print("calculating the mesh")
    time.sleep(0.2)
    print("[", Fore.GREEN + "+","] ","time clock setting choosed") 
    print("day = tick = constant number")
    
    #try: 
    #    result = subprocess.run(["./collision_deb.exe"]) 
    #    print("Output:", result.stdout)  # Print standard output 
    #    print("Errors:", result.stderr)    # Print standard error (if any) 
    #    print("calculation finished sucessfully")
    #except subprocess.CalledProcessError as e: 
    #    print("An error occurred while running the .exe file.") 
    #    print("Return Code:", e.returncode) 
    #    print("Output:", e.output) 
    #    print("Error Output:", e.stderr)

    print("removing old model files")

    #Mark Amery code -> delete content from folder
    folder = './data/memory/model'
    for filename in os.listdir(folder):
        file_path = os.path.join(folder, filename)
        try:
            if os.path.isfile(file_path) or os.path.islink(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path):
                shutil.rmtree(file_path)
        except Exception as e:
            print('Failed to delete %s. Reason: %s' % (file_path, e))
    

    file_logs = open("./data/logs/logs.txt", "w")
    file_logs.close()
    print("[", Fore.GREEN + "+","] ", "Log file created")

    cmd = input("Open a terminal to display logs? (Y/N) ")
    
    file.close()
    genFile.close()
    char.close()    
    c = Simulation(width+25, height+25, 'black', cmd)
    c.mainloop()
    



class Simulation(tk.Tk):
    def __init__(self, *args):
        super().__init__()
        self.title("DebugVersion0.0.8")
        self.resizable(False, False)
        
        self.day = 0
        self.time = 1 
                        
        #0.5: slow, 1: normal, 2: fast, 4: fast_forward
        #8: ultra fast
        #gerer avec clock.py
        
        # Create a canvas widget
        self.canvas = tk.Canvas(self, height=args[1], width=args[1], bg=args[2])
        self.canvas.pack(fill=tk.BOTH, expand=True)
        
        # Bind the configure event to the create_grid method
        self.bind('<Configure>', self.create_grid)

        subprocess.Popen(['python', 'sync_clock.py']) #remove shell=true 
        
        if args[3] == "Y" or args[3] == "y":
            subprocess.Popen(['start', 'cmd', '/k', 'python', 'data/logs_cmd.py'], shell=True) 

        
        input_thread = threading.Thread(target=self.edit)
        input_thread.daemon = True  # Daemonize thread
        input_thread.start()
        self.start_background_task()
        

        #thread = threading.Thread(target=self.movement)
        #thread.daemon = True  # This allows the thread to exit when the main program does
        #thread.start()
        
        
        # Example of creating a new character (rectangle)
        #self.bind('<Button-1>', self.create_new_character(40, 40))
        #self.bind('<Button-1>', self.create_new_character(60, 40))
        #self.bind('<Button-1>', self.create_new_character(40, 60))
        #self.canvas.create_oval(height/2, width/2, height/2+5, width/2+5, fill="red", outline="red")
        #center point
        #self.setup(self.edit, self.start_clock)


    def create_new_character(self,posx, posy, cmd, event=None):
        try:
            self.canvas.create_oval(posx, posy, posx+10, posy+10, fill="white", outline="red")
            if cmd == True:
                print("[", Fore.GREEN + "+","] ", "Character artifiaclly created sucessfully")
                write_logs(f"GUI created char: {posx, posy, posx+10, posy+10}")
        
        except:
            print(Fore.RED + 'Error', ': Artificial char. creation failed')
    
    def start_background_task(self):
        thread = threading.Thread(target=self.movement)
        thread.daemon = True  # Daemonize thread to exit when main program exits
        thread.start()

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
        while True:
            time.sleep(4)
            self.canvas.delete('all') 
            self.create_grid()
            try:
                with open("data/TempChar.csv", "r") as file:
                    file_get_pos = csv.reader(file)
                    next(file_get_pos)
                    for line in file_get_pos:
                        self.create_new_character(int(line[1])+10, int(line[2])+10, False)
                #print("[", Fore.GREEN + "+","]",'all entity was moved sucessfully') debbug

            except Exception as e:
                #print('there was an error in moving all the entities')
                print(Fore.RED + 'Error: ', e)


    def CreateCharStasts(self, id, values=None):
        #values est une liste
        s = ['M', 'F']
        stats = {'age': 15, 'health': 150, 'happiness': 80, 'stress': 12, 
        'mentalHealth':100, 'desire':0, 'loneliness': 7, 'boredom': 25, 'anger':10, 'hygiene':100, 
        'sex': s[random.randint(0,1)], 'bday': self.day, 'couple': 'no'}
        model = open('./data/memory/model/'+id+'.dmem', 'w')
        print('./data/memory/model/'+id+'.dmem')
        model.write('id=' + id + "\n") #0
        model.write('disease=null' + "\n") #1
        model.write('mvt=null' + "\n") #2
        model.write('ir_target=hap++' + '\n') #3
        model.write('caction=null' + '\n') #4
        model.write('paction=null' + '\n') #5
        model.write('immunity=null' + '\n') #6
        model.write('tmp=null' + '\n') #7
        model.write('mact=null' + '\n') #8
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




    
    def CreateTempPosition(self, id, x, y, gen):
        with open('./data/TempChar.csv', 'a', newline='') as fileTemp:
            csvwriter = csv.writer(fileTemp)
            csvwriter.writerow([id, x, y, gen])
        


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

    
    def runInParallel(*fns):
        proc = []
        for fn in fns:
            p = Process(target=fn)
            p.start()
            proc.append(p)
        for p in proc:
            p.join()

        runInParallel(func1, func2)

    

    def edit(self):     
        
        while 1:            
            command = input('>')
            if command == 'nc' or command == "newcharacter":
                # Creation of a new character artificially
                while True:
                    x = input("X position(px: int): ")
                    y = input("Y position(px: int): ")
                    try:
                        x = int(x)
                        y = int(y)
                        break  # Exit the loop if both inputs are valid integers
                    except ValueError:
                        print(Fore.RED + "Error:", "wrong input type, integer expected. Please try again.")

                if x < 0 or x > self.canvas.winfo_width() or y < 0 or y > self.canvas.winfo_height():
                    print(Fore.RED + "Error",": Out of Bounds -> x in ", (0, self.canvas.winfo_width()), "y in", (0, self.canvas.winfo_height()))
                elif x == 000: #random coords
                    print("random value")
                    xV = random.randint(0, self.canvas.winfo_width())
                    yV = random.randint(0, self.canvas.winfo_height())
                    self.create_new_character(xV, yV, True)
                    id = self.randmId()
                    self.CreateTempPosition(id, xV, yV, 'x')
                    self.CreateCharStasts(id)
                else:
                    
                    self.create_new_character(x, y, True)
                    id = self.randmId()
                    self.CreateTempPosition(id, x, y, 'x')
                    self.CreateCharStasts(id)

            elif command == "logs" or command == "l":
                print_logs()

            elif command == 'd' or command == 'data':
                type = input('type of data (referer help data): ')
                if type == 'all' or type == 'a':
                    self.get_all_Info()

                if type == 'id' :
                    id = input('enter character id: ')
                    self.get_info_Id(id)

            elif command == 'mvt' : #debug
                self.movement(4)

                
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
    print('client version: 0.0.8')
    time.sleep(0.2)
    print('https://github.com/LopoDistrict/HumanSimulation')
    begin_param()
