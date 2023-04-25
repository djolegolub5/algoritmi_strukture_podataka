#ifndef _tree_h_
#define _tree_h_
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include<stack>

class Tree{
	
	string* niz = nullptr;
	
	int m;
	int mchild;
	int mroot;
	
	struct pomocna {
		Tree* cvor;
		int k;
	};
	
	
public:
	Tree** pok = nullptr;
	Tree* parent;
	int n = 0;
	Tree() = default;
	Tree(int ma,int id=0){
		mroot = ((2 * ma - 2) / 3)*2 + 1;
		mchild = ma;
		if (id == 0) {
			pok = new Tree * [mroot];
			niz = new string[mroot - 1];
			for (int i = 0; i < mroot; i++) pok[i] = nullptr;
			m = mroot;
		}
		else {
			pok = new Tree * [mchild];
			niz = new string[mchild - 1];
			for (int i = 0; i < mchild; i++) pok[i] = nullptr;
			m = mchild;
		}
		
		parent = nullptr;
	}
	void brisi();
	bool dodaj(Tree* root, string x, int id=0);
	bool obrisi(Tree* root, string x);
	bool pronadji(string x);
	void pronadjik(int k);
	Tree* lomi(Tree* x, Tree* y, int i, Tree* z=nullptr);
	friend ostream& operator<<(ostream& os, Tree* root);
	Tree* deli(string a, Tree* x, Tree* y, Tree* z=nullptr);
	pomocna sledbenik(Tree* cvor, int k);

	~Tree() {
		delete[] pok;
		pok = nullptr;
		delete[] niz;
		niz = nullptr;

	}
};


#endif


