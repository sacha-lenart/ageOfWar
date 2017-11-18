#ifndef JOUEUR_H
#define JOUEUR_H

#include <ostream>
#include <fstream>

#include "ValeurNegativeException.h"

class Plateau;

class Joueur
{
    public:
        Joueur();
        Joueur(bool j, int a, int v, Plateau& p);
        virtual ~Joueur();
        void setArgent(int ar) throw (ValeurNegativeException);
        int getArgent();
        void creerFantassin();
        bool estJoueurA() const;
        void creerCatapulte();
        int getPosTour();
        int getVie(){return vie;}
        void creerArcher();
        void degat(int deg) throw (ValeurNegativeException);
        
        virtual void creerUnite();
    protected:
        Plateau* plateau;
        int argent;
        bool joueurA; // true si joueur A, false si joueur B;
        int vie;
        friend std::ostream& operator<<(std::ostream& flux, Joueur const& j);
    private:

};

#endif // JOUEUR_H
