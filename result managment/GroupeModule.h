#pragma once
#include"Matiere.h"
#include<string>
#include <vector>
class GroupeModule
{
	string IdGM;
	string NomGM;
	double CoefGM;
	vector<Matiere> ListeMat;
public:
	GroupeModule();
	GroupeModule(string, string, double, vector<Matiere>);
	bool idmatExists(string idm);
	void ajoutGM();
	void afficherGM();
	void updateGM();
	template<typename T>
	void updateGField(const string& id, const string& field, const T& value);	
    template<typename T>
	void updateGMMField(const string& id, const string& field, const T& value);
    void suppGM();


};

template<typename T>
inline void GroupeModule::updateGField(const string& id, const string& field, const T& value)
{
    sqlite3* db;
    char* errMsg = nullptr;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    else {
        std::cout << "Opened database successfully" << std::endl;

        // Set UTF-8 encoding
        sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);
    }

    // Prepare the SQL update statement
    std::string sqlQueryUpdate = "UPDATE GroupeModule SET " + field + " = ? WHERE IdGM = ?";
    sqlite3_stmt* stmtUpdate;
    rc = sqlite3_prepare_v2(db, sqlQueryUpdate.c_str(), -1, &stmtUpdate, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    // Bind the parameters to the statement
    if constexpr (std::is_same_v<T, std::string>) {
        sqlite3_bind_text(stmtUpdate, 1, value.c_str(), -1, SQLITE_STATIC);
    }
    else if constexpr (std::is_same_v<T, double>) {
        sqlite3_bind_double(stmtUpdate, 1, value);
    }
    else if constexpr (std::is_same_v<T, int>) {
        sqlite3_bind_int(stmtUpdate, 1, value);
    }
    sqlite3_bind_text(stmtUpdate, 2, id.c_str(), -1, SQLITE_STATIC);

    // Execute the statement
    rc = sqlite3_step(stmtUpdate);
    if (sqlite3_changes(db) > 0) {
        cout << "Group module with ID " << id << "'s " << field << " updated successfully." << endl;
    }
    else {
        cout << "No group module found with ID: " << id << "." << endl;
    }

    // Finalize statement and close database
    sqlite3_finalize(stmtUpdate);
    sqlite3_close(db);
}

template<typename T>
inline void GroupeModule::updateGMMField(const string& id, const string& field, const T& value)
{
    sqlite3* db;
    char* errMsg = nullptr;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    else {
        cout << "Opened database successfully" << endl;

        // Set UTF-8 encoding
        sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);

        // Prepare the SQL update statement
        std::string sqlQueryUpdate = "UPDATE GroupeModule_Matiere SET " + field + " = ? WHERE idmat = ?";
        sqlite3_stmt* stmtUpdate;
        rc = sqlite3_prepare_v2(db, sqlQueryUpdate.c_str(), -1, &stmtUpdate, nullptr);
        if (rc != SQLITE_OK) {
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return;
        }

        // Bind the parameters to the statement
        if constexpr (std::is_same_v<T, std::string>) {
            sqlite3_bind_text(stmtUpdate, 1, value.c_str(), -1, SQLITE_STATIC);
        }
        else if constexpr (std::is_same_v<T, double>) {
            sqlite3_bind_double(stmtUpdate, 1, value);
        }
        else if constexpr (std::is_same_v<T, int>) {
            sqlite3_bind_int(stmtUpdate, 1, value);
        }
        sqlite3_bind_text(stmtUpdate, 2, id.c_str(), -1, SQLITE_STATIC);

        // Execute the statement
        rc = sqlite3_step(stmtUpdate);
        if (sqlite3_changes(db) > 0) {
            cout << "GroupeModule_Matiere with ID " << id << "'s " << field << " updated successfully." << endl;
        }
        else {
            cout << "No GroupeModule_Matiere found with ID: " << id << "." << endl;
        }

        // Finalize statement and close database
        sqlite3_finalize(stmtUpdate);
        sqlite3_close(db);
    }
}