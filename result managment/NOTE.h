#pragma once
#include "Matiere.h"
#include "Etudiant.h"
#include<string>
#include <map>
class NOTE
{
	Matiere Mat;
	Etudiant Etu;
	float Note;
	string Type;
public:
	static map<int, string> TypeMap;
	NOTE();
	NOTE(Matiere,Etudiant,float,string);
	void afficherNot();



};

