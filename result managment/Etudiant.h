#pragma once
#include <iostream>
using namespace std;
class Etudiant 
{
    int Num_insc;
    string Nom;
    string Prenom;
    string Mail;
public:
    Etudiant();
    Etudiant(int,string,string,string);
    void afficheretu();
    void ajoutEtu();
    void suppetu();
    void updatetu();
    void updateField(int id, const std::string& field, const std::string& value);
};

