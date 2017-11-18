#ifndef PLATEAU_H
#define PLATEAU_H

#include "IndicePlateauException.h"
#include "Configuration.h"

#include <ostream>
#include <fstream> // ofstream

class Joueur;
class Soldat;

class Plateau
{
    public:
        Plateau(Configuration& conf);
        virtual ~Plateau();
        void creerFantassin(Joueur& j);
        void creerArcher(Joueur& j);
        void creerCatapulte(Joueur& j);
        Soldat** getPlateau();
        void setJoueurA(Joueur& j);
        void setJoueurB(Joueur& j);
        void action1Joueur(Joueur& j);
        void action2Joueur(Joueur& j);
        void action3Joueur(Joueur& j);
        Joueur* getJoueurA();
        Joueur* getJoueurB();
        std::ofstream& getFichier();
        void afficherConsoleEtPlateau();
        int getTour();
        void incrementerTour();
        int getIndiceCourant() const;
        void setIndiceCourant(int pos) throw (IndicePlateauException);
        void terminer();
        bool getFini();
        Configuration* getConf() const { return config; }
    protected:
    private:
        Configuration* config;
        Soldat** plateau;
        Joueur* jG;
        Joueur* jD;
        std::ofstream fichier;
        int tour;
        int indiceCourant;
        bool fini = false;

        friend std::ostream& operator<<(std::ostream& flux, Plateau const& p);
};

#endif // PLATEAU_H
