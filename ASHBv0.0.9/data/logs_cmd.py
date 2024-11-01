import os
import csv
import random
from colorama import init, Fore, Back, Style
import os.path
import datetime
import time
import subprocess 

def print_logs():    
    with open("./data/logs/logs.txt", "r") as log_file:
        linemoins = ""
        while True:
            for line in log_file:
                pass
                if len(line.strip()) != 0 and line != linemoins:
                    print(line)
                    linemoins = line

if __name__ == "__main__":
    print_logs()