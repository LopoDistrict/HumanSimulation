import os
import time

class start():
    def __init__(self):
        print("loading into simulation...")
        print("""
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@    @@@@@@@    @@@@@@@
@@@@@@@@    @@@@@@@    @@@@@@@
@@@@@@@@      @@@      @@@@@@@
@@@@@@@@@@    @@@    @@@@@@@@@
@@@@@@                   @@@@@
@@@@@@@@@@    @@@    @@@@@@@@@
@@@@@@@@      @@@      @@@@@@@
@@@@@@@@    @@@@@@@    @@@@@@@
@@@@@@@@    @@@@@@@    @@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@""")

        print("1. Start simulation\n 2. modify parameters \n ")
        
    def input(self):
        self.choice = input(">")


if __name__ == "__main__":
    r = start()
    r.choice()
    