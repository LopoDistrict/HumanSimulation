import math
#from simulation import height, width
import csv



class 4:
    def __init__(self, height, width):
        self.height = height
        self.width = width

        self.mesh = []  #matrice
        #on append que les mailles qui ont plus de 2 char dans la maille 

    def tempWrite(self, file, value):
        with open(f'{file}.asb', 'w', encoding='utf-8') as file:
            file.write(value)


    def separate(self):
        with open('./data/temp/tempSeparation.asb', 'r') as fileObj:
            first_char = fileObj.read(1) 
            #if not first_char: #on check si on a pas deja séparé sachant que la map ne fait qu'une taille
            HeightSliced = math.ceil(self.height/15)
            WidthSliced = math.ceil(self.width/15)
            tempHeight, tempWidth = 0, 0
            row = []
            for y in range(15):            
                while tempHeight < self.height:
                    row.append((tempHeight, tempHeight+HeightSliced, tempWidth, tempWidth+WidthSliced))
                    tempHeight += HeightSliced
                    #tempWidth += WidthSliced
                    #pourquoi dans python les comments sont en # et pas en //
                    #si ce langage n'etait polyvalent il puerait vraiment la merde
                self.mesh.append(row)
                tempHeight = 0
                tempWidth += WidthSliced 
                row = []
            self.tempWrite('./data/temp/tempSeparation', str(self.mesh))
            print(type(self.mesh))
            return self.mesh
                
            #else:
            #    self.mesh.append(fileObj.read(1)) # ne fonctionne pass
            #    print(self.mesh)
            #    return self.mesh



    def presence(self):        
        print("launching")
        print(self.mesh)
        #Nous premet de ne pas calculer le comportement des perssonnes qui ne sont pas en collisions
        #en cherchant combien de personne sont proche
        #afin de calculer les comportements de collisions des personnes proches par leur id
        #et de calculer le comportement des personnes seules separement
        #nous evite le calcul de rayon de chaque personne lors de la modification des stats
        #22:31 => fin :) gl hf
        #40min pour setup la fonction dans ma tete
        #envie de me défenestrer :=}
        num = 0 #nous garde un compte du nb de personne dans une maille
        presence = []
        tempChar = []
        with open('./data/TempChar.csv', "r") as csv_file:
            csv_reader = csv.reader(csv_file)
            csv_header = next(csv_reader)  # Skip the header row

            for i in range(len(self.mesh)):  # on boucle dans la premiere ligne de matrice [  =>[]<=  ]
                #print('i', i)
                
                for j in range(len(self.mesh[i])):  # on boucle dans la sous matrice en tuple [[ =>()<= ]]
                    #print("j", j)
                    csv_file.seek(0)  # Reset file pointer to the beginning of the file
                    next(csv_reader)  # Skip the header row again after resetting the file pointer
                    for row in csv_reader:                        
                        #print('num', num)
                        #print(" ")
                        #print('x0', self.mesh[i][j][0])
                        #print('y0', self.mesh[i][j][1])
                        #print('x1', self.mesh[i][j][2])
                        #print('y1', self.mesh[i][j][3])
                        print(row[1], row[2])
                        if int(row[1]) >= self.mesh[i][j][0] and int(row[1]) <= self.mesh[i][j][1] and int(row[2]) >= self.mesh[i][j][2] and int(row[2]) <= self.mesh[i][j][3]:  # putain de trop long
                            if num >= 2:
                                tempChar.append(row[0])
                                
                            else:
                                tempChar.append(row[0])
                                num += 1
                    
                    if tempChar != [] and len(tempChar) != 1:
                        presence.append(tempChar)
                    tempChar = []
                    num = 0
                    
        self.tempWrite('./data/temp/presence', str(presence))
        print(presence)
        return presence


if __name__ == "__main__":
    l = Collision(400, 400)
    l.separate()
    l.presence()