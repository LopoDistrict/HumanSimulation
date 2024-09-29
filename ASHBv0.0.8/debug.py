import os

def modifier_ligne_fichier(fichier_chemin, valeur_a_remplacer):
    # Fichier temporaire pour écrire les modifications
    fichier_temp = fichier_chemin + '.tmp'
    
    # Ouvrir le fichier original en mode lecture et le fichier temporaire en mode écriture
    with open(fichier_chemin, 'r') as fichier_original, open(fichier_temp, 'w') as fichier_modifie:
        for ligne in fichier_original:
            # Si la ligne contient la valeur spécifique, on la commente avec //
            if valeur_a_remplacer in ligne.strip():
                fichier_modifie.write(f"{ligne.replace('//', '')}")  # Préfixer la ligne avec //
            else:
                fichier_modifie.write(ligne)
    
    # Remplacer le fichier original par le fichier modifié
    os.remove(fichier_chemin)  # Supprimer le fichier original
    os.rename(fichier_temp, fichier_chemin)  # Renommer le fichier temporaire pour le remplacer

def parcours_dossier_et_modification(dossier_chemin, valeur_a_remplacer):
    # Parcourir tous les fichiers et sous-dossiers du dossier donné
    for dossier_racine, sous_dossiers, fichiers in os.walk(dossier_chemin):
        for fichier in fichiers:
            fichier_chemin_complet = os.path.join(dossier_racine, fichier)
            # On vérifie si c'est un fichier texte avant de tenter de le modifier
            try:
                modifier_ligne_fichier(fichier_chemin_complet, valeur_a_remplacer)
                print(f"Modifié : {fichier_chemin_complet}")
            except Exception as e:
                print(f"Erreur avec le fichier {fichier_chemin_complet}: {e}")


def supprimer_fichiers_tmp(dossier_chemin):
    # Parcourir tous les fichiers et sous-dossiers du dossier donné
    for dossier_racine, sous_dossiers, fichiers in os.walk(dossier_chemin):
        for fichier in fichiers:
            if fichier.endswith('.tmp'):
                chemin_fichier = os.path.join(dossier_racine, fichier)
                try:
                    os.remove(chemin_fichier)  # Supprimer le fichier
                    print(f"Supprimé : {chemin_fichier}")
                except Exception as e:
                    print(f"Erreur lors de la suppression de {chemin_fichier}: {e}")

## Exemple d'utilisation
dossier_racine = './'  # Remplacez par le chemin de votre dossier
supprimer_fichiers_tmp(dossier_racine)

## Exemple d'utilisation
#dossier_racine = './'  # Remplacez par le chemin de votre dossier
#valeur_a_remplacer = 'std::cout'
##
#parcours_dossier_et_modification(dossier_racine, valeur_a_remplacer)
