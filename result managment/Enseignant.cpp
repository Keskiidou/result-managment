#include "Enseignant.h"
#include <sqlite3.h>
Enseignant::Enseignant() :Nom(""), Prenom(""), Mail(""), CNRPS(0) {}
Enseignant::Enseignant(int cnrps, string nom, string prenom, string mail ): CNRPS(cnrps), Nom(nom),Prenom(prenom),Mail(mail){}

void Enseignant::ajoutens()
{

	cout << "donner le code cnrps du enseignant";
	cin >> CNRPS;
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
	const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS Enseignant ("
		"cnrps INTEGER PRIMARY KEY,"
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
	const char* sqlInsertData = "INSERT INTO Enseignant (cnrps, nom, prenom, mail) VALUES (%d, '%s', '%s', '%s');";
	char sql[300];

	snprintf(sql, sizeof(sql), sqlInsertData, CNRPS, Nom.c_str(), Prenom.c_str(), Mail.c_str());


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

void Enseignant::suppeens()
{
	{
		int cnrps_del;
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


			cout << "donner le cnrps du enseignant que vous voulez le supprimer " << endl;
			cin >> cnrps_del;


			const char* sqlQueryData = "DELETE FROM Enseignant where cnrps=?;";
			sqlite3_stmt* stmt;
			int rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);

			if (rc != SQLITE_OK) {
				cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
				sqlite3_close(db);
				return;
			}
			// Bind the parameter to the statement
			sqlite3_bind_int(stmt, 1, cnrps_del);

			// Execute the statement
			rc = sqlite3_step(stmt);

			if (sqlite3_changes(db) > 0) {
				cout << "enseignant  " << cnrps_del << " deleted successfully." << endl;
			}
			else {
				cout << "No enseignant  found with cnrps " << cnrps_del << "." << endl;
			}

		}
	}
}
void Enseignant::afficherens()
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

		const char* sqlQueryData = "SELECT * FROM Enseignant;";
		sqlite3_stmt* stmt;

		int rc = sqlite3_prepare_v2(db, sqlQueryData, -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << errMsg << std::endl;

			sqlite3_close(db);
			return;
		}

		while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
			int cnrps = sqlite3_column_int(stmt, 0);
			const unsigned char* name = sqlite3_column_text(stmt, 1);
			const unsigned char* prenom = sqlite3_column_text(stmt, 2);
			const unsigned char* mail = sqlite3_column_text(stmt, 3);

			// Check if values are not NULL before printing
			std::cout << "cnrps: " << cnrps << ", Nom: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
				<< ", Prenom: " << (prenom ? reinterpret_cast<const char*>(prenom) : "NULL")
				<< ", Mail: " << (mail ? reinterpret_cast<const char*>(mail) : "NULL") << std::endl;
		}


		sqlite3_finalize(stmt);
		sqlite3_close(db);
	}
}

void Enseignant::updatens()
{
	int Cnrps;
	cout << "donner le Cnrps de l'enseignant pour modifier: ";
	cin >> Cnrps;

	int choice;
	cout << "What do you want to update?" << endl;
	cout << "1. prenom" << endl;
	cout << "2. nom" << endl;
	cout << "3. Email" << endl;
	cout << "Enter your choice: ";
	cin >> choice;

	string newValue;
	switch (choice) {
	case 1:
		cout << "Enter the new name: ";
		cin >> newValue;
		updateEnsField(Cnrps, "prenom", newValue);
		break;
	case 2:
		cout << "Enter the new last name: ";
		cin >> newValue;
		updateEnsField(Cnrps, "nom", newValue);
		break;
	case 3:
		cout << "Enter the new email: ";
		cin >> newValue;
		updateEnsField(Cnrps, "mail", newValue);
		break;
	default:
		cout << "Invalid choice!" << endl;
		break;
	}
}

void Enseignant::updateEnsField(int Cnrps, const std::string& field, const std::string& value)
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

		string sqlQuery = "UPDATE Enseignant SET " + field + " = ? WHERE cnrps = ?;";
		sqlite3_stmt* stmt;

		int rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}

		// Bind the parameters to the statement
		sqlite3_bind_text(stmt, 1, value.c_str(), -1, SQLITE_STATIC);
		sqlite3_bind_int(stmt, 2, Cnrps);

		// Execute the statement
		rc = sqlite3_step(stmt);

		if (sqlite3_changes(db) > 0) {
			cout << "enseignant " << Cnrps << "'s " << field << " updated successfully." << endl;
		}
		else {
			cout << "No enseignant found with this cnrps " << Cnrps << "." << endl;
		}

		sqlite3_finalize(stmt);
	}
}
