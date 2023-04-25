#include "tree.h"
void sortiraj(string* niz, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (niz[i] > niz[j]) {
				string a = niz[i];
				niz[i] = niz[j];
				niz[j] = a;
			}
		}
	}
}
void parents(Tree* cvor, int n) {
	for (int i = 0; i <= n; i++) {
		if (cvor->pok[i])cvor->pok[i]->parent = cvor;
	}
}
Tree::pomocna Tree::sledbenik(Tree* cvora, int k)
{
	pomocna x;
	Tree* p = nullptr;
	Tree* q = nullptr;
	x.cvor = nullptr;


	if ((k + 1) <= cvora->n) {
		if (cvora->pok[k + 1] != nullptr) {
			p = cvora->pok[k + 1];
			while (p->pok[0] != nullptr) p = p->pok[0];
			x.cvor = p;
			x.k = 0;
			return x;
		}
	}
	if (k < cvora->n - 1) {
		x.cvor = cvora;
		x.k = k + 1;
		return x;
	}
	p = cvora;
	q = cvora->parent;
	while (q != nullptr) {
		p = q;
		for (int i = 0; i < p->n; i++) {
			x.cvor = p;
			x.k = i;
			if (p->niz[i] > cvora->niz[k]) return x;
		}
		q = q->parent;
		x.cvor = q;
		x.k = 0;
	}
	return x;
}


void Tree::brisi(){
	stack<Tree*> steki;
	steki.push(this);
	Tree* tr = nullptr;
	while (!(steki.empty())) {
		tr = steki.top();
		steki.pop();
		for (int i = 0; i <= tr->n; i++) {
			if (tr->pok[i])steki.push(tr->pok[i]);
		}
		if(tr)delete tr;
	}
}

bool Tree::dodaj(Tree* root, string x, int ide) {
	if ((*root).pronadji(x)) return false;
	Tree* p = root;
	Tree* q = nullptr;
	if (ide == 0) {
		while (p && p->pok[0] != nullptr) {
			q = p;
			int i = 0;
			while (i<p->n && x > p->niz[i]) i++;
			p = p->pok[i];
		}
	}
	if (p == nullptr) return false;
	if (p->n + 1 < p->m) {
		p->niz[p->n++] = x;
		sortiraj(p->niz, p->n);
	}
	else {
		deli(x, p, q);
	}
	/*stack<Tree*> steki;
	steki.push(root);
	Tree* tr = nullptr;
	while (!(steki.empty())) {
		tr = steki.top();
		steki.pop();
		for (int i = 0; i <= tr->n; i++) {
			if (tr->pok[i])tr->pok[i]->parent = tr;
			if (tr->pok[i])steki.push(tr->pok[i]);
		}
	}*/
	return true;

}

bool Tree::obrisi(Tree* root, string x)
{
	int t;
	if (!root->pronadji(x)) return false;
	Tree* p = root;
	Tree* q = nullptr;
	pomocna z;
	int i = 0;
	while (p->pok[0] != nullptr) {
		q = p;
		i = 0;
		while (i < p->n && x > p->niz[i]) i++;
		if (x == p->niz[i]) break;
		p = p->pok[i];
	}
	for (i = 0; i < p->n; i++) if (x == p->niz[i]) break;
	t = i;
	if (p->pok[0]) {
		z = sledbenik(p, i);
		string c = p->niz[i];
		p->niz[i] = z.cvor->niz[z.k];
		z.cvor->niz[z.k] = c;
		p = z.cvor;
		t = i = z.k;
	}
	if (p == root) {
		if (p->n > 1) {
			string c = p->niz[p->n - 1];
			p->niz[p->n - 1] = x;
			p->niz[i] = c;
			p->n--;
			sortiraj(p->niz, p->n);

		}
	}
	else if (p->n > (2 * p->m - 1) / 3) {
		string c = p->niz[p->n - 1];
		p->niz[p->n - 1] = x;
		p->niz[i] = c;
		p->n--;
		sortiraj(p->niz, p->n);
	}
	else {
		Tree* y = p->parent;
		Tree* s = nullptr;
		int i = 0;
		while (i<y->n && x > y->niz[i]) i++;
		i++;
		if (i <= y->n)s = y->pok[i];
		if (i <= y->n && s && s->n > (2 * p->m - 1) / 3) {
			string c = p->niz[p->n - 1];
			p->niz[p->n - 1] = x;
			p->niz[t] = c;
			p->n--;
			p->niz[p->n++] = y->niz[i - 1];
			sortiraj(p->niz, p->n);
			y->niz[i - 1] = s->niz[0];
			string r = s->niz[s->n - 1];
			s->niz[s->n - 1] = s->niz[0];
			s->niz[0] = r;
			s->n--;
			sortiraj(s->niz, s->n);
		}
		else {
			if (i + 1 <= y->n) s = y->pok[i + 1];
			if (i + 1 <= y->n && s && s->n > (2 * p->m - 1) / 3) {
				Tree* w = y->pok[i];
				string c = p->niz[p->n - 1];
				p->niz[p->n - 1] = x;
				p->niz[t] = c;
				p->n--;
				p->niz[p->n++] = y->niz[i - 1];
				sortiraj(p->niz, p->n);
				y->niz[i - 1] = w->niz[0];
				/*string q = w->niz[w->n - 1];
				w->niz[w->n - 1] = y->niz[i];*/
				w->niz[0] = y->niz[i];
				sortiraj(w->niz, w->n);
				y->niz[i] = s->niz[0];
				string h = s->niz[0];
				s->niz[0] = s->niz[s->n - 1];
				s->niz[s->n - 1] = h;
				s->n--;
				sortiraj(s->niz, s->n);
			}
			else {
				if (i - 2 >= 0) s = y->pok[i - 2];
				if (i - 2 >= 0 && s && s->n > (2 * p->m - 1) / 3) {
					p->niz[t] = y->niz[i - 2];
					sortiraj(p->niz, p->n);
					y->niz[i - 2] = s->niz[s->n - 1];
					s->n--;
				}
				else {
					if (i - 3 >= 0) s = y->pok[i - 3];
					if (i - 3 >= 0 && s && s->n > (2 * p->m - 1) / 3) {
						Tree* w = y->pok[i - 2];
						p->niz[t] = y->niz[i - 2];
						sortiraj(p->niz, p->n);
						y->niz[i - 2] = w->niz[w->n - 1];
						w->niz[w->n - 1] = y->niz[i - 3];
						sortiraj(w->niz, w->n);
						y->niz[i - 3] = s->niz[s->n - 1];
						s->n--;
					}
					else {

					}
				}

			}
		}
	}
	//else lomi(p, q, i);
	return true;

}

bool Tree::pronadji(string x)
{
	Tree* p = this;
	while (p) {
		int i = 0;
		while (i < p->n && x > p->niz[i]) i++;
		if (i < p->n && p->niz[i] == x) return true;
		p = p->pok[i];
	}
	return false;
}

void Tree::pronadjik(int k) {
	if (k <= 0) cout << "NEMA\n";
	else {
		Tree* p = this;
		while (p->pok[0]) {
			int i = 0;
			p = p->pok[0];
		}
		pomocna x;
		if (k <= p->n) cout << p->niz[k - 1] << endl;
		else {
			x.cvor = p;
			x.k = 0;
			for (int i = 0; i < k - 1; i++) {
				x = sledbenik(x.cvor, x.k);
				if (x.cvor == nullptr) break;
			}
			if (x.cvor == nullptr) cout << "NEMA\n";
			else {
				cout << x.cvor->niz[x.k] << endl;
			}
		}
	}
}

Tree* Tree::lomi(Tree* x, Tree* y, int i, Tree* z)
{

	return nullptr;
}

Tree* Tree::deli(string a, Tree* x, Tree* y, Tree* z) {
	int razs;
	int razx;
	Tree* s = nullptr;
	int i;
	string* p = new string[3 * x->m];
	if (y) {
		s = nullptr;

		i = 0;
		while (i<y->n && a > y->niz[i]) i++;
		i++;
		int qq = i;
		if (i <= y->n)s = y->pok[i];
		if (s && s->n + 1 < s->m) {

			int j;
			int id = 0;
			for (j = 0; j < x->n; j++) {
				p[j] = x->niz[j];
			}
			p[j++] = a;
			p[j++] = y->niz[i - 1];
			for (int k = 0; k < s->n; k++) {
				p[j++] = s->niz[k];
			}
			razx = j / 2 - x->n;
			razs = -(s->n - j + j / 2 + 1);
			sortiraj(p, j);
			int duz = j;
			y->niz[i - 1] = p[j / 2];
			x->n = j / 2;
			s->n = (j - j / 2 - 1);
			int i;
			for (i = 0; i < duz / 2; i++) x->niz[i] = p[i];
			int k = 0;
			for (int i = j / 2 + 1; i < j; i++, k++) s->niz[k] = p[i];
			if (z != nullptr) {
				if (p[j / 2] == a) {
					for (int k = s->n; k >= 1; k--) {
						s->pok[k] = s->pok[k - 1];
					}
					s->pok[0] = z;
					parents(s, s->n);
					//z->parent = s;
				}
				else {
					for (int k = s->n; k >= razs; k--) {
						s->pok[k] = s->pok[k - 1];
					}
					for (int j = razs; j > 0; j--) {
						//x->pok[x->n - j]->parent = s;
						s->pok[razs-j] = x->pok[x->n + razx - j+1];
					}
					parents(s, s->n);
					int k;
					for (k = 0; k < x->n; k++) if (x->niz[k] == a) break;
					int id = ++k;
					k++;
					//joj
					for (int j =x->n; j >= k; j--) x->pok[j] = x->pok[j - 1];
					x->pok[id] = z;
					z->parent = x;
				}
			}
			for (int q = x->n + 1; q < x->m; q++) x->pok[q] = nullptr;
			for (int q = s->n + 1; q < s->m; q++) s->pok[q] = nullptr;
			return y;
		}
		else {
			if (i - 2 >= 0 && y->pok[i - 2] && y->pok[i - 2]->n + 1 < y->pok[i - 2]->m) {
				int j;
				s = y->pok[i - 2];
				if (s->n + 1 < s->m) {
					for (j = 0; j < s->n; j++) p[j] = s->niz[j];
					p[j++] = y->niz[i - 2];
					p[j++] = a;
					int id = 0;
					for (int k = 0; k < x->n; k++) {
						p[j++] = x->niz[k];
					}
					sortiraj(p, j);
					y->niz[i - 2] = p[j / 2];
					razs = j / 2 - s->n;
					razx = x->n - j + j / 2 + 1;
					s->n = j / 2;
					int i1;
					for (i1 = 0; i1 < j / 2; i1++) s->niz[i1] = p[i1];
					x->n = (j - j / 2 - 1);
					int k = 0;
					for (int i = j / 2 + 1; i < j; i++, k++) x->niz[k] = p[i];
					if (z) {
						int q = 0;
						for (int j = razs - 1; j >= 0; j--) {
							//x->pok[q]->parent = s;
							s->pok[s->n - j] = x->pok[q++];
						}
						parents(s, s->n);
						int k;
						for (k = 0; k <= x->n; k++) {
							x->pok[k] = x->pok[k + 1];
							if (x->niz[k] == a) break;
						}
						int id = ++k;
						x->pok[id] = z;
						parents(x, x->n);
						z->parent = x;
					}
					for (int q = x->n + 1; q < x->m; q++) x->pok[q] = nullptr;
					for (int q = s->n + 1; q < s->m; q++) s->pok[q] = nullptr;
					return y;
				}
			}
		}
		if (s) {
			int j = 0;
			int id = 0;
			for (int k = 0; k < x->n; k++, j++) {
				p[j] = x->niz[j];
			}
			p[j++] = a;
			p[j++] = y->niz[i - 1];
			for (int k = 0; k < s->n; k++) p[j++] = s->niz[k];
			sortiraj(p, j);
			Tree* novi = new Tree(x->m, 1);
			novi->n = (2 * x->m - 1) / 3;
			int duz = j;
			int nn = x->n;
			int sn = s->n;
			int razx = x->n - ((2 * x->m - 2) / 3);
			int razs = s->n - (2 * x->m) / 3;
			y->niz[i - 1] = p[(2 * x->m - 2) / 3];
			x->n = (2 * x->m - 2) / 3;
			s->n = (2 * x->m) / 3;
			for (int i = 0; i < (2 * x->m - 2) / 3; i++) {
				x->niz[i] = p[i];
			}
			//if (z) x->pok[i] = nullptr;
			int r = (2 * x->m - 2) / 3 + 1;
			for (int i = 0; i < (2 * x->m - 1) / 3; i++) {
				novi->niz[i] = p[r++];
			}
			//if (z) s->pok[i] = nullptr;
			int pomoc = r++;

			for (int i = 0; i < (2 * x->m) / 3; i++) {
				s->niz[i] = p[r++];
			}

			if (z) {

				if (p[(2 * x->m - 2) / 3] == a) {
					novi->pok[0] = z;
					z->parent = novi;
					int i;
					for (i = 1; razx > 0; i++, razx--) {
						novi->pok[i] = x->pok[nn - razx + 1];
						//x->pok[nn - razx+1]->parent = novi;
					}
					//parents(novi, novi->n);
					//i++;
					int k;
					for (int j = i, k = 0; j <= novi->n; j++, k++) {
						novi->pok[j] = s->pok[k];
						//s->pok[k]->parent = novi;
					}
					parents(novi, novi->n);
					for (int i = 0; i <= s->n; i++) {
						s->pok[i] = s->pok[i + razs];
					}
				}
				else {
					int id = 0;
					int auh = razx;
					for (int i = 0; i < x->n; i++) {
						if (x->niz[i] == a) {
							id = -1;
							auh++;
						}
					}
					int j;
					for (j = 0; razx > id; j++) {
						if (novi->niz[j] == a) {
							novi->pok[j + 1] = z;
							z->parent = novi;
						}
						if (novi->pok[j] != z) {
							novi->pok[j] = x->pok[nn - auh + 1];
							//x->pok[nn - razx+1]->parent = novi;
							razx--;
							auh--;
						}

					}
					//mzdgrsk
					if(novi->pok[j]==z)j++;
					int k = 0;
					for (int i = j; i <= novi->n; i++, k++) {
						novi->pok[i] = s->pok[k];
						//s->pok[k]->parent = novi;
					}
					parents(novi, novi->n);
					for (int i = 0; i <= s->n; i++) {
						s->pok[i] = s->pok[i + razs];
					}
					if (id == -1) {
						x->pok[x->n] = z;
						//z->parent = x;
					}
					parents(x, x->n);
				}

			}
				for (int q = x->n + 1; q < x->m; q++) x->pok[q] = nullptr;
				for (int q = s->n + 1; q < s->m; q++) s->pok[q] = nullptr;
				if (y->n + 1 < y->m) {
					y->niz[y->n++] = p[pomoc];
					sortiraj(y->niz, y->n);
					for (int k = y->n; k >= i + 1; k--) y->pok[k] = y->pok[k - 1];
					y->pok[i] = novi;
					novi->parent = y;
					return y;
				}
				else {
					y->pok[i] = novi;
					novi->parent = y;
					deli(p[pomoc], y, y->parent, s);
				}
			}
			else {
				if (i - 2 >= 0) {
					int j;
					s = y->pok[i - 2];
					for (j = 0; j < s->n; j++) p[j] = s->niz[j];
					p[j++] = y->niz[i - 2];
					p[j++] = a;
					int id = 0;
					for (int k = 0; k < x->n; k++) {
						p[j++] = x->niz[k];
					}
					sortiraj(p, j);
					int duz = j;
					int nn = x->n;
					int sn = s->n;
					int razx = x->n - (2 * x->m - 2) / 3;
					int razs = s->n - (2 * x->m - 1) / 3;
					y->niz[i - 2] = p[(2 * x->m - 2) / 3];
					s->n = (2 * x->m - 2) / 3;
					x->n = (2 * x->m - 1) / 3;
					for (int i = 0; i < (2 * x->m - 2) / 3; i++) {
						s->niz[i] = p[i];
					}
					//if (z) x->pok[i] = nullptr;
					int r = (2 * x->m - 2) / 3 + 1;
					for (int i = 0; i < (2 * x->m - 1) / 3; i++) {
						x->niz[i] = p[r++];
					}
					//if (z) s->pok[i] = nullptr;
					if (z) {

					}
					int pomoc = r++;
					Tree* novi = new Tree(x->m, 1);
					novi->n = (2 * x->m) / 3;
					for (int i = 0; i < (2 * x->m) / 3; i++) {
						novi->niz[i] = p[r++];
					}


					if (z) {
						if (p[pomoc] == a) {
							novi->pok[0] = z;
							z->parent = novi;
							for (int i = 1; i <= novi->n; i++) {
								novi->pok[i] = x->pok[razx + i];
								//x->pok[razx + i]->parent = novi;
							}
							parents(novi, novi->n);
							for (int i = x->n; i >= razs; i--) {
								x->pok[i] = x->pok[i - 1];
							}
							for (int i = 0; i < razs; i++) {
								x->pok[i] = s->pok[sn - i];
								//s->pok[sn - i]->parent = x;
							}
							parents(x, x->n);


						}
						else {
							for (int j = 0; j <= novi->n; j++) {
								if (novi->niz[j] == a) {
									novi->pok[j + 1] = z;
									//z->parent = novi;
									/*i--;*/
								}
								if (novi->pok[j] != z) {
									novi->pok[j] = x->pok[nn - razx];
									//x->pok[nn - razx]->parent = novi;
									razx--;
								}

							}
							parents(novi, novi->n);
							for (int i = x->n; i >= razs; i--) {
								x->pok[i] = x->pok[i - 1];
							}
							for (int i = 0; i < razs; i++) {
								x->pok[i] = s->pok[sn - i];
								//s->pok[sn - i]->parent = x;
							}
							parents(x, x->n);

						}
					}
					if (y->n + 1 < y->m) {
						y->niz[y->n++] = p[pomoc];
						sortiraj(y->niz, y->n);
						for (int k = y->n; k > i; k--) y->pok[k] = y->pok[k - 1];
						y->pok[i] = novi;
						novi->parent = y;

						return y;
					}
					//pok
					else deli(p[pomoc], y, y->parent, novi);
				}
			}

		}
		else {
			Tree* levo = nullptr, * desno = nullptr;
			levo = new Tree(x->mchild, 1);
			desno = new Tree(x->mchild, 1);

			int k = 0;
			int ide = 0;
			for (int i = 0; i < x->n; i++) {
				p[k++] = x->niz[i];
			}
			p[k++] = a;
			sortiraj(p, k);

			for (int i = 0; i < k / 2; i++) {
				levo->niz[i] = p[i]; levo->n++;
			}
			int j = 0;
			for (int i = k / 2 + 1; i < k; i++) {
				desno->niz[j++] = p[i];
				desno->n++;
			}
			levo->parent = x;
			desno->parent = x;
			if (z) {
				if (a == p[k / 2]) {
					desno->pok[0] = z;
					z->parent = desno;
					int i;
					for (i = 0; i <= levo->n; i++) {
						levo->pok[i] = x->pok[i];
						x->pok[i]->parent = levo;
					}
					for (int j = 1; j <= desno->n; j++) {
						x->pok[i]->parent = desno;
						desno->pok[j] = x->pok[i++];

					}
				}
				else {
					int i = 0;
					for (int ki = 0; ki <= levo->n; ki++) {
						if (levo->niz[ki] == a) {
							levo->pok[ki + 1] = z;
							z->parent = levo;
							/*i--;*/
						}
						if (levo->pok[ki] != z) {
							x->pok[i]->parent = levo; levo->pok[ki] = x->pok[i++];
						}
					}
					for (int j = 0; j <= desno->n; j++) {
						if (desno->niz[j] == a) {
							desno->pok[j + 1] = z;
							z->parent = desno;
							/*i--;*/
						}
						if (desno->pok[j] != z) {
							x->pok[i]->parent = desno;
							desno->pok[j] = x->pok[i++];
						}
					}
				}
			}
			for (int i = 2; i < x->m; i++) x->pok[i] = nullptr;
			x->n = 1;
			x->niz[0] = p[k / 2];
			x->pok[0] = levo;
			x->pok[1] = desno;

		}
}

ostream& operator<<(ostream& os, Tree* root) {
	struct a {
		Tree* stablo;
		int level;
	};
	stack<a> stek;

	a pomoc;
	pomoc.level = 0;
	pomoc.stablo = root;

	stek.push(pomoc);
	while (!stek.empty()) {
		Tree* tr; int level;
		pomoc = stek.top();
		tr = pomoc.stablo;
		level = pomoc.level;
		stek.pop();
		for (int i = 0; i < level; i++) os << "*";
		for (int i = 0; i < tr->n; i++) {
			os << tr->niz[i] << ' ';
		}
		os << endl;
		for (int i = 0; i < tr->n + 1; i++) {
			pomoc.level = level + 1;
			pomoc.stablo = tr->pok[i];
			if (pomoc.stablo)stek.push(pomoc);
		}
	}
	return os;
}
