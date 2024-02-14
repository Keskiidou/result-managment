#include "NOTE.h"
map<int, string> NOTE::TypeMap{ {1, "DS"}, {2, "EXAMEN"}, {3, "TP"} };
NOTE::NOTE():Mat(), Etu(),Note(0.0),Type(""){}
NOTE::NOTE(Matiere matiere, Etudiant etudiant, float note, string type) :Mat(matiere), Etu(etudiant), Note(note), Type(type) {}

void NOTE::afficherNot()
{
	//Mat.affichermat();
	//Etu.afficheretu();
	cout << "votre note est " << Note << endl;
	cout << "le type d'epreuve est  " << Type << endl;
}
