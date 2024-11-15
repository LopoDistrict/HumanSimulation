import json
import os
import csv
import random
from colorama import init, Fore, Back, Style
import os.path
import datetime
import time
import panda
import subprocess 
import matplotlib.pyptlot as plt 

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

def read_csv_raw(path_file):
    try:
        df = pd.read_csv(path_file)
        print(df)
    except:
        print("an error occured, cannot print csv: " + path_file)

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

def all_csv_data(id):
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
                print("x="row[1] + "\t" + "y="+row[2])
                print("")
            break

def pos_ent_all(id):
    with open("./data/TempChar.csv", "r") as csv_file:
        csvfile.seek(0)
        lines = csv.read_csv(csvfile, delimiter=",")
        for row in lines:
            print("")
            print(x)
            print("All Position")
            print("x="row[1] + "\t" + "y="+row[2])
            print("")
            


