#include "../header/Soldat.h"
#include "../header/Fantassin.h"
#include "../header/Plateau.h"
#include "../header/IndicePlateauException.h"
#include "../header/ValeurNegativeException.h"

#include <iostream>
#include <sstream>

Soldat::Soldat(int p, int v, int a, int pm, int po, int z, Plateau& pl, Joueur& j)
{
    prix = p;
    vie = v;
    att = a;
    portee = po;
    zone = z;
    plateau = &pl;
    joueur = &j;
    porteeMin = pm;
    if(joueur->estJoueurA())
    {
        position = 0;
    }
    else
    {
        position = plateau->getConf()->tailleMap-1;
    }
}

int Soldat::getPos()
{
    return position;
}

int Soldat::getPrix()
{
    return prix;
}

Soldat::Soldat()
{

}

Soldat::~Soldat()
{

}

Joueur* Soldat::getJoueur()
{
    return joueur;
}

int Soldat::getAtt()
{
	return att;
}

// Permet d'infliger des dégats au soldat. Le paramètre correspond au soldat qui fait les dégats
void Soldat::degat(Soldat& s)
{
	std::cout << "        " << s << " : attaque " << *this << std::endl;
	plateau->getFichier() << "        " << s << " : attaque " << *this << std::endl;
    vie -= s.getAtt();
    if(vie <= 0)
    {
		std::cout << "              -->"; // affichage du destructeur
        plateau->getPlateau()[position] = nullptr;
        try { s.getJoueur()->setArgent(s.getJoueur()->getArgent()+(prix/2)); }
		catch(ValeurNegativeException e) {cout << e.what() << endl;}
        actionMort(s);
        delete this;
    }
    plateau->afficherConsoleEtPlateau();
}

// Fonction générique à tous les soldats leur permettant d'avancer sur le plateau
void Soldat::avancer()
{
	if(!plateau->getFini())
	{
		if(joueur->estJoueurA())
		{
			if((plateau->getPlateau()[position+1]==nullptr) && (position+1 <= 10))
			{
				std::cout << "        " << *this << " : avance" << std::endl;
				plateau->getFichier() << "        " << *this << " : avance" << std::endl;
				plateau->getPlateau()[position] = nullptr;
				plateau->getPlateau()[position+1] = &(*this);
				if (plateau->getIndiceCourant() == position) {
					try {
						plateau->setIndiceCourant(position+1);
					} catch(IndicePlateauException e) {
						cout << e.what() << endl;
					}
				}
				position++;
				plateau->afficherConsoleEtPlateau();
			}
		}
		else
		{
			if((plateau->getPlateau()[position-1]==nullptr) && (position-1 >= 1))
			{
				std::cout << "        " << *this << " : avance" << std::endl;
				plateau->getFichier() << "        " << *this << " : avance" << std::endl;
				plateau->getPlateau()[position] = nullptr;
				plateau->getPlateau()[position-1] = &(*this);
				if (plateau->getIndiceCourant() == position) {
					try {
						plateau->setIndiceCourant(position-1);
					} catch(IndicePlateauException e) {
						cout << e.what() << endl;
					}
				}
				position--;
				plateau->afficherConsoleEtPlateau();
			}
		}
	}
}

// Fonction générique aux soldats leur permettant d'attaquer leurs ennemis
void Soldat::attaquer()
{
    // Le soldat n'attaque pas si la partie est finie
	if(!plateau->getFini())
	{
	    // Cas où le soldat appartient au joueur a
		if(joueur->estJoueurA())
		{
			// on vérifie que l'on ne va pas dépasser les bornes du tableau
			int lim_i = position+portee+zone;
			if (lim_i > plateau->getConf()->tailleMap) lim_i = plateau->getConf()->tailleMap;
			int debut_i = position+porteeMin;
			if (debut_i > plateau->getConf()->tailleMap-1) debut_i = plateau->getConf()->tailleMap-1;

            // debut_i vaut position + porteeMin. Il s'agit de la première position où le soldat peut espérer attaquer
			for(int i=debut_i;i<lim_i;i++)
			{
			    // On regarde si la position scrutée est occupée par un ennemi
				if((plateau->getPlateau()[i]!=nullptr) && !(plateau->getPlateau()[i]->getJoueur()->estJoueurA()))
				{
				    // Cas où la zone n'est pas encore prise en compte
					if(i<=position+portee)
					{
						int lim_j = i+zone;
						if (lim_j >= plateau->getConf()->tailleMap) lim_j = plateau->getConf()->tailleMap;
						for(int j=i;j<lim_j;j++)
						{
							if((j==plateau->getConf()->tailleMap-1) && (plateau->getPlateau()[j]==nullptr)){
                                // On attaque le joueur
								try {plateau->getJoueurB()->degat(att);}
								catch (ValeurNegativeException e) {cout << e.what() << endl;}
							}
							else if (plateau->getPlateau()[j] != nullptr) {
							    // On attaque l'ennemi
								plateau->getPlateau()[j]->degat(*this);
							}
						}
						return;
					}
					// Cas où la zone est prise en compte
					else
					{
						int lim_j = position+portee+zone;
						if (lim_j >= plateau->getConf()->tailleMap) lim_j = plateau->getConf()->tailleMap;
						int debut_j = position+portee;
						if (debut_j > plateau->getConf()->tailleMap-1) debut_j = plateau->getConf()->tailleMap-1;
						else if (debut_j < position+1) debut_j = position+1;
						// On attaque tous les soldats à portée
						for(int j=debut_j;j<lim_j;j++)
						{
							if((j==plateau->getConf()->tailleMap-1) && (plateau->getPlateau()[j]==nullptr)){
								try {plateau->getJoueurB()->degat(att);}
								catch (ValeurNegativeException e) {cout << e.what() << endl;}
							}
							else if (plateau->getPlateau()[j] != nullptr) {
								plateau->getPlateau()[j]->degat(*this);
							}
						}
					}
				}
				// On vérifie si on touche un joueur
				else if((i==plateau->getConf()->tailleMap-1) && (plateau->getPlateau()[i]==nullptr))
				{
					try {plateau->getJoueurB()->degat(att);}
					catch (ValeurNegativeException e) {cout << e.what() << endl;}
				}
			}
		}
		else // Identique au "if" du dessus mais avec les positions opposées
		{
			int lim_i = position-portee-zone;
			if (lim_i < -1) lim_i = -1;
			int debut_i = position-porteeMin;
			if (debut_i < 0) debut_i = 0;

			for(int i=debut_i;i>lim_i;i--)
			{
				if((plateau->getPlateau()[i]!=nullptr) && (plateau->getPlateau()[i]->getJoueur()->estJoueurA()))
				{
					if(i>=position-portee)
					{
						int lim_j = i-zone;
						if (lim_j <= -1) lim_j = -1;
						for(int j=i;j>lim_j;j--)
						{
							if((j==0) && (plateau->getPlateau()[j]==nullptr)){
								try {plateau->getJoueurA()->degat(att);}
								catch (ValeurNegativeException e) {cout << e.what() << endl;}
							}
							else if (plateau->getPlateau()[j] != nullptr) {
								plateau->getPlateau()[j]->degat(*this);
							}
						}
						return;
					}
					else
					{
						int lim_j = position-portee-zone;
						if (lim_j <= -1) lim_j = -1;
						int debut_j = position-portee;
						if (debut_j < 0) debut_j = 0;
						else if (debut_j > (position-1)) debut_j = position-1;
						for(int j=debut_j;j>lim_j;j--)
						{
							if((j==0) && (plateau->getPlateau()[j]==nullptr)){
								try {plateau->getJoueurA()->degat(att);}
								catch (ValeurNegativeException e) {cout << e.what() << endl;}
							}
							else if (plateau->getPlateau()[j] != nullptr) {
								plateau->getPlateau()[j]->degat(*this);
							}
						}
					}

				}
				else if((i==0) && (plateau->getPlateau()[i]==nullptr))
				{
					try {plateau->getJoueurA()->degat(att);}
					catch (ValeurNegativeException e) {cout << e.what() << endl;}
				}
			}
		}
	}
}


int Soldat::getVie()
{
    return vie;
}

std::string intPosToString2(int i) throw (ValeurNegativeException) {
	if (i<0)
		throw ValeurNegativeException();
	else {
		std::ostringstream oss;
		oss << i;
		if (i >= 10)
			return oss.str();
		else {
			std::string s("00");
			s[1] = oss.str()[0];
			return s;
		}
	}
}

void Soldat::afficherCaract(std::ostream& flux) const
{
    if (joueur->estJoueurA())
        flux << " A  ";
    else
        flux << " B  ";
    try { flux << intPosToString2(vie); }
    catch (ValeurNegativeException e) {cout << e.what() << endl;}
    flux << " ";
}

std::ostream& operator<<(std::ostream &flux, Soldat const& s)
{
    s.afficher(flux);
	flux << *s.joueur <<  ", pos:" << s.position;
    return flux;
}
