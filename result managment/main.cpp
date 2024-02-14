#include <iostream>
#include "personne.h"
#include "Etudiant.h"
#include "Enseignant.h"
#include "Matiere.h"
#include "GroupeModule.h"
#include "Groupe.h"
#include "NOTE.h"
#include <sqlite3.h>
#include<string>
using namespace std;
int main() {

	//personne P1;
	//P1.ajoutPerso();
	//P1.afficherp();
	//P1.suppperso();
	Etudiant E1;
	//E1.ajoutEtu();
	E1.afficheretu();
	//E1.suppetu();
	//E1.updatetu();
	Enseignant E2;
	//E2.ajoutens();
	E2.afficherens();
	//E2.updatens();
	//E2.afficherens();
	Matiere M1;
	//M1.ajoutmatiere();
	M1.afficherMAt();
	//M1.updateMat();
	//M1.suppMat();
	GroupeModule GM1;
	//GM1.ajoutGM();
	GM1.afficherGM();
	//GM1.updateGM();
	//GM1.suppGM();
	//GM1.afficherGM();
	return 0;
	


}
