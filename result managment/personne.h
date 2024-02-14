#pragma once
#include <iostream>
using namespace std;
class personne
{
protected:
	string Nom;
	string Prenom;
	string Mail;
private:
	int ID;
	
public:
	personne() ;
	personne(int, string, string, string);
	//void afficherp();
	//void ajoutPerso();
	//void suppperso();
	//int getID() { return ID; }

};

