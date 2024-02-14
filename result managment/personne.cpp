#include "personne.h"
#include <sqlite3.h>
#include<string>

personne::personne():ID(0),Nom(""),Prenom(""),Mail(""){}

personne::personne(int id, string nom, string prenom, string mail):ID(id),Nom(nom), Prenom(prenom),Mail(mail){}



//void personne::ajoutPerso()
//{
//	cout << "Donner Nom : ";
//	getline(cin, Nom);
//	cout << "Donner Prenom : ";
//	getline(cin, Prenom);
//	cout << "Donner Mail : ";
//	getline(cin, Mail);
//
//
//	sqlite3* db;
//	char* errMsg = nullptr;
//	int rc = sqlite3_open("example.db", &db);
//	if (rc) {
//		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
//		return;
//	}
//	else {
//		std::cout << "Opened database successfully" << std::endl;
//
//		// Set UTF-8 encoding
//		sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);
//	}
//
//	const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Personne ("
//		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
//		"nom TEXT NOT NULL COLLATE NOCASE,"
//		"prenom TEXT NOT NULL COLLATE NOCASE,"
//		"mail TEXT NOT NULL COLLATE NOCASE);";
//	rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg);
//	if (rc != SQLITE_OK) {
//		std::cerr << "SQL error: " << errMsg << std::endl;
//		sqlite3_free(errMsg);
//		sqlite3_close(db);
//		return;
//	}
//	else {
//		cout << "Table created successfully" << endl;
//	}
//	const char* sqlInsertData = "INSERT INTO Personne (nom, prenom, mail) VALUES ('%s','%s','%s');";
//	char sql[100];  // Assuming a maximum length for the SQL query
//
//	// Format the SQL query with variables
//	snprintf(sql, sizeof(sql), sqlInsertData, Nom.c_str(), Prenom.c_str(), Mail.c_str());
//
//	rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
//	if (rc != SQLITE_OK) {
//		std::cerr << "SQL error: " << errMsg << std::endl;
//		sqlite3_free(errMsg);
//		sqlite3_close(db);
//		return;
//	}
//	else {
//		cout << "Data Inserted successfully" << endl;
//	}
//
//
//
//	sqlite3_close(db);
//}


//void personne::afficherp()
//{
//	sqlite3* db;
//	char* errMsg = nullptr;
//	int rc = sqlite3_open("example.db", &db);
//	if (rc) {
//		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
//		return;
//	}
//	else {
//		std::cout << "Opened database successfully" << std::endl;
//
//		// Set UTF-8 encoding
//		sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);
//		const char* sqlQueryData = "SELECT * FROM Personne;";
//		sqlite3_stmt* stmt;
//
//		rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);
//		if (rc != SQLITE_OK) {
//			std::cerr << "SQL error: " << errMsg << std::endl;
//			sqlite3_free(errMsg);
//			sqlite3_close(db);
//			return;
//		}
//
//		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
//			int id = sqlite3_column_int(stmt, 0);
//			const unsigned char* name = sqlite3_column_text(stmt, 1);
//			const unsigned char* prenom = sqlite3_column_text(stmt, 2);
//			const unsigned char* mail = sqlite3_column_text(stmt, 3);
//
//			// Check if values are not NULL before printing
//			std::cout << "ID: " << id << ", Nom: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
//				<< ", Prenom: " << (prenom ? reinterpret_cast<const char*>(prenom) : "NULL")
//				<< ", Mail: " << (mail ? reinterpret_cast<const char*>(mail) : "NULL") << std::endl;
//		}
//
//
//		sqlite3_finalize(stmt);
//		sqlite3_close(db);
//	}
//}

//void personne::suppperso() 
//{
//	int id_del;
//
//	cout << "donner l'id du personne que vous voulez le supprimer " << endl;
//	cin >> id_del;
//	sqlite3* db;
//	char* errMsg = nullptr;
//	int rc = sqlite3_open("example.db", &db);
//	if (rc) {
//		cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
//		return;
//	}
//	else {
//		cout << "Opened database successfully" << endl;
//
//		// Set UTF-8 encoding
//		sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);
//	}
//
//	const char* sqlQueryData = "DELETE FROM Personne where id=?;";
//	sqlite3_stmt* stmt;
//	rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);
//
//	if (rc != SQLITE_OK) {
//		cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
//		sqlite3_close(db);
//		return;
//	}
//	// Bind the parameter to the statement
//	sqlite3_bind_int(stmt, 1, id_del);
//
//	// Execute the statement
//	rc = sqlite3_step(stmt);
//
//	if (sqlite3_changes(db) > 0) {
//		cout << "Person with ID " << id_del << " deleted successfully." << endl;
//	}
//	else {
//		cout << "No person found with ID " << id_del << "." << endl;
//	}
//	// Finalize the statement and close the database
//	sqlite3_finalize(stmt);
//	sqlite3_close(db);
//
//}


	


    