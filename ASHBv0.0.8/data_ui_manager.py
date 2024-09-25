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