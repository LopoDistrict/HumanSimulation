"""l = "OOOO0000>OOOO000025"
print(l[0:8])
print(l[8])
print(l[9:17])
print(l[17:len(l)])

def point(id):
    #return l'id pointé
    with open('testfile.txt') as file:
        for line in file:
            if line[0:8] == id and l[8] == ">":
                return line[9:17]
    return "not"


def get_couple(id):
    #return l'id pointé
    with open('testfile.txt') as file:
        for line in file:
            if line[0:8] == id and l[8] == "-":
                return line[9:17]
    return "not"

#on check si les deux on un désir réciproque
#sinon on try to start_couple
#si reciproque et ne marche pas on augmente le desir

def modify_desire(idA, idB, constant):
    with open('testfile.txt') as file:
        for line in file:
            if line[0:17] == idA+"-"+idB or line[0:17] == idB+"-"+idA:
                line[17:len(line)] += constant
            elif line[0:17] == idA+">"+idB or line[0:17] == idB+">"+idA:
                line[17:len(line)] += constant

    with open("file.txt", "w") as file:
        for line in lines:
            file.write(line)

def get_desire_couple(idA, idB):
    with open('testfile.txt') as file:
        for line in file:
            if idA in line and idB in line:
                return line[17:len(line)]


def get_desire_single(idA, idB):
    with open('testfile.txt') as file:
        for line in file:
            if line[0:17] == idA + ">" idB:
                return line[17:len(line)]
        
        
import random

def randmId():
    letters = "abcdefghijklmnopqrstuvwxyz"
    num = "0123456789"
    id = ""
    for i in range(8): 
        if i in [0, 6, 7]:
            id += num[random.randint(0, 9)]
        else:
            id += letters[random.randint(0, 25)]
    return id



    for i in range(40):
        with open('../data/TempChar.csv','a') as fd:
            if random.randint(0,1) == 1:
                fd.write(randmId()+ ',15'+ ',15'+ ',yes' +'\n')
            else:
                fd.write(randmId()+ ',15'+ ',15'+ ',no'+'\n')




def create_new_character(x, y):
    print(type(x))
    print(type(y))
    print(x)
    print(y)
import csv
try:
    with open("../data/TempChar.csv", "r") as file:
        file_get_pos = csv.reader(file)
        next(file_get_pos)
        for line in file_get_pos:
            print(line[1])
            print(line[2])
            create_new_character(int(line[1])+10, int(line[2])+10)
    print('all entity was moved')
except Exception as e:
    print('there was an error in moving all the entities')
    print( e)


def get_model(id, line):
    path = "../../data/memory/model/" + id + ".dmem"    
    result = ""
    with open(path) as file:
        return file.readlines()[line]

def get_line_equivalent(id, line):
    lineFile = str(get_model(id, line))
    path = "../../data/memory/model/" + id + ".dmem"
    value = ""    
    for i in lineFile:
        if i == "=":
            return value
        value += i
    
def get_value(id, line):
    value = get_line_equivalent(id, line)
    model = get_model(id, line)
    return model[len(value)+1:] 

print(get_model('0kfpdq75', 1))
print(get_line_equivalent('0kfpdq75', 1))
print(get_value('0kfpdq75', 1))     


def get_value_char(id, ind, path):
    with open(path) as file:
        result = ""
        for line in file:
            if id in line:
                return line.split(',')[ind]
        
#print(get_value_char("0kfpdq75", 2, "../data/TempChar.csv"))


def modify_model_mov(id, path, value, l):
    with open(path, 'r') as file:
        lines = file.readlines()
        
        lines[l] = value + '\n'
        with open(path, "w") as filew:
            filew.writelines(lines)
        
        #filew.write(file.readlines()[l])


modify_model_mov('0kfpdq75',  "../data/memory/model/0kfpdq75"  + ".dmem", "mvt=NE15" , 2)
"""
import os
import random

class Data:
    def get_value_char(self, id, index):
        # Placeholder for actual implementation
        pass

    def print_vector(self, vector):
        for item in vector:
            print(item)

    def get_index(self, id):
        # Placeholder for actual implementation
        pass

    def update_csv_cell(self, index, column, value):
        # Placeholder for actual implementation
        pass

def roll_random(chance, min_val, max_val):
    return random.randint(min_val, max_val) < chance

def num_generator(length, num):
    return ''.join(random.choices('abcdefghijklmnopqrstuvwxyz0123456789', k=length))

def start_desire(id):
    obj = Data()
    gender = obj.get_value_char(id, 11)
    maille_file_path = "./data/temp/presence.asb"
    maille = []

    # Read lines from the file into the maille list
    with open(maille_file_path, 'r') as maille_file:
        maille = maille_file.readlines()

    obj.print_vector(maille)

    # Check if the id exists in maille
    for line in maille:
        if id in line[1:8]:
            print("true")
            current_id = line[10:18]
            print("current_id", current_id)

            if obj.get_value_char(current_id, 11) != gender:
                if roll_random(20, 0, 300):
                    print("desire started:", id)
                    print(line[10:18])
                    with open("./data/memory/couple.mem", 'a') as mem_file:
                        mem_file.write(f"{id}>{current_id}{num_generator(2, 7)}\n")
                    obj.update_csv_cell(obj.get_index(id), 13, "yes")

def main():
    start_desire("4cdtwa69")

if __name__ == "__main__":
    main()

