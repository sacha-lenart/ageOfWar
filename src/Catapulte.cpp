#include "../header/Catapulte.h"
#include "../header/Plateau.h"

#include <iostream>

// Constructeur d'une catapulte : p = prix, v = vie, a = attaque, pm = portéeMin, po = portée, z = zone, pl = plateau et j = joueur
Catapulte::Catapulte(int p, int v, int a, int pm, int po, int z, Plateau &pl, Joueur &j) : Soldat(p, v, a, pm, po, z, pl, j)
{

}

Catapulte::~Catapulte()
{
    std::cout << "  Destruction de Catapulte" << std::endl;
}

Catapulte::Catapulte() : Soldat()
{

}

void Catapulte::action1()
{
    attaquer();
}

void Catapulte::action2()
{

}

void Catapulte::action3()
{
    avancer();
}

void Catapulte::afficher(std::ostream& flux) const
{
	flux << "CATAPULTE : ";
}

// fonction appelé pour afficher une catapulte dans un plateau 
// (affichage différent de l'affichage normal)
void Catapulte::afficherDansPlateau(std::ostream &flux, int posCourante)
{
	if (position == posCourante) flux << "*CATAP*";
    else flux << " catap ";
}
