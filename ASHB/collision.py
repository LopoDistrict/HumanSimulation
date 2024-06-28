import math
import main
import csv

# /!\  INSTANCIER LA CLASSE COLLISION AVEC VAR DE main.py   /!\

class Collision:
    def __init__(self, height, width):
        self.height = height
        self.width = width

        self.mesh = []  #matrice
        #on append que les mailles qui ont plus de 2 char dans la maille 

    def separate(self):
        HeightSliced = self.height/15
        WidthSliced =self.width/15
        tempHeight, tempWidth = 0, 0
        row = []
        for y in range(15):            
            while tempHeight < self.height:
                row.append((tempHeight, tempHeight+HeightSliced, tempWidth, tempWidth+WidthSliced))
                tempHeight += HeightSliced
                tempWidth += WidthSliced
                #pourquoi dans python les comments sont en # et pas en //
                #si ce langage n'etait polyvalent il puerait vraiment la merde
            self.mesh.append(row)
            tempHeight, tempWidth = 0, 0
            row = []
        return self.mesh


    
    def presence(self):
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
        csv_file = csv.reader(open('./data/TempChar.csv', "r"), delimiter=",")
        for i in range(len(self.mesh)): #on boucle dans la premiere ligne de matrice [  =>[]<=  ]
            #ca pue les commantaires python
            for j in range(len(self.mesh[i])): #on boucle dans la sous matrice en tuple [[ =>()<= ]]
                for row in csv_file:
                    if row[0] >= self.mesh[i][j][0] and row[0] <= self.mesh[i][j][1] and row[1] >= self.mesh[i][j][2] and row[1] <= self.mesh[i][j][3]: #putain de trop long
                    #143 CARACTERE POUR UNE CONDITION :)
                        if num >= 2:
                            presence.append(row[0])
                        else:
                            num += 1    
                num = 0
        return presence

            
if __name__ == "__main__":
    Collision(main.height, main.width)


