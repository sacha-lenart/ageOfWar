#include "../header/Joueur.h"
#include "../header/Plateau.h"
#include "../header/Soldat.h"

#include <iostream>
#include <stdlib.h> // rand

// Constructeur du joueur IA : j = true si joueur A, false sinon. A = argent au d�but du jeu, v = vie de la base, p = plateau
Joueur::Joueur(bool j, int a, int v, Plateau& p)
{
    joueurA = j;
    argent = a;
    vie = v;
    plateau = &p;
}

Joueur::Joueur()
{

}

Joueur::~Joueur()
{
    std::cout << "  Destruction de Joueur" << std::endl;
}

// Cr�ation automatique d'une unit�, le choix de l'unit� cr��e se fait en fonction de l'argent du joueur d'une variable al�atoire
void Joueur::creerUnite()
{
    // On ne cr�e une unit� que si la partie n'est pas termin�e
	if(!plateau->getFini())
	{
		int nb_alea = rand() % 10; // nbre al�atoire entre 0 et 9

		if(argent >= plateau->getConf()->prixCatapulte) { // nous pouvons tout cr�er ici
			// dans ce cas, nous cr�ons forc�ment quelquechose
			if (nb_alea <= 1)
				creerFantassin();
			else if (nb_alea <= 3)
				creerArcher();
			else creerCatapulte();
		}
		else if(argent >= plateau->getConf()->prixArcher) { // nous pouvons cr�er archer et fantassin
			// dans les autres cas, nous pouvons economiser
			if (nb_alea <= 2)
				creerFantassin();
			else if (nb_alea <= 6)
				creerArcher();
		}
		else if(argent >= plateau->getConf()->prixFantassin) { // nous pouvons cr�er fantassin seulement
			if (nb_alea <= 4)
				creerFantassin();
		}
	}
}

void Joueur::setArgent(int ar) throw (ValeurNegativeException)
{
	if (ar < 0)
		throw ValeurNegativeException();
	else
		argent = ar;
}

int Joueur::getArgent()
{
    return argent;
}

bool Joueur::estJoueurA() const
{
    return joueurA;
}

// Inflige des d�gats au joueur
void Joueur::degat(int deg) throw (ValeurNegativeException)
{
	if (deg < 0)
		throw ValeurNegativeException();
	else {
		vie-=deg;
		vie = vie<=0 ? 0 : vie;
		std::string j;
		j = joueurA ? "Joueur A : " : "Joueur B : ";
		std::cout << "        " << *plateau->getPlateau()[plateau->getIndiceCourant()] << " : attaque ";
		std::cout << j << "perd " << deg << " pv. Reste " << vie << " pv" << std::endl;
		plateau->getFichier() << "        " << *plateau->getPlateau()[plateau->getIndiceCourant()] << " : attaque ";
		plateau->getFichier() << j << "perd " << deg << " pv. Reste " << vie << " pv" << std::endl;
		plateau->afficherConsoleEtPlateau();
		// Si le joueur n'a plus de vie, on termine la partie
		if(vie<=0)
		{
			plateau->terminer();
		}
	}
}

void Joueur::creerFantassin()
{
    plateau->creerFantassin(*this);
}

void Joueur::creerArcher()
{
    plateau->creerArcher(*this);
}

void Joueur::creerCatapulte()
{
    plateau->creerCatapulte(*this);
}

int Joueur::getPosTour()
{
    if(estJoueurA())
        return 0;
    else return plateau->getConf()->tailleMap-1;
}

std::ostream &operator<<(std::ostream &flux, Joueur const& j)
{
    if (j.joueurA)
        flux << "joueur A";
    else flux << "joueur B";
    return flux;
}
