#ifndef CATAPULTE_H
#define CATAPULTE_H

#include "Soldat.h"

class Catapulte : public Soldat
{
    public:
        Catapulte(int p, int v, int a, int pm, int po, int z, Plateau &pl, Joueur &j);
        Catapulte();
        ~Catapulte();
        void action1();
        void action2();
        void action3();
        void actionMort(Soldat &s){}
        void afficherDansPlateau(std::ostream& flux, int posCourante);
        void afficher(std::ostream& flux) const;
        
    protected:
    private:
};

#endif // CATAPULTE_H
