#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "hashtable2.h"
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
int hashFunction(int indeks, int n) {
	return indeks % n;
}
int main() {
	int k, p;
	cout << "Unesi vrednosti velicine bucket-a k i broj bitova p: ";
	cin >> k >> p;
	int n = pow(2, p);
	int koristin = n;
	HashTable2** x = new HashTable2*[n];
	for (int i = 0; i < n; i++) {
		x[i] = new HashTable2(k, p, p-1);
	}
	while (true) {
		cout << "\n1.Dodaj ispit u listu prijavljenih za zadatog studenta.\n"
			"2.Obrisi ispit iz liste prijavljenih za zadatog studenta.\n"
			"3.Isprazni tabelu.\n"
			"4.Ispisi broj kljuceva.\n"
			"5.Ispisi tabelu.\n"
			"6.Dodaj studenta u tabelu.\n"
			"7.Izbrisi studenta iz tabele.\n"
			"8.Prekini program.\n\n";
		int rb;
		cout << "Unesi redni broj: ";
		cin >> rb;
		if (rb == 1) {
			string sifra;
			int indeks;
			cout << "Unesi sifru ispita i broj indeksa studenta: ";
			cin >> sifra >> indeks;
			int i = hashFunction(indeks, n);
			x[i]->dodajispit(sifra, indeks);
		}
		else if (rb == 2) {
			string sifra;
			int indeks;
			cout << "Unesi sifru ispita i broj indeksa studenta: ";
			cin >> sifra >> indeks;
			int i = hashFunction(indeks, n);
			x[i]->izbrisispit(sifra, indeks);
		}
		else if (rb == 3) {
			for (int i = 0; i < n; i++) {
				x[i]->clear();
				x[i] = new HashTable2(k, p, p - 1);
			}
		}
		else if (rb == 4) {
			int br = 0;
			for (int i = 0; i < n; i++) {
				br += x[i]->keyCount();
			}
			cout << br << endl;
		}
		else if (rb == 5) {
			for (int i = 0; i < n; i++) {
				cout << *x[i] << endl;

			}
		}

		else if (rb == 6) {
			int izbor;
			cout << "Unesi sa standardnog ulaza(1) ili iz datoteke(2): ";
			cin >> izbor;
			if (izbor == 1) {
				int indeks;
				cout << "Unesi indeks: ";
				cin >> indeks;
				string ime;
				cout << "Unesi ime: ";
				cin >> ime;
				string prezime;
				cout << "Unesi prezime: ";
				cin >> prezime;
				vector<string> niz;
				cout << "Unosi sifre predmeta, kraj oznaci sa -1: ";
				while (true) {
					string a;
					cin >> a;
					if (a == "-1") break;
					niz.push_back(a);

				}
				int n = niz.size();
				string* a = new string[n];
				for (int i = n - 1; i >= 0; i--) {
					a[i] = niz[i];
				}
				x[hashFunction(indeks,koristin)]->insertKey(indeks, ime, prezime, a, n);

			}
			else if (izbor == 2) {
				cout << "Unesi ime datoteke: ";
				string imen;
				cin >> imen;
				ifstream datoteka;
				datoteka.open(imen);
				if (!datoteka) {
					cout << "Nije moguce otvoriti ovu datoteku!";
					continue;
				}
				string a, ime, prezime, pom;
				int indeks;
				vector <string> pomocni;
				getline(datoteka, a);
				while (getline(datoteka, a)) {
					pomocni.clear();
					char* token = strtok((char*)a.c_str(), ",");
					while (token != NULL)
					{
						pomocni.push_back(token);
						token = strtok(NULL, ",");

					}
					int n = pomocni.size();
					string* b = new string[n];
					int ah = n;
					for (int i = n - 1; i >= 0; i--) {
						b[i] = pomocni[i];
					}
					int indeks = stoi(b[0]);
					token = strtok((char*)b[1].c_str(), " ");
					pomocni.clear();
					while (token != NULL)
					{
						pomocni.push_back(token);
						token = strtok(NULL, " ");

					}
					string ime = pomocni[0];
					string prezime = pomocni[1];
					if (ah == 3) {
						token = strtok((char*)b[2].c_str(), " ");
						pomocni.clear();
						while (token != NULL)
						{
							pomocni.push_back(token);
							token = strtok(NULL, " ");
						}
						n = pomocni.size();
						string* s = new string[n];
						for (int i = n - 1; i >= 0; i--) {
							s[i] = pomocni[i];
						}
						x[hashFunction(indeks,koristin)]->insertKey(indeks, ime, prezime, s, n);
					}
					else x[hashFunction(indeks, koristin)]->insertKey(indeks, ime, prezime, nullptr, 0);

				}
			}
		}
		else if (rb == 7) {
			cout << "Unesi indeks koji brises: ";
			int indeks;
			cin >> indeks;
			x[hashFunction(indeks, koristin)]->deleteKey(indeks);
		}
		else if (rb == 8) {
		for (int i = 0; i < n; i++) delete x[i];
		delete[] x;
		break;
		}
		else continue;


	}


	return 0;
}