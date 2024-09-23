import json
import os
import csv
import random
from colorama import init, Fore, Back, Style
import os.path
import datetime
import time
import subprocess 

def print_logs():
    with open("./data/logs/logs.txt", "r") as logfile:
        for line in logfile:
            print(line)

def write_logs(val):
    with open('./data/logs/logs.txt', "a") as logsFile:
        logsFile.write(f"<{datetime.datetime.now()}> {val}"+"\n")


def rep_l(file, line, value):
    with open(file, 'r', encoding='utf-8') as file: 
        data = file.readlines() 
        
    print(data) 
    data[line] = value + "\n"
        
    with open(file, 'w', encoding='utf-8') as file: 
        file.writelines(data) 