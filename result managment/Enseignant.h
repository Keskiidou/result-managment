#pragma once
#include <iostream>
using namespace std;
class Enseignant
{
    int CNRPS;
    string Nom;
    string Prenom;
    string Mail;
public:
    Enseignant();
    Enseignant(int, string, string, string);
    void ajoutens();
    void suppeens();
    void afficherens();
    void updatens();
    void updateEnsField(int id, const std::string& field, const std::string& value);
    int getCNRPS(){ return CNRPS; };
  
};

