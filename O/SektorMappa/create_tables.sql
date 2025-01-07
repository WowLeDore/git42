-- create_tables.sql
CREATE TABLE Secteurs (
    id_secteur INTEGER PRIMARY KEY AUTOINCREMENT,
    nom_secteur TEXT NOT NULL,
    type_secteur TEXT,
    nombre_personnes_impactees INTEGER,
    importance INTEGER,
    latitude REAL,
    longitude REAL,
    geohash TEXT,
    adresse TEXT,
    code_postal TEXT
);

CREATE TABLE Contacts (
    id_contact INTEGER PRIMARY KEY AUTOINCREMENT,
    id_secteur INTEGER,
    nom_contact TEXT,
    fonction TEXT,
    email TEXT,
    telephone TEXT,
    FOREIGN KEY (id_secteur) REFERENCES Secteurs(id_secteur)
);

CREATE TABLE Horaires (
    id_horaire INTEGER PRIMARY KEY AUTOINCREMENT,
    id_secteur INTEGER,
    jour_semaine TEXT,
    heure_ouverture TIME,
    heure_fermeture TIME,
    FOREIGN KEY (id_secteur) REFERENCES Secteurs(id_secteur)
);

CREATE TABLE Employes (
    id_employe INTEGER PRIMARY KEY AUTOINCREMENT,
    id_secteur INTEGER,
    nom_employe TEXT,
    fonction TEXT,
    date_embauche DATE,
    salaire REAL,
    FOREIGN KEY (id_secteur) REFERENCES Secteurs(id_secteur)
);

CREATE TABLE Zones (
    id_zone INTEGER PRIMARY KEY AUTOINCREMENT,
    nom_zone TEXT,
    latitude REAL,
    longitude REAL,
    rayon_km INTEGER
);

CREATE TABLE SecteursZones (
    id_secteur INTEGER,
    id_zone INTEGER,
    FOREIGN KEY (id_secteur) REFERENCES Secteurs(id_secteur),
    FOREIGN KEY (id_zone) REFERENCES Zones(id_zone)
);

