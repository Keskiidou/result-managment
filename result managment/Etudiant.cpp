#include "Etudiant.h"
#include <sqlite3.h>
#include <string>
#include <iostream>
Etudiant::Etudiant():Num_insc(0),personne() {}
Etudiant::Etudiant(string nom, string prenom, string mail, int num_insc): personne(),Num_insc(num_insc)
{
	Nom = nom;
	Prenom = prenom;
	Mail = mail;
}


void Etudiant::ajoutEtu()
{
	cout << "donner le ID etudiant";
	cin >> Num_insc;
	cout << "Donner Nom : ";
	cin >> Nom;
	cout << "Donner Prenom : ";
	cin >> Prenom;
	cout << "Donner Mail : ";
	cin >> Mail;

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
	const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Etudiant ("
		"num_insc INTEGER PRIMARY KEY,"
		"nom TEXT NOT NULL COLLATE NOCASE,"
		"prenom TEXT NOT NULL COLLATE NOCASE,"
		"mail TEXT NOT NULL COLLATE NOCASE);";
		rc = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << errMsg << std::endl;
			sqlite3_free(errMsg);
			sqlite3_close(db);
			return;
		}
		else {
			cout << "Table created successfully" << endl;
		}
		const char* sqlInsertData = "INSERT INTO Etudiant (num_insc, nom, prenom, mail) VALUES (%d, '%s', '%s', '%s');";
		char sql[300];

		snprintf(sql, sizeof(sql), sqlInsertData, Num_insc, Nom.c_str(), Prenom.c_str(), Mail.c_str());


		rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << errMsg << std::endl;
			sqlite3_free(errMsg);
		}
		else {
			std::cout << "Data Inserted successfully" << std::endl;
		}

		sqlite3_close(db);
}


void Etudiant::afficheretu() 
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

		const char* sqlQueryData = "SELECT * FROM Etudiant;";
		sqlite3_stmt* stmt;

		int rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << errMsg << std::endl;

			sqlite3_close(db);
			return;
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			int num_insc = sqlite3_column_int(stmt, 0);
			const unsigned char* name = sqlite3_column_text(stmt, 1);
			const unsigned char* prenom = sqlite3_column_text(stmt, 2);
			const unsigned char* mail = sqlite3_column_text(stmt, 3);

			// Check if values are not NULL before printing
			std::cout << "ID: " << num_insc << ", Nom: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
				<< ", Prenom: " << (prenom ? reinterpret_cast<const char*>(prenom) : "NULL")
				<< ", Mail: " << (mail ? reinterpret_cast<const char*>(mail) : "NULL") << std::endl;
		}


		sqlite3_finalize(stmt);
		sqlite3_close(db);
	}
}


void Etudiant::suppetu()
{
	int id_del;
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


		cout << "donner le num_insc du etudiant que vous voulez le supprimer " << endl;
		cin >> id_del;


		const char* sqlQueryData = "DELETE FROM Etudiant where num_insc=?;";
		sqlite3_stmt* stmt;
		int rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);

		if (rc != SQLITE_OK) {
			cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}
		// Bind the parameter to the statement
		sqlite3_bind_int(stmt, 1, id_del);

		// Execute the statement
		rc = sqlite3_step(stmt);

		if (sqlite3_changes(db) > 0) {
			cout << "etudiant  " << id_del << " deleted successfully." << endl;
		}
		else {
			cout << "No etudiant  found with num_insc " << id_del << "." << endl;
		}

	}
}



void Etudiant::updatetu()
{

		int id;
		cout << "Enter the ID of the student you want to update: ";
		cin >> id;

		int choice;
		cout << "What do you want to update?" << endl;
		cout << "1. Name" << endl;
		cout << "2. Last Name" << endl;
		cout << "3. Email" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		string newValue;
		switch (choice) {
		case 1:
			cout << "Enter the new name: ";
			cin >> newValue;
			updateField(id, "nom", newValue);
			break;
		case 2:
			cout << "Enter the new last name: ";
			cin >> newValue;
			updateField(id, "prenom", newValue);
			break;
		case 3:
			cout << "Enter the new email: ";
			cin >> newValue;
			updateField(id, "mail", newValue);
			break;
		default:
			cout << "Invalid choice!" << endl;
			break;
		}


}

void Etudiant::updateField(int num_insc, const string& field, const string& value) 
{

	sqlite3* db;
	char* errMsg = nullptr;
	int rc = sqlite3_open("example.db", &db);
	if (rc) {
		std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
		return;
	}
	else 
	{
		std::cout << "Opened database successfully" << std::endl;

		// Set UTF-8 encoding
		sqlite3_exec(db, "PRAGMA encoding = 'UTF-8';", nullptr, nullptr, nullptr);

		string sqlQuery = "UPDATE Etudiant SET " + field + " = ? WHERE num_insc = ?;";
		sqlite3_stmt* stmt;

		int rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}

		// Bind the parameters to the statement
		sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, num_insc);

		// Execute the statement
		rc = sqlite3_step(stmt);

		if (sqlite3_changes(db) > 0) {
			cout << "Student " << num_insc << "'s " << field << " updated successfully." << endl;
		}
		else {
			cout << "No student found with ID " << num_insc << "." << endl;
		}

		sqlite3_finalize(stmt);
	}
}

