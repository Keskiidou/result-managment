#pragma once
#include <iostream>
#include "personne.h"
using namespace std;
class Enseignant:
    public personne
{
    int CNRPS;

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

