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
import ctypes



def increase_tick_rate(new_tick):
    tick = new_tick
    print(f"Tick was changed new tick: {new_tick}")
    
"""
def start_clock(tick):
    day = 0
    while True:
        try:   
            write_logs("New clock triggering, day: "+ str(day))
            write_main_logs("New clock triggering, day: "+str(day))         
            mylib = ctypes.CDLL('./lib_clock.so')  # For Windows
            
            # Specify the argument and return types of the functions
            mylib.add.argtypes = [ctypes.c_double, ctypes.c_double]
            mylib.add.restype = ctypes.c_double

            mylib.multiply.argtypes = [ctypes.c_double, ctypes.c_double]
            mylib.multiply.restype = ctypes.c_double

            restult = mylib.main_loop()
            
        except:
            write_logs("An Error occured")
    time.sleep(tick) 
    #write_logs("Execution time: " + time.time() - begin_time)
    day += tick #actualise day avec tick + write dans les param
    app_l("./data/temp/GenTempModule.asb", 4, str(day))    
"""
   
def start_clock(tick):
    day = 0
    #clock.cpp ne tourne qu'une seule fois
    #c'est dans ce fichier que nous devons le faire tourner au rythme souhaité
    #TO:DO
    #checker la frequence des ticks : day += 1 => vitesse clock definie par tick 
    #OU day += tick vitesse clock definie par les ticks
    while True:
        begin_time = time.time()
        #print("New cycle started")
        try: 
            write_logs("New clock triggering, day: "+ str(day))
            write_main_logs("New clock triggering, day: "+str(day))
            result = subprocess.run(["./clock5.exe"], check=True, capture_output=True, text=True) 
            #print("Output:", result.stdout)  # Print standard output 
            write_logs(result.stdout)
            #print("Errors:", result.stderr)    # Print standard error (if any) 
            #print("calculation finished sucessfully")
        except subprocess.CalledProcessError as e: 
            #print("An error occurred while running the clock.exe file.") 
            #print("Return Code:", e.returncode) 
            #print("Output:", e.output)
            write_logs(e.output) 
            #print("Error Output (clock):", e.stderr)
            write_logs(e.stderr)
            write_logs(f"Error occured while running clock.exe: {e.stderr}")
        time.sleep(tick) 
        write_logs("Execution time: " + str(time.time() - begin_time))
        day += tick #actualise day avec tick + write dans les param
        app_l("./data/temp/GenTempModule.asb", 4, str(day))


if __name__ == "__main__":
    start_clock(2)