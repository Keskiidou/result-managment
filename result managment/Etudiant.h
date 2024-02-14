#pragma once
#include <iostream>
#include "personne.h"
using namespace std;
class Etudiant :
    public personne

{
    int Num_insc;
 
public:
    Etudiant();
    Etudiant(string,string,string, int);
    void afficheretu();
    void ajoutEtu();
    void suppetu();
    void updatetu();
    void updateField(int id, const std::string& field, const std::string& value);
};

