#ifndef _hashtable2_h_
#define _hashtable2_h_
#include <string>
#include <iostream>
using namespace std;
#include <cmath>
class HashTable2{
	int k, p;
	int bit;
	
	struct tabela {
		tabela() = default;
		struct predmeti {
			string info;
			predmeti* next;
			predmeti(string x) : info(x), next(nullptr) {}
		};
		int indeks;
		string ime, prezime;
		predmeti* head = nullptr, * tail = nullptr;
		void dodajispit(string i) {
			if (!postojiispit(i)) {

				predmeti* x = new predmeti(i);
				if (!head)head = x;
				else tail->next = x;
				tail = x;
			}
		}
		bool postojiispit(string i) {
			predmeti* x = head;
			while (x) {
				if (x->info == i) return true;
				x = x->next;
			}
			return false;
		}
		tabela(int i, string im, string p, string* a, int brpred) : indeks(i), ime(im), prezime(p) {
			for (int j = 0; j < brpred; j++) {
				dodajispit(a[j]);
			}
		}
		void izbaciispit(string i) {
			predmeti* x = head, * y = nullptr;
			if (postojiispit(i)) {
				while (x && x->info != i) {
					y = x;
					x = x->next;
				}
				if (y == nullptr) {
					if (x)head = x->next;
					else head = tail = nullptr;
					delete x;
				}
				else {
					y->next = x->next;
					if (tail == x) tail = y;
					delete x;

				}

			}
		}
		~tabela() {
			predmeti* x = head;
			while (head) {
				head = head->next;
				delete x;
				x = head;
			}


		}
	};
	struct vracanje {
		int i;
		int j;
		HashTable2* t;
		HashTable2::tabela* tab;
	};
	struct struktura {
		tabela* table;
		char def = 'e';
		~struktura() {
			delete table;
			def = 'd';
		}
	};
	struktura* s;
	int vratislobodnu() {
		for (int i = 0; i < this->k; i++) {
			if (s[i].def != 'f') return i;
		}
		return this->k;
	}
	HashTable2* left = nullptr;
	HashTable2* right = nullptr;
	HashTable2* parent=nullptr;
public:
	HashTable2(int ka, int pa, int b) : k(ka), p(pa) {
		/*n = pow(2, p);*/
		bit = b;
		s = new struktura [k];
		for (int i = 0; i < k; i++) {
			s[i].table = nullptr;
			}
		}
	vracanje& findKey(int ind, int key);
	bool insertKey(int ind, string i, string prez, string* a, int brpr);
	bool deleteKey(int k);
	void clear();
	int keyCount();
	friend ostream& operator<<(ostream& os, HashTable2& ht);
	void dodajispit(string i, int ind);
	void izbrisispit(string i, int ind);
	~HashTable2() {
		delete[] s;
		s = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

};
#endif
