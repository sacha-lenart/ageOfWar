#ifndef SOLDAT_H
#define SOLDAT_H

#include "Joueur.h"

#include <ostream>

class Plateau;

class Soldat
{
    public:
        Soldat();
        Soldat(int p, int v, int a, int pm, int po, int z, Plateau& pl, Joueur& j);
        virtual ~Soldat();
        virtual void action1() = 0;
        virtual void action2() = 0;
        virtual void action3() = 0;
        void attaquer();
        Joueur* getJoueur();
        void degat(Soldat &s);
        void avancer();
        int getPos();
        int getVie();
        int getPrix();
        int getAtt();
        virtual void setSuperSoldat(){}
        virtual void actionMort(Soldat& s) = 0;
        
        virtual void afficherDansPlateau(std::ostream& flux, int posCourante) = 0;
        friend std::ostream& operator <<(std::ostream& flux, Soldat const& s); 
        virtual void afficher(std::ostream& flux) const = 0;
		void afficherCaract(std::ostream &flux) const;
     
    protected:
        int prix;
        int vie;
        int att;
        int portee;
        int porteeMin;
        int zone;
        Plateau* plateau;
        Joueur* joueur;
        int position = -1;

    private:

};

#endif // SOLDAT_H
