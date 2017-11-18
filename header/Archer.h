#ifndef ARCHER_H
#define ARCHER_H

#include "Soldat.h"

class Archer : public Soldat
{
    public:
        Archer(int p, int v, int a, int pm, int po, int z, Plateau &pl, Joueur &j);
        ~Archer();
        void action1();
        void action2();
        void action3();
        void afficherDansPlateau(std::ostream& flux, int posCourante);
        void actionMort(Soldat &s){}
        void afficher(std::ostream& flux) const;
        //std::ostream& operator<<(std::ostream& flux);
    protected:
    private:
};

#endif // ARCHER_H
