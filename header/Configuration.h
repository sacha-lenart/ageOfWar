#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>

class Configuration
{
    public:
        Configuration(std::string nomFichier = "confStandard.txt");
        virtual ~Configuration();
        int prixFantassin = 10;
        int prixArcher = 12;
        int prixCatapulte = 20;
        int vieFantassin = 10;
        int vieArcher = 8;
        int vieCatapulte = 12;
        int attFantassin = 4;
        int attArcher = 3;
        int attCatapulte = 6;
        int portMinFantassin = 1;
        int portMinArcher = 1;
        int portMinCatapulte = 2;
        int porteeFantassin = 1;
        int porteeArcher = 3;
        int porteeCatapulte = 3;
        int zoneFantassin = 1;
        int zoneArcher = 1;
        int zoneCatapulte = 2;

        int vieJoueur = 100;
        int orParTour = 8;
        int limiteTour = 100;
        int tailleMap = 12;
    protected:
    private:
};

#endif // CONFIGURATION_H
