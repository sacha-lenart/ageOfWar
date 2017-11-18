#include "../header/Fantassin.h"
#include "../header/Plateau.h"

#include <iostream>

Fantassin::Fantassin(int p, int v, int a, int pm, int po, int z, Plateau &pl, Joueur &j) : Soldat(p, v, a, pm, po, z, pl, j)
{

}

Fantassin::Fantassin() : Soldat()
{

}

Fantassin::~Fantassin()
{
    std::cout << "  Destruction de Fantassin" << std::endl;
}

void Fantassin::actionMort(Soldat &s)
{
	s.setSuperSoldat();
}

void Fantassin::setSuperSoldat()
{
	super = true;
}

void Fantassin::action1()
{
    attaquer();
}

void Fantassin::action2()
{
    avancer();
}

void Fantassin::action3()
{
	if(super)
        attaquer();
	else
		if(!aAttaque) attaquer();
}

void Fantassin::afficher(std::ostream& flux) const
{
	if (!super)
        flux << "FANTASSIN : ";
    else flux << "SUPER-SOLDAT : ";
}

// fonction appelé pour afficher un fantassin ou super-soldat dans un plateau 
// (affichage différent de l'affichage normal)
void Fantassin::afficherDansPlateau(std::ostream &flux, int posCourante)
{
    if (!this->super) {
		if (position == posCourante)
			flux << "*FANTA*";
		else flux << " fanta ";
	}
    else {
		if (position == posCourante)
			flux << "*SUPER*";
		else flux << " super ";
	}
}
