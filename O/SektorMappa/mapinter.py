import folium
from folium.plugins import MarkerCluster
import sqlite3
import math

# Connexion à la base de données SQLite
def fetch_data_from_db(db_name):
    conn = sqlite3.connect(db_name)
    cursor = conn.cursor()

    # Récupérer les secteurs avec leurs coordonnées géographiques, type de secteur et le nombre d'employés
    cursor.execute('''
        SELECT nom_secteur, latitude, longitude, nombre_personnes_impactees, type_secteur
        FROM Secteurs
    ''')
    data = cursor.fetchall()
    conn.close()
    return data

# Fonction pour créer la carte interactive
def create_map(data):
    # Initialiser la carte centrée sur l'Île-de-France
    m = folium.Map(location=[48.8566, 2.3522], zoom_start=10)  # Paris coordinates

    # Créer des groupes de secteurs pour chaque type
    secteur_groups = {}

    # Définir une couleur pour chaque secteur
    sector_colors = {
        "Agriculture": "green",
        "BTP": "yellow",
        "Commerce de détail": "blue",
        "Industrie": "red",
        "Transport": "purple",
        "Technologie": "orange",
        "Énergie": "cyan"
    }

    # Fonction pour générer la taille des cercles en fonction du nombre d'employés
    def get_circle_radius(employees):
        # Logarithmic scale for better distribution
        return 5 + math.log(employees + 1) * 5  # Log scale for circle size

    # Parent group names (e.g., Commerce, Secteur d'activité, etc.)
    parent_groups = {
        "Secteur d'activité": ["Agriculture", "BTP", "Commerce de détail", "Industrie"],
        "Industrie": ["Technologie", "Énergie"],
        "Commerce": ["Commerce de détail", "Transport"]
    }

    # Organiser les données en fonction des secteurs
    for sector in data:
        name, lat, long, employees, sector_type = sector

        # Créer un groupe pour chaque type de secteur s'il n'existe pas encore
        if sector_type not in secteur_groups:
            secteur_groups[sector_type] = folium.FeatureGroup(name=sector_type)

        # Définir la couleur du cercle en fonction du secteur
        color = sector_colors.get(sector_type, "blue")  # Default to blue if not found

        # Ajouter des marqueurs dans les groupes correspondants
        folium.CircleMarker(
            location=[lat, long],
            radius=get_circle_radius(employees),  # Taille du cercle en fonction du nombre d'employés
            popup=f"{name} - {sector_type}: {employees} employés",
            color=color,
            fill=True,
            fill_color=color,
            fill_opacity=0.6
        ).add_to(secteur_groups[sector_type])

    # Ajouter les groupes parentaux et leurs groupes enfants à la carte
    for parent_group, child_groups in parent_groups.items():
        parent_layer = folium.FeatureGroup(name=parent_group)

        for child_group in child_groups:
            # Ajouter chaque groupe enfant à son groupe parent
            if child_group in secteur_groups:
                secteur_groups[child_group].add_to(parent_layer)

        # Ajouter le groupe parent (avec ses enfants) à la carte
        parent_layer.add_to(m)

    # Ajouter le contrôle des couches (LayerControl)
    folium.LayerControl(collapsed=False).add_to(m)

    # Sauvegarder la carte sous forme de fichier HTML
    m.save('interactive_map_with_sectors_and_parent_selector.html')
    print("Carte interactive générée et sauvegardée dans 'interactive_map_with_sectors_and_parent_selector.html'.")

# Récupérer les données depuis la base de données
db_name = 'secteurs_activites_idf.db'  # Nom de votre base de données
data = fetch_data_from_db(db_name)

# Créer et afficher la carte interactive
create_map(data)

