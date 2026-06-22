/*
 * Chapter 18 - BankDB Demo
 *
 * Driver for the map-based bank database - see BankDB.h for the conceptual
 * notes. Adds two accounts, looks them up by number and by name, and shows that
 * a missing account number makes findAccount() throw out_of_range.
 */

#include "BankDB.h"
#include <print>
#include <stdexcept>

using namespace std;

int main()
{
	BankDB db;

	db.addAccount(BankAccount{ 100, "Nicholas Solter" });
	db.addAccount(BankAccount{ 200, "Scott Kleper" });

	try {
		auto& account{ db.findAccount(100) };
		println("Found account 100");
		account.setClientName("Nicholas A Solter");

		auto& account2{ db.findAccount("Scott Kleper") };
		println("Found account of Scott Kleper");

		auto& account3{ db.findAccount(1000) };
	} catch (const out_of_range& caughtException) {
		println("Unable to find account: {}", caughtException.what());
	}
}
