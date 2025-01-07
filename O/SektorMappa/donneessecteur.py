import sqlite3

# Connexion à la base de données SQLite
def insert_data_into_db(db_name):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    # Données d'exemple pour la table Secteurs
    secteurs_data = [
        ("Services financiers", "Services", 50000, 48.8566, 2.3522),
        ("Industrie pharmaceutique", "Industrie", 30000, 48.8566, 2.3420),
        ("Commerce de détail", "Commerce", 12000, 48.8700, 2.3400),
        ("Transport public", "Services", 100000, 48.8584, 2.2945)
    ]

    # Insérer les données dans la table Secteurs
    cursor.executemany('''
        INSERT INTO Secteurs (nom_secteur, type_secteur, nombre_personnes_impactees, latitude, longitude)
        VALUES (?, ?, ?, ?, ?)
    ''', secteurs_data)

    # Données d'exemple pour la table Contacts
    contacts_data = [
        (1, "Jean Dupont", "Directeur", "jean.dupont@exemple.com", "0123456789"),
        (2, "Marie Martin", "Manager", "marie.martin@exemple.com", "0987654321"),
        (3, "Pierre Durand", "Chef de secteur", "pierre.durand@exemple.com", "0147258369"),
        (4, "Sophie Leroy", "Responsable", "sophie.leroy@exemple.com", "0174839201")
    ]

    # Insérer les données dans la table Contacts
    cursor.executemany('''
        INSERT INTO Contacts (id_secteur, nom_contact, fonction, email, telephone)
        VALUES (?, ?, ?, ?, ?)
    ''', contacts_data)

    # Données d'exemple pour la table Horaires
    horaires_data = [
        (1, "Lundi", "09:00", "18:00"),
        (2, "Mardi", "09:00", "18:00"),
        (3, "Mercredi", "09:00", "18:00"),
        (4, "Jeudi", "09:00", "18:00")
    ]

    # Insérer les données dans la table Horaires
    cursor.executemany('''
        INSERT INTO Horaires (id_secteur, jour_semaine, heure_ouverture, heure_fermeture)
        VALUES (?, ?, ?, ?)
    ''', horaires_data)

    # Sauvegarder et fermer la connexion
    conn.commit()
    conn.close()

# Exécution du code pour insérer les données dans la base de données
db_name = 'secteurs_activites_idf.db'
insert_data_into_db(db_name)
print("Données insérées avec succès dans la base de données.")

