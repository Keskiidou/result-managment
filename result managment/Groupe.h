#pragma once
#ifndef GROUPE_H
#define GROUPE_H
#include "GroupeModule.h"
#include "Etudiant.h"
#include<string>
#include <vector>
#include <map>
class Groupe
{
	string IdGRP;
	string Niveau;
	string Diplome;
	string Specialite;
	int Num_G;
	vector <GroupeModule> ListeModules;
	vector <Etudiant> ListeEtudiants;



public:
	static map<int, string> NiveauMap;
	static map<int, string> DiplomeMap;
	static map<int, string> SpecialiteMap;
	static map<int, int> Num_GMap;

	Groupe();
	Groupe(string, string, string, string, int, vector <GroupeModule>, vector <Etudiant>);
	void afficherGRP();
	void ajoutGR();
};


#endif 