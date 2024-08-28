from math import ceil
import os
import pandas as pd #no offense 
import ctypes
import csv
from data.gen_tree import TreeNode
from data.linked import Cellule
import random
#from main import 

class Data:
    def __init__(self):
        self.cal_lib = ctypes.CDLL('./calculation_software/cal.so')
        #self.rand_lib = ctypes.CDLL('./calculation_software/rand.so')
    
    
    def randmId(self):
        letters = "abcdefghijklmnopqrstuvwxyz"
        num = "0123456789"
        id = ""
        for i in range(8): 
            if i in [0, 6, 7]:
                id += num[random.randint(0, 9)]
            id += letters[random.randint(0, 25)]
        return id




    def desire(self, id, alr=False):  #a tester
        self.cal_lib.desire.argtypes = [ctypes.c_float, ctypes.c_int]
        self.cal_lib.desire.restype = ctypes.c_float

        old_s = float(self.get_value_char(id, 6))

        if old_s >= 50 and not alr:
            with open('./data/memory/couple.mem', 'r') as pointer:                                
                for i in pointer:
                    linked = Cellule(pointer.readline())
                    if linked.contenu == id:
                        #on a trouvé le pointant mtn on check pour 2 try 
                        #le pointé grace self.suivante
                        pointed = linked.suivante.contenu  
                        formula = (150 + self.get_value_char(pointed, 3))
                        if self.roll_random(formula/(old_s/5), 0, 200) or self.roll_random(formula/(self.cal_lib.desire(old_s, 0) /5), 0, 200):
                            #si true on a le desir entre eux
                            return self.start_couple(self, id, pointed)

                        else: #remove le pointer
                            with open("target.txt", "r+") as f:
                                d = f.readlines()
                                f.seek(0)
                                for i in d:
                                    if i != str(Cellule(id,pointed)):
                                        f.write(i)
                                f.truncate()    
                            # /!\ DDOIT LE GARDER EN MEMOIRE ET LE TRANSMETTRE /!\    

            #on check le pointeur pour verifier les 2 try
            #pointeur ./data/memory/couple.mem

        nvstats = self.cal_lib.desire(old_s, 0) 
        #0 est une constante qui peut faire augmenter le desire 
        #ou le faire baisser, cette const peut etre influencer par le pointé ou meme 
        #par le pointeur
        
        return self.update_csv_cell(self.get_index(id) , 6,  ceil(nvstats))
    



    def start_desire(self, id):
        #horrible function construction
        #with: 2, if: 4, for: 2
        gender = self.get_value_char(id, 11) 
        with open('./data/temp/presence.asb', 'r', newline='') as maille:
            maille = [maille]
            if id in maille:
                for i in range(len(list(maille))):
                    if id in maille[i]:
                        for j in range(len(maille[i])):
                            if self.get_value_char(maille[i][j], 11) != gender:
                                # pour savoir si idA commence a désirer un idB dans sa maille
                                if self.roll_random(50, 0, 200) == 'true': #on peut ajouter une const
                                    #k où k peut etre influer a la baisse par la genealogie ou autre
                                    # debut d'une reelle attirance donc on met en memoire le pointeur
                                    with open('./data/memory/temp_char.mem', 'a', newline='', encoding='utf-8') as mem_file:
                                        #si l'attirance a marché on fait pointé l'idA de base 
                                        #vers le char idB (maille[i][j]) que l'idA est attiré
                                        mem_file.write(Cellule(id, maille[i][j]))





    def start_couple(self, idA, idB): #a tester
        #le pointeur et pointé on accepté par 
        #la fonction roll() de la lib rand_lib
        if int(self.get_value_char(idA, 1)) >= 16 and int(self.get_value_char(idB, 1)) >= 16: #age minimum pour relation (xd)
            tree_parent = "TreeNode('X', TreeNode([(idA, idB), []]))" #on créer un arbre avec les parents                              
            
            with open('./data/memory/gen.mem', 'a', newline='') as file_gen:                                
                file_gen.write(f'{self.randmId()}: {tree_parent}\n')  
                
            self.desire(idA, True)
            self.desire(idB, True)
            self.bonheur(idA, 30)
            self.bonheur(idB, 30)
            #se rapproche physiquement
        else:
            print('Not tall enough.')





    def roll_random(self, tranche, begin, end):  #a tester
        self.rand_lib.roll.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
        self.rand_lib.roll.restype = ctypes.c_bool

        return self.cal_lib.roll(tranche, begin, end)



    def bonheur(self, id, const):        
        #self.cal_lib.bohneur.argtypes = [ctypes.c_int, ctypes.c_int] # REFAIRE LIB AVEC FLOAT CAR ERREUR
        self.cal_lib.bohneur.argtypes = [ ctypes.c_float]
        #self.cal_lib.bohneur.restype = ctypes.c_int 
        self.cal_lib.bohneur.restype = ctypes.c_float 

        old_s = float(self.get_value_char(id, 3))
        
        
        with open('./data/temp/presence.asb', 'r') as maille:
            maille = [maille]
            maille2 = maille.readlines()

            print(maille2)
            if id not in str(maille2):
                print("not in mesh")
                const-=0.2                
                nvstats = old_s + self.cal_lib.bohneur(const)  #0 = c = constante variable
                
            else:
                print("in mesh")
                const += 3
                #on recupere tout ceux qui sont proches 
                #si ces personnes la sont heureux cad leur stast >= 60
                # on augmente la const qui fait augpmente le bohneur
                with open('./data/temp/presence.asb', 'r') as file:
                    file = [file]
                    presence_data = eval(file.read())

                result = [id_list for id_list in presence_data if id in id_list]

                print('result', result)
                for i in range(len(result[0])):
                    print(result[0][i])
                    if result[0][i] != id and int(self.get_value_char(result[0][i], 3)) >= 60:
                        print('good')
                        const += 6.5


                """
                const += 3
                maille.seek(0)

                maille = [maille]
                for i in range(len(maille)):
                    print('maille[i]', maille[i])
                    print(type(maille[i]))
                    if id in maille[i]:
                        for j in range(len(maille[i])):
                            print('maille[i][j]', maille[i][j])
                            print(self.get_value_char(maille[i][j], 3))
                            if int(self.get_value_char(maille[i][j], 3)) >= 60: 
                                const += 6.5
                """
                                                
                nvstats = old_s + self.cal_lib.bohneur(const) #0 = c = constante variable
            
        print('nvstats bohneur', nvstats)
        return self.update_csv_cell(self.get_index(id) , 3,  ceil(nvstats))



    
    def solitude(self, id):        
        # Declare the function signature
        self.cal_lib.solitude.argtypes = [ctypes.c_float, ctypes.c_float]
        self.cal_lib.solitude.restype = ctypes.c_float 
      
        # update solitude stats in the file based on presence
        with open('./data/temp/presence.asb', 'r', newline='') as maille:
            maille = [maille]
            old = float(self.get_value_char(id, 7))
            new = (float(self.get_value_char(id, 3)) / 9) / (float(self.get_value_char(id, 8)) / 6)

            print(old)
            print(new)
            if id not in maille:
                nvstats = self.cal_lib.solitude(old, new)
                print('not in')
            else:
                nvstats = self.cal_lib.solitude(old, new / maille.read().count(id))

            print('nvstats', ceil(nvstats))
            ind = self.get_index(id)
            print(ind)
            return self.update_csv_cell(ind , 7, ceil(nvstats))

        

    def get_index(self, id):                    
        with open('./data/CharacterData.csv') as file:
            file_get = csv.reader(file)
            num = 0
            for row in file_get:
                num+=1
                if row[0] == id:                    
                    return num-1


    def get_value_char(self, id, value_ind):
        #value est un indice (checker la feuille stats + emotion        
        with open('./data/TempChar.csv') as file:
            file_get = csv.reader(file)
            for row in file_get:
                if row[0] == id:
                    #print(row[value_ind])
                    file.seek(0)
                    return row[value_ind]

        return 'Error: bad id/value'


    def update_csv_cell(self, row_index, col_index, new_value):
        # Read the CSV file
        with open('./data/CharacterData.csv', 'r') as file:
            reader = csv.reader(file)
            rows = list(reader)
        # Update the cell value
        rows[row_index][col_index] = new_value
        # Write the updated data back to the CSV file
        with open('./data/CharacterData.csv', 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerows(rows)

    
    def modify_value_char(self, id, value, stats):
        # /!\ OBSOLETE
        #value != indice
        df = pd.read_csv("./data/CharacterData.csv") 
        
        df.loc[id, value] = stats        
        df.to_csv("./data/CharacterData.csv", index=False) 



if __name__ == "__main__":
    
    l = Data()
    print(l.get_value_char('0kfpdq75', 1))


 


