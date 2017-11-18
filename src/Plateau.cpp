#include "../header/Plateau.h"
#include "../header/Fantassin.h"
#include "../header/Archer.h"
#include "../header/Catapulte.h"
#include "../header/Soldat.h"
#include "../header/ValeurNegativeException.h"

#include <iostream>
#include <sstream>

// Constructeur du plateau ne nécessitant que la configuration du jeu
Plateau::Plateau(Configuration& conf)
{
    config = &conf;
    
    tour = 1;
    indiceCourant = -1;

    // On initialise le plateau de soldats
    plateau = new Soldat*[config->tailleMap];

    // initialisation du "terrain"
    for(int i=0;i<=config->tailleMap-1;i++)
        plateau[i]=nullptr;

    // ouverture du fichier annexe
    fichier.open ("etat_plateau.txt", std::ofstream::out);
    if(!fichier)
        std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
}

// Destructeur du plateau
Plateau::~Plateau()
{
    std::cout << "  Destruction de Plateau" << std::endl;
    // fermeture de fichier
    fichier.close();

    // On détruit tous les soldats
	for (int i=0; i<=config->tailleMap-1; i++) {
		if (plateau[i] != nullptr)
			delete plateau[i];
	}
}

// Permet d'arrêter la partie
void Plateau::terminer()
{
	fini = true;
}

bool Plateau::getFini()
{
	return fini;
}

Soldat** Plateau::getPlateau()
{
    return plateau;
}

std::ofstream& Plateau::getFichier()
{
    return fichier;
}

int Plateau::getTour()
{
    return tour;
}

void Plateau::incrementerTour()
{
    tour += 1;
}

int Plateau::getIndiceCourant() const
{
	return indiceCourant;
}

void Plateau::setIndiceCourant(int pos) throw (IndicePlateauException)
{
	if ((pos >= config->tailleMap) || (pos < -1)) // en position -1, l'indice courant n'est sur aucun soldat
		throw IndicePlateauException();
	else
		indiceCourant = pos;
}

// Fait faire l'action 1 à tous les soldats du joueur j dans le bon ordre
void Plateau::action1Joueur(Joueur& j)
{
    if(j.estJoueurA())
    {
        for(int i=0;i<config->tailleMap-1;i++)
        {
            if((plateau[i] != nullptr) && (plateau[i]->getJoueur()->estJoueurA()))
            {
                indiceCourant = i;
                plateau[i]->action1();
            }
        }
    }
    else
    {
        for(int i=config->tailleMap-1;i>0;i--)
        {
            if((plateau[i] != nullptr) && (!plateau[i]->getJoueur()->estJoueurA()))
            {
				indiceCourant = i;
                plateau[i]->action1();
            }
        }
    }
}

// Fait faire l'action 2 à tous les soldats du joueur j dans le bon ordre
void Plateau::action2Joueur(Joueur& j)
{
    if(j.estJoueurA())
    {
        for(int i=config->tailleMap-1;i>=0;i--)
        {
            if((plateau[i] != nullptr) && (plateau[i]->getJoueur()->estJoueurA()))
            {
                indiceCourant = i;
                plateau[i]->action2();
            }
        }
    }
    else
    {
        for(int i=0;i<=config->tailleMap-1;i++)
        {
            if((plateau[i] != nullptr) && (!plateau[i]->getJoueur()->estJoueurA()))
            {
				indiceCourant = i;
                plateau[i]->action2();
            }
        }
    }
}

// Fait faire l'action 3 à tous les soldats du joueur j dans le bon ordre
void Plateau::action3Joueur(Joueur& j)
{
    if(j.estJoueurA())
    {
        for(int i=config->tailleMap-1;i>=0;i--)
        {
            if((plateau[i] != nullptr) && (plateau[i]->getJoueur()->estJoueurA()))
            {
				indiceCourant = i;
                plateau[i]->action3();
            }
        }
    }
    else
    {
        for(int i=0;i<=config->tailleMap-1;i++)
        {
            if((plateau[i] != nullptr) && (!plateau[i]->getJoueur()->estJoueurA()))
            {
                indiceCourant = i;
                plateau[i]->action3();
            }
        }
    }
}

void Plateau::setJoueurA(Joueur& j)
{
    jG = &j;
}

void Plateau::setJoueurB(Joueur& j)
{
    jD = &j;
}

Joueur* Plateau::getJoueurA()
{
    return jG;
}

Joueur* Plateau::getJoueurB()
{
    return jD;
}

// Fonction de création d'une catapulte
void Plateau::creerCatapulte(Joueur& j)
{
    // position à laquelle faire apparaître la catapulte
    int pos = j.getPosTour();
    // getPosTour() ne peut renvoyer que 0 ou 11, pas la peine d'envoyer
    // une IndicePlateauException

    // on vérifie que la position est libre
    if(plateau[pos] == nullptr)
    {
        if(j.getArgent()>=config->prixCatapulte)
        {
			try { j.setArgent(j.getArgent()-config->prixCatapulte); /* déduction du coût */ }
			catch(ValeurNegativeException e) {cout << e.what() << endl;}
			// Nouvelle instance de catapulte créée avec les bons attributs
            plateau[pos] = new Catapulte(config->prixCatapulte, config->vieCatapulte, config->attCatapulte, config->portMinCatapulte, config->porteeCatapulte, config->zoneCatapulte, *this, j);
            std::string jo = j.estJoueurA() ? "A" : "B";
			std::cout << "        Joueur " << jo << " : creation de catapulte" << std::endl;
			fichier << "        Joueur " << jo << " : creation de catapulte" << std::endl;
			indiceCourant = pos;
			afficherConsoleEtPlateau();
        }
    }
}

// Fonction de création d'un fantassin
void Plateau::creerFantassin(Joueur& j)
{
    int pos = j.getPosTour();

    if(plateau[pos] == nullptr)
    {
        if(j.getArgent()>=config->prixFantassin)
        {
            try { j.setArgent(j.getArgent()-config->prixFantassin); }
			catch(ValeurNegativeException e) {cout << e.what() << endl;}
            plateau[pos] = new Fantassin (config->prixFantassin, config->vieFantassin, config->attFantassin, config->portMinFantassin, config->porteeFantassin, config->zoneFantassin, *this, j);
            std::string jo = j.estJoueurA() ? "A" : "B";
			std::cout << "        Joueur " << jo << " : creation de fantassin" << std::endl;
			fichier << "        Joueur " << jo << " : creation de fantassin" << std::endl;
			indiceCourant = pos;
			afficherConsoleEtPlateau();
        }
    }
}

// Fonction de création d'un archer
void Plateau::creerArcher(Joueur& j)
{
    int pos = j.getPosTour();

    if(plateau[pos] == nullptr)
    {
        if(j.getArgent()>=config->prixArcher)
        {
            try { j.setArgent(j.getArgent()-config->prixArcher); }
			catch(ValeurNegativeException e) {cout << e.what() << endl;}
            plateau[pos] = new Archer (config->prixArcher, config->vieArcher, config->attArcher, config->portMinArcher, config->porteeArcher, config->zoneArcher, *this, j);
            std::string jo = j.estJoueurA() ? "A" : "B";
			std::cout << "        Joueur " << jo << " : creation d'archer" << std::endl;
			fichier << "        Joueur " << jo << " : creation d'archer" << std::endl;
			indiceCourant = pos;
			afficherConsoleEtPlateau();
        }
    }
}

// retourne une chaine de caractère au format désiré pour l'affichage des points des bases
std::string afficherPointsBase(int pts) throw (ValeurNegativeException)
{
	if (pts<0)
		throw ValeurNegativeException();
	else {
		std::ostringstream oss;
		oss << pts;
		if (pts >= 100)
			return oss.str();
		else if (pts >= 10) {
			std::string s("___");
			s[2] = oss.str()[1];
			s[1] = oss.str()[0];
			return s;
		}
		else {
			std::string s("___");
			s[1] = oss.str()[0];
			return s;
		}
	}
}

std::ostream &operator<<(std::ostream &flux, Plateau const& p)
{
    flux << "____0";
    int i;
    for(i=1 ; i<p.getConf()->tailleMap-1;i++)
    {
        if(i<10)
            flux << "_______" << i;
        else
            flux << "______" << i;
    }
    flux << "______" << i << "___" << std::endl;


    flux << "|";
    if (p.plateau[0]==nullptr)
        flux << " baseA ";
    else
        p.plateau[0]->afficherDansPlateau(flux, p.getIndiceCourant());

    for (int i=1;i<=p.getConf()->tailleMap-2;i++) {
        flux << "|";
        if (p.plateau[i]==nullptr)
            flux << "       ";
        else
            p.plateau[i]->afficherDansPlateau(flux, p.getIndiceCourant());
    }

    flux << "|";
    if (p.plateau[p.getConf()->tailleMap-1]==nullptr)
        flux << " baseB ";
    else
        p.plateau[p.getConf()->tailleMap-1]->afficherDansPlateau(flux, p.getIndiceCourant());
    flux << "|" << std::endl;

    for (int i=0;i<=p.getConf()->tailleMap-1;i++) {
        flux << "|";
        if (p.plateau[i]==nullptr)
            flux << "       ";
        else
            p.plateau[i]->afficherCaract(flux);
    }
	flux << "|" << std::endl;
	try {
        flux << "|__" << afficherPointsBase(p.jG->getVie()) << "__";
        for(i=1 ; i<p.getConf()->tailleMap-1;i++)
        {
            flux << "|_______";
        }
        flux << "|__" << afficherPointsBase(p.jD->getVie()) << "__|" << std::endl;
    }
	catch (ValeurNegativeException e) {cout << e.what() << endl;}

    return flux;
}

void Plateau::afficherConsoleEtPlateau()
{
    std::cout << *this << std::endl;
    fichier << *this << std::endl;
}
