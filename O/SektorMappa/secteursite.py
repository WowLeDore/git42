from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

# Fonction pour se connecter à la base de données et obtenir les données
def get_data(table, order_by="id_secteur"):
    conn = sqlite3.connect('secteurs_activites_idf.db')
    cursor = conn.cursor()

    query = f"SELECT * FROM {table} ORDER BY {order_by};"
    cursor.execute(query)
    data = cursor.fetchall()
    conn.close()

    return data

@app.route('/')
def index():
    # Récupérer la table et le tri depuis les paramètres de la requête
    table = request.args.get('table', 'Secteurs')
    order_by = request.args.get('sort', 'id_secteur')

    # Obtenir les données de la table demandée
    data = get_data(table, order_by)

    # Obtenir la liste des tables pour le sélecteur
    tables = ['Secteurs', 'Contacts', 'Horaires', 'Employes', 'Zones', 'SecteursZones']

    # Rendre les données dans le modèle HTML
    return render_template('index.html', data=data, sort_by=order_by, table=table, tables=tables)

if __name__ == '__main__':
    app.run(debug=True)

