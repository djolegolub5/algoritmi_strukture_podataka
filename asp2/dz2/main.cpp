#include <iostream>
using namespace std;
#include <string>
#include "tree.h"
#include <fstream>
int main() {
	int id;
	Tree* root = nullptr;
	while (true) {
		cout << "---------------------------------------------------------------\n"
			"1. Stvori stablo!\n"
			"2. Pronadji kljuc!\n"
			"3. Umetni kljuc u stablo!\n"
			"4. Obrisi kljuc iz stabla!\n"
			"5. Ispisi sadrzaj stabla!\n"
			"6. Pronadji k-ti najmanji element stabla\n"
			"7. Unesi iz datoteke!\n"
			"8. Obrisi stablo i zavrsi program\n"
			"---------------------------------------------------------------\n";
		cin >> id;
		if (id == 1) {
			int m, from;
			cout << "Unesi red stabla: ";
			cin >> m;
			root = new Tree(m);
		}
		else if (id == 2) {
			string key;
			cout << "Kljuc: ";
			cin >> key;
			if (root != nullptr) {
				int tacno=root->pronadji(key);
				if (tacno == 1) cout << "POSTOJI";
				else cout << "NE POSTOJI";
			}
			else continue;
		}
		else if (id == 3) {
			string key;
			cout << "Kljuc: ";
			cin >> key;
			if (root) {
				root->dodaj(root, key);
				
			}

			else continue;
		}
		else if (id == 4) {
			string key;
			cout << "Kljuc: ";
			cin >> key;
			if (root) root->obrisi(root, key);
		}
		else if (id == 5) {

			if (root)cout << root;
			else continue;
		}
		else if (id == 6) {
			int k;
			cout << "Unesi k: ";
			cin >> k;
			if (root) {
				root->pronadjik(k);
			}
			else continue;
		}
		else if (id == 7) {
			ifstream datoteka;
			datoteka.open("dat.txt");
			if (root) {
				if (!datoteka) {
					cout << "Nije moguce otvoriti ovu datoteku!";
					continue;
				}
				string a, b, c;
				while (getline(datoteka, a)) {
					root->dodaj(root, a);
					
				}
			}
			datoteka.close();
		}
		else if (id == 8) {
			
			root->brisi();
			exit(0);
			root = nullptr;
		}
		else continue;


	}


	return 0;
}