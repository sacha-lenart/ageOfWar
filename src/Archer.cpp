#include "../header/Archer.h"
#include "../header/Plateau.h"

#include <iostream>
#include <ostream>

// Constructeur d'un archer : p = prix, v = vie, a = attaque, pm = port�eMin, po = port�e, z = zone, pl = plateau et j = joueur
Archer::Archer(int p, int v, int a, int pm, int po, int z, Plateau &pl, Joueur &j) : Soldat(p, v, a, pm, po, z, pl, j)
{

}

// Destructeur d'archer
Archer::~Archer()
{
    std::cout << "  Destruction d'Archer" << std::endl;
}

// L'archer attaque pour sa premi�re action
void Archer::action1()
{
    attaquer();
}

// L'archer avance pour sa deuxi�me action
void Archer::action2()
{
    avancer();
}

// L'archer n'a pas de troisi�me action
void Archer::action3()
{

}

void Archer::afficher(std::ostream& flux) const
{
	flux << "ARCHER : ";
}

// fonction appel� pour afficher un archer dans un plateau 
// (affichage diff�rent de l'affichage normal)
void Archer::afficherDansPlateau(std::ostream &flux, int posCourante)
{
	if (position == posCourante) flux << "*ARCHE*";
    else flux << " arche ";
}
