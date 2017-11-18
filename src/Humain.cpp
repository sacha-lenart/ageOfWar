#include "../header/Humain.h"
#include "../header/Plateau.h"

#include <iostream>
#include <cstdlib>

using namespace std;

Humain::Humain() : Joueur()
{

}

// Le joueur humain poss�de les m�mes attributs que le joueur IA mais dispose en plus d'un nom
Humain::Humain(bool j, int a, int v, Plateau& p, std::string n) : Joueur(j, a, v, p)
{
	nom = n;
}

// Fonction qui demande au joueur quelle unit� il souhaite cr�er et la cr�e
void Humain::creerUnite()
{
    string choix;
    bool fini = false;
    ostream stream(nullptr);

    while(!fini){
        cout << "    " << nom << ", quelle unite souhaitez-vous creer ? Vous avez " << argent << " d'or\n"
        << "      1. Fantassin " << "(" << plateau->getConf()->prixFantassin << " d'or) \n"
        << "      2. Archer " << "(" << plateau->getConf()->prixArcher << " d'or) \n"
        << "      3. Catapulte " << "(" << plateau->getConf()->prixCatapulte << " d'or) \n"
        << "      4. Aucune\n    ";

        cin >> choix;

        // Si la saisie est incorrecte
        while(choix != "1" && choix != "2" && choix != "3" && choix != "4")
        {
            cout << "    Saisie incorrecte ! " << nom << ", quelle unite souhaitez-vous creer ? Vous avez " << argent << " d'or\n"
            << "      1. Fantassin " << "(" << plateau->getConf()->prixFantassin << " d'or) \n"
            << "      2. Archer " << "(" << plateau->getConf()->prixArcher << " d'or) \n"
            << "      3. Catapulte " << "(" << plateau->getConf()->prixCatapulte << " d'or) \n"
            << "      4. Aucune\n    ";

            cin >> choix;
        }

        int choixN = atoi(choix.c_str());

        // On v�rifie que le joueur a assez d'argent, sinon on lui redemande
        switch(choixN)
        {
        case 1 :
            if(argent >= plateau->getConf()->prixFantassin)
            {
                fini = true;
                creerFantassin();
            }
            else
                cout << "    Pas assez d'argent !\n";
            break;
        case 2 :
            if(argent >= plateau->getConf()->prixArcher)
            {
                fini = true;
                creerArcher();
            }
            else
                cout << "    Pas assez d'argent !\n";
            break;
        case 3:
            if(argent >= plateau->getConf()->prixCatapulte)
            {
                fini = true;
                creerCatapulte();
            }
            else
                cout << "    Pas assez d'argent !\n";
            break;
        case 4 :
            fini = true;
        }
    }


}
