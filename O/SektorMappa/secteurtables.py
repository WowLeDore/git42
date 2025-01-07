import sqlite3

def create_tables_from_sql(sql_file, db_name):
    # Connexion à la base de données SQLite
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    # Ouvrir le fichier SQL et lire les commandes
    with open(sql_file, 'r') as file:
        sql_script = file.read()

    # Exécution des commandes SQL
    try:
        cursor.executescript(sql_script)
        conn.commit()
        print(f"Tables créées avec succès dans {db_name}.")
    except sqlite3.Error as e:
        print(f"Erreur lors de la création des tables : {e}")
    finally:
        # Fermer la connexion à la base de données
        conn.close()

# Nom du fichier SQL et de la base de données SQLite
sql_file = 'create_tables.sql'
db_name = 'secteurs_activites_idf.db'

# Créer les tables à partir du fichier SQL
create_tables_from_sql(sql_file, db_name)

