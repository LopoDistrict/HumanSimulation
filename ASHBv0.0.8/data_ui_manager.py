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
    