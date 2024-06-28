# AUTHOR: Komodo
# Build : V0.0.1
# Fonction du bohneur 

# calcul le bohneur à partir de 2 valeur 
# c : constante qui peut affecter le bohneur 
#       - négativement si c <= 0
#       - positivement si c > 0
#       - nullement si c = 0
# v : valeur du bohneur au t-1, donc la valeur du bohneur au
# nouveau jour
# le bohneur baisse plus lentement qu'il croit



def calcul_bohneur(c, v):
    if c <= 0:
        return v - (0.038 * abs(c))
    else:
        return v + 0.018 * c



v= 80
b = []
for i in range(100):
    v = calcul_bohneur(0, v)
    b.append(v)

print(b)
    