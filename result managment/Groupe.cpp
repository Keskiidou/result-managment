#include "Groupe.h"

map<int, string> Groupe::NiveauMap{ {1, "Premiere"}, {2, "deuxieme"}, {3, "troisieme"}, {4, "quatrieme"} };
map<int, string> Groupe::DiplomeMap{ {1, "ING"}, {2, "MASTER"}, {3, "LMD"} };
map<int, string> Groupe::SpecialiteMap{ {1, "INF"}, {2, "INDUS"}, {3, "MATH"} };
map<int, int> Groupe::Num_GMap{ {1, 1}, {2, 2}, {3, 3} };
Groupe::Groupe() : IdGRP(""), Niveau(""), Diplome(""), Specialite(""), Num_G(1), ListeModules(), ListeEtudiants() {}
Groupe::Groupe(string id, string niveau, string diplome, string specialite, int numG, vector<GroupeModule> modules, vector<Etudiant> etudiants) : IdGRP(id), Niveau(niveau), 
Diplome(diplome), Specialite(specialite), Num_G(numG),
ListeModules(modules), ListeEtudiants(etudiants){}
void Groupe::afficherGRP()
{
	//cout << "l'ID du groupe  : " << IdGRP << endl;
	//cout << "le niveau du groupe est  : " << Niveau << endl;
	//cout << "le diplome est  : " << Diplome << endl;
	//cout << "la specialité est  : " << Specialite << endl;
	//cout << "le numero du group est  : " << Num_G << endl;
	//for (size_t i = 0; i < ListeModules.size(); i++)
	//{
	//	ListeModules[i].affichergrpm();
	//
	//}	
	//for (size_t i = 0; i < ListeEtudiants.size(); i++)
	//{
	//	ListeEtudiants[i].afficheretu();
	//
	//}
}

void Groupe::ajoutGR()
{
    // Open the database connection
    sqlite3* db;
    char* errMsg = nullptr;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return;
    }
    else {
        cout << "Opened database successfully" << endl;

        // Set UTF-8 encoding
        sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);
    }
    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Groupe ("
        "IdGRP TEXT PRIMARY KEY,"
        "Niveau TEXT NOT NULL COLLATE NOCASE,"
        "Diplome TEXT NOT NULL COLLATE NOCASE,"
        "Specialite TEXT NOT NULL COLLATE NOCASE,"
        "NumG INTEGER NOT NULL COLLATE NOCASE)";
    rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error creating Matiere table: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return;
    }
    else {
        cout << "Table created successfully" << endl;
    }
    const char* sqlCreateGroupeModule_MatiereTable = "CREATE TABLE IF NOT EXISTS Groupe_GM_Etudiant ("
        "IdG TEXT,"
        "IdGm TEXT,"
        "numinsc INTEGER,"
        "PRIMARY KEY (IdG, IdGM,num_insc),"
        "FOREIGN KEY (IdG) REFERENCES Groupe(IdGRP),"
        "FOREIGN KEY (IdGm) REFERENCES GroupeModule(IdGM)"
        "FOREIGN KEY (numinsc) REFERENCES Etudiant(num_insc)"
        ");";   
    rc = sqlite3_exec(db, sqlCreateGroupeModule_MatiereTable, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "GroupeModule_Matiere table created successfully" << endl;
    }
}
