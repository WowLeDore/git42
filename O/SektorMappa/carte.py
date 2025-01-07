import folium
from folium.plugins import MarkerCluster
import sqlite3

# Connexion à la base de données SQLite
def fetch_data_from_db(db_name):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    # Récupérer les secteurs avec leurs coordonnées géographiques et le nombre d'employés
    cursor.execute('''
        SELECT nom_secteur, latitude, longitude, nombre_personnes_impactees
        FROM Secteurs
    ''')
    data = cursor.fetchall()
    conn.close()
    return data

# Fonction pour créer la carte
def create_map(data):
    # Initialiser la carte centrée sur l'Île-de-France
    m = folium.Map(location=[48.8566, 2.3522], zoom_start=10)  # Paris coordinates

    # Ajouter un MarkerCluster pour regrouper les points
    marker_cluster = MarkerCluster().add_to(m)

    # Ajouter des marqueurs sur la carte, en fonction du nombre d'employés
    for sector in data:
        name, lat, long, employees = sector
        folium.CircleMarker(
            location=[lat, long],
            radius=5 + employees / 1000,  # Plus le nombre d'employés est élevé, plus le cercle est grand
            popup=f"{name}: {employees} employés",
            color='blue',
            fill=True,
            fill_color='blue',
            fill_opacity=0.6
        ).add_to(marker_cluster)

    # Sauvegarder la carte sous forme de fichier HTML
    m.save('map_with_sectors.html')
    print("Carte générée et sauvegardée dans 'map_with_sectors.html'.")

# Récupérer les données depuis la base de données
db_name = 'secteurs_activites_idf.db'  # Nom de votre base de données
data = fetch_data_from_db(db_name)

# Créer et afficher la carte
create_map(data)

