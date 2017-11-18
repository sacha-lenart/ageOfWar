#ifndef HUMAIN_H
#define HUMAIN_H

#include "Joueur.h"
#include <string>

class Humain : public Joueur
{
	public:
		Humain();
		Humain(bool j, int a, int v, Plateau& p, std::string n);
		virtual ~Humain(){}
		void creerUnite();
	private:
		std::string nom;
};

#endif // HUMAIN_H
