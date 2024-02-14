#pragma once
#include<string>
#include <type_traits>
#include "Enseignant.h"
#include<sqlite3.h>
using namespace std;
class Matiere
{
    string iDMat;
    string NomMat;
    double Coef;
    Enseignant Ens;
public:
    Matiere();
    Matiere(string, string, double, Enseignant);

    void ajoutmatiere();
    void afficherMAt();
    template<typename T>
    void updateMatField(const string& id, const string& field, const T& value);
    void updateMat();
    void suppMat();
    string getIdmat() const {
        return iDMat;
    }

    
    void setIdmat(const string& id) {
        iDMat = id;
    }



};
    template<typename T>
    inline void Matiere::updateMatField(const string& id, const string& field, const T& value)
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


            if (field == "cnrp" && std::is_integral_v<T>) {
                std::string sqlQueryCheck = "SELECT COUNT(*) FROM Enseignant WHERE cnrps = ?";
                sqlite3_stmt* stmtCheck;
                rc = sqlite3_prepare_v2(db, sqlQueryCheck.c_str(), -1, &stmtCheck, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                    return;
                }
                // Bind the parameter to the statement
                if constexpr (std::is_same_v<T, int>) {
                    sqlite3_bind_int(stmtCheck, 1, value);
                }

                // Execute the statement
                rc = sqlite3_step(stmtCheck);
                if (rc != SQLITE_ROW) {
                    cout << "No enseignant found with CNRPS: " << value << endl;
                    sqlite3_finalize(stmtCheck);
                    sqlite3_close(db);
                    return;
                }
                sqlite3_finalize(stmtCheck);
            }
            // Prepare the SQL update statement
            std::string sqlQueryUpdate = "UPDATE Matiere SET " + field + " = ? WHERE idmat = ?";
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
                cout << "Matiere with ID " << id << "'s " << field << " updated successfully." << endl;
            }
            else {
                cout << "No matiere found with ID: " << id << "." << endl;
            }

            // Finalize statement and close database
            sqlite3_finalize(stmtUpdate);
            sqlite3_close(db);
        }
    }
