#include "../header/Configuration.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Configuration::Configuration(string nomFichier)
{
    // Ouverture du fichier de configuration
    ifstream fichier(nomFichier, ios::in);
    if(fichier)
    {
        string vide;
        // On charge toutes les données de configuration dans les attributs associés
        fichier >> vide >> vide >> vide >> vide
        >> vide >> prixFantassin >> prixArcher >> prixCatapulte
        >> vide >> vieFantassin >> vieArcher >> vieCatapulte
        >> vide >> attFantassin >> attArcher >> attCatapulte
        >> vide >> portMinFantassin >> portMinArcher >> portMinCatapulte
        >> vide >> porteeFantassin >> porteeArcher >> porteeCatapulte
        >> vide >> zoneFantassin >> zoneArcher >> zoneCatapulte
        >> vide >> vieJoueur
        >> vide >> orParTour
        >> vide >> limiteTour
        >> vide >> tailleMap;

        fichier.close();
    }
    else cerr << "Erreur fichier configuration" << endl;
}

Configuration::~Configuration()
{
    //dtor
}
