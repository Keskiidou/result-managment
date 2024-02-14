#include "GroupeModule.h"
#include <type_traits>

GroupeModule::GroupeModule():IdGM(""), NomGM(""), CoefGM(0.0), ListeMat(){}
GroupeModule::GroupeModule(string idgm, string nomgm, double coefgm, vector<Matiere> listemat) : IdGM(idgm), NomGM(nomgm), CoefGM(coefgm), ListeMat({ listemat }) {}

bool GroupeModule::idmatExists(string idm)
{
    // Open the database connection
    sqlite3* db;
    char* errMsg = nullptr;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return false ;
    }
    else {
        cout << "Opened database successfully" << endl;

        // Set UTF-8 encoding
        sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);
    }
    const char* sqlQueryData = "SELECT idmat FROM Matiere WHERE idmat = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false ;
    }
    // Bind the parameter to the statement
    sqlite3_bind_text(stmt, 1, idm.c_str(), -1, SQLITE_TRANSIENT);
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE && rc != SQLITE_ROW) {
        cerr << "Error executing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db); 
        return false;
    }

    bool exists = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db); 
    return exists;
}

void GroupeModule::ajoutGM()
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
    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS GroupeModule ("
        "IdGM TEXT PRIMARY KEY,"
        "NomGM TEXT NOT NULL COLLATE NOCASE,"
        "CoefGM REAL NOT NULL COLLATE NOCASE);";
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

    const char* sqlCreateGroupeModule_MatiereTable = "CREATE TABLE IF NOT EXISTS GroupeModule_Matiere ("
        "IdGM TEXT,"
        "idmat TEXT,"
        "PRIMARY KEY (IdGM, idmat),"
        "FOREIGN KEY (IdGM) REFERENCES GroupeModule(IdGM),"
        "FOREIGN KEY (idmat) REFERENCES Matiere(idmat)"
        ");";
    rc = sqlite3_exec(db, sqlCreateGroupeModule_MatiereTable, nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "GroupeModule_Matiere table created successfully" << endl;
    }

    cout << "donner le id du groupe module :  " << endl;
    cin >> IdGM;
    cout << "donner le nom de group module : " << endl;
    cin >> NomGM;
    cout << "donner la coefficient  de group module : " << endl;
    cin >> CoefGM;
     
    string idm;
    while (true) {
        cout << "Enter idmat (or type 'done' to finish): ";
        cin>> idm;
        if (idm == "done") break;
        if (idmatExists( idm)) {
            Matiere matiere;
            matiere.setIdmat(idm);
            ListeMat.push_back(matiere);
        }
        else {
            cout << "Invalid idmat! Please enter a valid idmat." << endl;
        }
    }
    string sqlInsertGroupModule = "INSERT INTO GroupeModule (IdGM, NomGM, CoefGM) VALUES ('" + IdGM + "', '" + NomGM + "', " + to_string(CoefGM) + ");";
     rc = sqlite3_exec(db, sqlInsertGroupModule.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to insert group module: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }
    cout << "Group module inserted successfully." << endl;

    
    for (const auto& matiere : ListeMat) {
        string idm = matiere.getIdmat();
        string sqlInsertAssociation = "INSERT INTO GroupeModule_Matiere (IdGM, idmat) VALUES ('" + IdGM + "', '" + idm + "');";
        rc = sqlite3_exec(db, sqlInsertAssociation.c_str(), nullptr, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "Failed to associate group module with matiere: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            
            return;
        }
    }

    cout << "Group module added successfully" << endl;
}

void GroupeModule::afficherGM()
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
    // Display GroupeModule table
    const char* sqlQueryGroupeModule = "SELECT * FROM GroupeModule;";
    sqlite3_stmt* stmtGroupeModule;
    rc = sqlite3_prepare_v2(db, sqlQueryGroupeModule, -1, &stmtGroupeModule, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::cout << "GroupeModule Table:" << std::endl;
    while ((rc = sqlite3_step(stmtGroupeModule)) == SQLITE_ROW) {
        const unsigned char* idGM = sqlite3_column_text(stmtGroupeModule, 0);
        const unsigned char* nomGM = sqlite3_column_text(stmtGroupeModule, 1);
        double coefGM = sqlite3_column_double(stmtGroupeModule, 2);

        std::cout << "IdGM: " << (idGM ? reinterpret_cast<const char*>(idGM) : "NULL")
            << ", NomGM: " << (nomGM ? reinterpret_cast<const char*>(nomGM) : "NULL")
            << ", CoefGM: " << coefGM << std::endl;
    }

    sqlite3_finalize(stmtGroupeModule);

    // Display GroupeModule_Matiere table
    const char* sqlQueryGroupeModule_Matiere = "SELECT * FROM GroupeModule_Matiere;";
    sqlite3_stmt* stmtGroupeModule_Matiere;
    rc = sqlite3_prepare_v2(db, sqlQueryGroupeModule_Matiere, -1, &stmtGroupeModule_Matiere, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::cout << "GroupeModule_Matiere Table:" << std::endl;
    while ((rc = sqlite3_step(stmtGroupeModule_Matiere)) == SQLITE_ROW) {
        const unsigned char* idGM = sqlite3_column_text(stmtGroupeModule_Matiere, 0);
        const unsigned char* idmat = sqlite3_column_text(stmtGroupeModule_Matiere, 1);

        std::cout << "IdGM: " << (idGM ? reinterpret_cast<const char*>(idGM) : "NULL")
            << ", idmat: " << (idmat ? reinterpret_cast<const char*>(idmat) : "NULL") << std::endl;
    }

    sqlite3_finalize(stmtGroupeModule_Matiere);
    sqlite3_close(db);


    
}

void GroupeModule::updateGM()
{
    string idGm;
    cout << "donner idGm pour modifier: ";
    cin >> idGm;
    string idgmat;
    
    int choice;
    cout << "What do you want to update?" << endl;
    cout << "1. Nom GM" << endl;
    cout << "2. Coef GM" << endl;
    cout << "3. Mat" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
    string newValue;
    switch (choice) {
    case 1:
        cout << "Enter the new nomGM: ";
        cin >> newValue;
        updateGField(idGm, "NomGM", newValue);
        break;
    case 2:
        cout << "Enter the new coefGM: ";
        cin >> newValue;
        updateGField(idGm, "CoefGM", newValue);
        break;
    case 3:
        cout << "donner idgmat pour modifier: ";
        cin >> idgmat;
        cout << "Enter the new idmat: ";
        cin >> newValue;
        updateGMMField(idgmat, "idmat", newValue);
        break;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }
}

void GroupeModule::suppGM()
{
    string IdGM_del;
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


        cout << "donner le id de groupe module   que vous voulez le supprimer " << endl;
        cin >> IdGM_del;


        const char* sqlDeleteGroupeModule = "DELETE FROM GroupeModule WHERE IdGM=?;";
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, sqlDeleteGroupeModule, -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return;
        }

        // Bind the parameter to the statement
        sqlite3_bind_text(stmt, 1, IdGM_del.c_str(), -1, SQLITE_TRANSIENT);

        // Execute the statement
        rc = sqlite3_step(stmt);

        if (rc == SQLITE_DONE) {
            cout << "Group module " << IdGM_del << " deleted successfully from GroupeModule table." << endl;
        }
        else {
            cout << "No group module found with ID " << IdGM_del << " in GroupeModule table." << endl;
        }

        // Reset statement for reuse
        sqlite3_reset(stmt);

        // Delete from GroupeModule_Matiere table
        const char* sqlDeleteGroupeModuleMatiere = "DELETE FROM GroupeModule_Matiere WHERE IdGM=?;";
        rc = sqlite3_prepare_v2(db, sqlDeleteGroupeModuleMatiere, -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
            sqlite3_close(db);
            return;
        }

        // Bind the parameter to the statement
        sqlite3_bind_text(stmt, 1, IdGM_del.c_str(), -1, SQLITE_TRANSIENT);

        // Execute the statement
        rc = sqlite3_step(stmt);

        if (rc == SQLITE_DONE) {
            cout << "Group module " << IdGM_del << " deleted successfully from GroupeModule_Matiere table." << endl;
        }
        else {
            cout << "No group module found with ID " << IdGM_del << " in GroupeModule_Matiere table." << endl;
        }

        // Finalize statement and close database
        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }

}





