#ifndef FANTASSIN_H
#define FANTASSIN_H

#include "Soldat.h"

class Fantassin : public Soldat
{
    public:
        Fantassin(int p, int v, int a, int pm, int po, int z, Plateau &pl, Joueur &j);
        Fantassin();
        ~Fantassin();
        void action1();
        void action2();
        void action3();
        void actionMort(Soldat& s);
        void setSuperSoldat();
        void afficher(std::ostream& flux) const;
        void afficherDansPlateau(std::ostream& flux, int posCourante);
    protected:
    private:
        bool super = false;
        bool aAttaque = false;
};

#endif // FANTASSIN_H
