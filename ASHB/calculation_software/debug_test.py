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



"""
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