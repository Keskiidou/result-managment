#include "Matiere.h"
#include <sqlite3.h>
#include <string>
#include <type_traits>

using namespace std;

Matiere::Matiere() : iDMat(""), NomMat(""), Coef(0.0), Ens() {}

Matiere::Matiere(string idmat, string nomat, double coef, Enseignant ens) : iDMat(idmat), NomMat(nomat), Coef(coef), Ens(ens) {}

void Matiere::ajoutmatiere() {
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

    

    // Input prompts for subject details
    cout << "Enter the ID of the subject: ";
    cin >> iDMat;
    cout << "Enter the name of the subject: ";
    cin >> NomMat;
    cout << "Enter the coefficient of the subject: ";
    cin >> Coef;

    
    int getcnrps;
    cout << "Enter the CNRPS of the enseignant: ";
    cin >> getcnrps;


    const char* sqlQueryData = "SELECT cnrps FROM Enseignant WHERE cnrps = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }
    // Bind the parameter to the statement
    sqlite3_bind_int(stmt, 1, getcnrps);
    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        cout << "Enseignant with CNRPS " << getcnrps << " exists" << endl;
    }
    else if (rc == SQLITE_DONE) {
        cout << "Enseignant with CNRPS " << getcnrps << " does not exist." << endl;
    }
    else {
        cerr << "Error fetching data: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    // SQL statement to create the Matiere table
    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Matiere ("
        "idmat TEXT PRIMARY KEY,"
        "nommat TEXT NOT NULL COLLATE NOCASE,"
        "coef REAL NOT NULL COLLATE NOCASE,"
        "cnrp INTEGER NOT NULL COLLATE NOCASE,"
        "FOREIGN KEY (cnrp) REFERENCES Enseignant(cnrps)"
        ");";


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
    
    const char* sqlInsertData = "INSERT INTO Matiere (idmat, nommat, coef, cnrp) VALUES ('%s', '%s', %f, %d);";
    char sql[300];

    snprintf(sql, sizeof(sql), sqlInsertData, iDMat.c_str(), NomMat.c_str(), Coef, getcnrps);


    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Data Inserted successfully" << std::endl;
    }

 

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Matiere::afficherMAt()
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

        const char* sqlQueryData = "SELECT * FROM Matiere;";
        sqlite3_stmt* stmt;

        int rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;

            sqlite3_close(db);
            return;
        }

        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            const unsigned char* idM = sqlite3_column_text(stmt, 0);
            const unsigned char* nameM = sqlite3_column_text(stmt, 1);
            double CoefM = sqlite3_column_double(stmt, 2);
            int cnrps = sqlite3_column_int(stmt, 3);
            

            std::cout << "IDMat: " << (idM ? reinterpret_cast<const char*>(idM) : "NULL")
                << ", NomMat: " << (nameM ? reinterpret_cast<const char*>(nameM) : "NULL")
                << ", Coef: " << CoefM
                << ", CNRPS: " << cnrps << std::endl;
        }


        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
}
void Matiere::updateMat()
{
    string idMat;
    cout << "donner idMat pour modifier: ";
    cin >> idMat;

    int choice;
    cout << "What do you want to update?" << endl;
    cout << "1. Nom mat" << endl;
    cout << "2. Coef" << endl;
    cout << "3. ens" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    string newValue;
    switch (choice) {
    case 1:
        cout << "Enter the new nommat: ";
        cin >> newValue;
        updateMatField(idMat, "nommat", newValue);
        break;
    case 2:
        cout << "Enter the new coef: ";
        cin >> newValue;
        updateMatField(idMat, "coef", newValue);
        break;
    case 3:
        cout << "Enter the new cnrp: ";
        cin >> newValue;
        updateMatField(idMat, "cnrp", newValue);
        break;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
}

void Matiere::suppMat()
{
    string IdM_del;
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


        cout << "donner le id de matiere  que vous voulez le supprimer " << endl;
        cin >> IdM_del;


        const char* sqlQueryData = "DELETE FROM Matiere where idmat=?;";
        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return;
        }
        // Bind the parameter to the statement
        sqlite3_bind_text(stmt, 1, IdM_del.c_str(), -1, SQLITE_TRANSIENT);
        // Execute the statement
        rc = sqlite3_step(stmt);

        if (sqlite3_changes(db) > 0) {
            cout << "matiere  " << IdM_del << " deleted successfully." << endl;
        }
        else {
            cout << "No matiere  found with idmat  " << IdM_del << "." << endl;
        }

    }
}

