import tkinter as tk
import json
import os
import csv
import random
from colorama import init, Fore, Back, Style
import os.path
import datetime
import time
import subprocess 
from data_ui_manager import *



def increase_tick_rate(new_tick):
    tick = new_tick
    print(f"Tick was changed new tick: {new_tick}")
    

def start_clock(tick):
    #clock.cpp ne tourne qu'une seule fois
    #c'est dans ce fichier que nous devons le faire tourner au rythme souhaité
    while True:
        print("New cycle started")
        try: 
            result = subprocess.run(["./clock.exe"], check=True, capture_output=True, text=True) 
            print("Output:", result.stdout)  # Print standard output 
            print("Errors:", result.stderr)    # Print standard error (if any) 
            print("calculation finished sucessfully")
        except subprocess.CalledProcessError as e: 
            print("An error occurred while running the clock.exe file.") 
            print("Return Code:", e.returncode) 
            print("Output:", e.output) 
            print("Error Output:", e.stderr)
            write_logs(f"Error occured while running clock.exe: {e.stderr}")

        time.sleep(tick)
