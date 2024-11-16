import json
import os
import csv
import random
from colorama import init, Fore, Back, Style
import os.path
import datetime
import time
#import panda
import subprocess 
import platform
import psutil


def print_logs():
    with open("./data/logs/logs.txt", "r") as logfile:
        for line in logfile:
            print(line)

def write_logs(val):
    with open('./data/logs/logs.txt', "a") as logsFile:
        logsFile.write(f"<{datetime.datetime.now()}> {val}"+"\n")
    
def write_main_logs(val):
    with open('./data/logs/main_logs.txt', "a") as logsFile:
        logsFile.write(f"<{datetime.datetime.now()}> {val}"+"\n")


def app_l(file_path, line_number, value):
    # Read the contents of the file
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    # Check if the line number is valid
    if line_number < 1 or line_number > len(lines):
        print("Error: Line number out of range.")
        return
    
    # Append the value to the specified line
    lines[line_number - 1] = value + '\n'
    
    # Write the modified contents back to the file
    with open(file_path, 'w') as file:
        file.writelines(lines)

def save():
    #ISO-8601
    date = datetime.datetime.now().strftime("%Y-%m-%d·%H-%M-%S")
    save_folder = "./saves/save-" + date + "-" + self.randmId()
    os.mkdir(save_folder)
    
    files = [
        "/logs/logs.txt", 
        "/logs/main_logs.txt", 
        "/temp/presence.asb", 
        "/temp/GenTempModule.asb", 
        "/temp/tempSeparation.asb", 
        "/memory/couple.mem", 
        "/memory/gen.mem",
        "/TempChar.csv",
        "/CharacterData.csv"
    ]

    print("Saving files...")
    for i in files:
        try:
            shutil.copy("./data" + i, save_folder)
            print("Saving: ./data" + i)
        except Exception as e:
            print(f"An error occurred, cannot save: ./data{i}. Error: {e}")

            
    for root, dirs, files in os.walk("./data/memory/model"):
        for file in files:
            file_path = os.path.join(root, file)
            try:
                shutil.copy(file_path, save_folder)
                print("Saving:", file_path)
            except Exception as e:
                print(f"An error occurred, cannot save: {file_path}. Error: {e}")

    print("Data saved at", save_folder)
    #on récupère tout les values
    #-.asb extenstion => ./data/temp/
    #-.dmem extension => ./data/memory/model/
    #-.csv extension => ./ //fichier racine de data

                
def get_line_equivalent(id, line):
    lineFile = str(get_model(id, line))
    path = "./data/temp/GenTempModule.asb"
    value = ""    
    for i in lineFile:
        if i == "=":
            return value
        value += i


def get_model(id, line):
    path = "./data/temp/GenTempModule.asb"    
    result = ""
    with open(path) as file:
        return file.readlines()[line]


def get_value(id, line):
    value = get_line_equivalent(id, line)
    model = get_model(id, line)
    return model[len(value)+1:] 

'''
def read_csv_raw(path_file):
    try:
        df = pd.read_csv(path_file)
        print(df)
    except:
        print("an error occured, cannot print csv: " + path_file)
'''

def get_index(id):                    
    with open('./data/CharacterData.csv') as file:
        file_get = csv.reader(file)
        num = 0
        for row in file_get:
            num+=1
            if row[0] == id:                    
                return num-1


def get_value_char(id, value_ind):
    #value est un indice (checker la feuille stats + emotion        
    with open('./data/TempChar.csv') as file:
        file_get = csv.reader(file)
        for row in file_get:
            if row[0] == id:
                #print(row[value_ind])
                file.seek(0)
                return row[value_ind]

        return 'Error: bad id/value'

def data_csv_entity_data(id):
    x = ['id',"age", 'health', 'happiness', 'stress', 'mentalHealth', 'desire',
     'loneliness', 'boredom', 'anger', 'hygiene', 'sex', 'bday', 'couple']
    with open("./data/CharacterData.csv", "r") as csvfile:
        lines = csv.read_csv(csvfile, delimiter=",")
        for row in lines:
            if row[0] == id:
                print("")
                print(x)
                print("Entity Data: " + id)
                print(row)
                print("")
            break

def all_csv_data():
    x = ['id',"age", 'health', 'happiness', 'stress', 'mentalHealth', 'desire',
     'loneliness', 'boredom', 'anger', 'hygiene', 'sex', 'bday', 'couple']
    with open("./data/CharacterData.csv", "r") as csvfile:
        lines = csv.read_csv(csvfile, delimiter=",")
        csvfile.seek(0)
        for row in lines:
            print("")
            print(x)
            print("All Entities Data")
            print(row)
            print("")


def print_pos_ent(id):
    with open("./data/TempChar.csv", "r") as csv_file:
        lines = csv.read_csv(csvfile, delimiter=",")
        for row in lines:
            if row[0] == id:
                print("")
                print(x)
                print("Entity Position: " + id)
                print("x: "+row[1] + "\t" + "y: "+row[2])
                print("")
            break

def pos_ent_all():
    with open("./data/TempChar.csv", "r") as csv_file:
        csvfile.seek(0)
        lines = csv.read_csv(csvfile, delimiter=",")
        for row in lines:
            print("")
            print(x)
            print("All Position")
            print("x="+row[1] + "\t" + "y="+row[2])
            print("")
            
def debbug_screen():
    print("<- debbug_menu -> ")
    #client information
    print(platform.machine())
    print(platform.version())
    print(platform.platform())
    print(platform.processor())
    print("Node: " +platform.node())
    print(psutil.cpu_count())
    print(psutil.cpu_stats())
    print(psutil.cpu_freq())
    print(psutil.cpu_stats())
    memory = psutil.virtual_memory()
    print(f"mem: {memory.total} bytes")
    print(f"mem available: {memory.available} bytes")
    print(f"Used mem: {memory.used} bytes | {memory.percent}% ")
    print("")
    #software information
    with open("./data/temp/GenTempModule.asb", "r") as sfile:
        lines = sfile.readlines()
        print(f"ASHB {lines[4]}")
        print(f"height_map: {lines[0]}", end=" ")
        print(f"width_map: {lines[1]}", end=" ")
        print(f"climate: {lines[2]}", end=" ")
        
        print(f"day: {lines[3]}", end=" ")
        
    with open("./data/TempChar.csv", "r") as csv_file:
        csv_file.seek(0)
        c=0
        for row in csv_file:
            c+=1
        print(f"Ent: {c}")