import sys
import numpy as np
from PyQt5 import QtCore, QtWidgets
import pyqtgraph as pg
import pyqtgraph.opengl as gl
from random import randint
import csv

class Graph3D(QtWidgets.QWidget):
    def __init__(self):
        print('loading...')
        super().__init__()
        
        
        # Setup the GUI layout
        self.layout = QtWidgets.QVBoxLayout(self)
        self.view = gl.GLViewWidget()
        self.layout.addWidget(self.view)
        self.setLayout(self.layout)
        self.resize(800, 600)
        self.setWindowTitle("Graph")
        
        # Set up the 3D graph
        self.graph_items = []
        self.setup_graph()
        

    def get_couple(self, id):
        #return l'id pointé
        with open('../data/memory/couple.mem') as file:
            for line in file:
                print('line[0:8]'+line[0:8])
                print(id == line[0:8])
                print('id'+ id)
                print(line[8])
                if line[0:8] == id and line[8] == "-":
                    return line[9:17]
        return "not"


    def setup_graph(self):
        # Create some nodes and edges         
        edges = []
        visited = []
        count = 0
        csv_file = csv.reader(open('../data/TempChar.csv', "r"), delimiter=",")
        next(csv_file)

        for row in csv_file:
            if row[3] == "no": 
                print('no_couple')                                
                #nodes.append([randint(1, 8),randint(1, 8), randint(1, 8)])
                count += 1
                 
            else:                
                if self.get_couple(row[0]) != 'not' and self.get_couple(row[0]) not in visited:
                    visited.append(self.get_couple(row[0]))
                    print('couple')
                    edges.append((count, count+1))
                    count+=2

            visited.append(row[0])

        print(visited)
        print(edges)
        print(np.random.randint(1,8, size=(len(visited), 3)))
        
        
        pos = np.array(np.random.randint(1,8, size=(len(visited), 3))) #len visited )        
        self.pos = pos

        # Add nodes (spheres) to the view
        for p in pos:
            node = gl.GLScatterPlotItem(pos=np.array([p]), size=8, color=(1, 1, 1, 1))
            self.view.addItem(node)
            self.graph_items.append(node)
        
        # Add edges (lines) to the view
        #edges = [(0, 1), (0, 2)]
        for edge in edges:
            line = gl.GLLinePlotItem(pos=pos[list(edge)], color=(1, 1, 1, 1), width=2, antialias=True)
            self.view.addItem(line)
            self.graph_items.append(line)




class TextWindow(QtWidgets.QWidget):
    def __init__(self, text):
        super().__init__()
        
        # Setup the window layout
        self.setWindowTitle("Graph")
        self.layout = QtWidgets.QVBoxLayout(self)
        self.label = QtWidgets.QLabel(text, self)
        self.layout.addWidget(self.label)
        self.setLayout(self.layout)

if __name__ == "__main__":
    
    app = QtWidgets.QApplication(sys.argv)
    graph = Graph3D()
    graph.show()
    sys.exit(app.exec_())
