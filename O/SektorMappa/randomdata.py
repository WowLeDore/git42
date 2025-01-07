import random
import sqlite3

# Connexion à la base de données SQLite
def insert_more_data(db_name):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    # Liste des secteurs d'activités (ajout de nouveaux secteurs)
    secteurs = [
        "Services financiers", "Industrie pharmaceutique", "Commerce de détail",
        "Transport public", "Agriculture", "Technologie", "Énergie", "BTP",
        "Santé", "Éducation", "Tourisme", "Culture", "Industries", "Transports",
        "Logistique", "Environnement", "Recherche et développement"
    ]

    # Générer des données aléatoires pour chaque secteur
    for _ in range(100):  # Générer 100 secteurs aléatoires
        nom_secteur = random.choice(secteurs)
        latitude = round(random.uniform(48.6, 49.1), 4)  # Latitude en Île-de-France
        longitude = round(random.uniform(2.1, 2.5), 4)  # Longitude en Île-de-France
        nombre_personnes_impactees = random.randint(500, 100000)  # Nombre d'employés entre 500 et 100 000

        # Insérer les données dans la table Secteurs
        cursor.execute('''
            INSERT INTO Secteurs (nom_secteur, type_secteur, nombre_personnes_impactees, latitude, longitude)
            VALUES (?, ?, ?, ?, ?)
        ''', (nom_secteur, "Secteur d'activité", nombre_personnes_impactees, latitude, longitude))

    # Sauvegarder et fermer la connexion
    conn.commit()
    conn.close()

# Exécution du code pour insérer les données
db_name = 'secteurs_activites_idf.db'
insert_more_data(db_name)
print("Données supplémentaires insérées avec succès dans la base de données.")

