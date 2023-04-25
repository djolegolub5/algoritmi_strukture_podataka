#include "hashtable2.h"
#include <stack>
HashTable2::vracanje& HashTable2::findKey(int ind,int key)
{

    vracanje v;
    v.i = 0;
    v.j = 0;
    v.t = nullptr;
    v.tab = nullptr;
    int i;
    HashTable2* tr = this;
    while (true) {
        v.t = tr;
        if (tr->left == nullptr) {
            for (int i = 0; i < tr->k; i++) {
                if (tr->s[i].def == 'f' && tr->s[i].table->indeks == ind) {
                    v.j = i;
                    v.t = tr;
                    v.tab = tr->s[i].table;
                    return v;
                }

            }
            return v;
        }
        else {
            if ((unsigned(ind) >> unsigned(tr->bit + 1)) & 1) {
                tr = tr->right;
            }
            else {
                tr = tr->left;
            }
        }
    }
    return v;
}

bool HashTable2::insertKey(int ind, string im, string prez, string* predmet, int brpr)
{
    vracanje v = findKey(ind, ind % int(pow(2, this->p)));
    if (!(v.tab)) {
        int i;
        int j;
        i = v.t->vratislobodnu();
        if (i < this->k) {
            v.t->s[i].table = new tabela(ind, im, prez, predmet, brpr);
            v.t->s[i].def = 'f';
            return true;
        }
        else{
            v.t->left = new HashTable2(v.t->k, v.t->p, v.t->bit + 1);
            v.t->right = new HashTable2(v.t->k, v.t->p, v.t->bit + 1);
            
            for (int i = 0; i < v.t->k; i++) {
                if (((unsigned(v.t->s[i].table->indeks)>>unsigned(v.t->bit + 1)) & 1)) {
                    int q = v.t->right->vratislobodnu();
                    v.t->right->s[q].table = new tabela(v.t->s[i].table->indeks, v.t->s[i].table->ime, v.t->s[i].table->prezime, nullptr, 0);
                    v.t->right->s[q].def = 'f';
                    v.t->right->s[q].table->head = v.t->s[i].table->head;
                    v.t->right->s[q].table->tail = v.t->s[i].table->tail;
                    v.t->right->parent = v.t;
                }
                else {
                    int q = v.t->left->vratislobodnu();
                    v.t->left->s[q].table = new tabela(v.t->s[i].table->indeks, v.t->s[i].table->ime, v.t->s[i].table->prezime, nullptr,0);
                    v.t->left->s[q].def = 'f';
                    v.t->left->s[q].table->head = v.t->s[i].table->head;
                    v.t->left->s[q].table->tail = v.t->s[i].table->tail;
                    v.t->left->parent = v.t;
                }
                v.t->s[i].table = nullptr;
                v.t->s[i].def = 'e';
            }
            unsigned int key = ind % int(pow(2, this->p));
            if (((unsigned(ind) >> unsigned(v.t->bit + 1))) & 1) {
                int q = v.t->right->vratislobodnu();
                if (q == this->k) {
                    this->insertKey(ind, im, prez, predmet, brpr);
                }
                else {
                    v.t->right->s[q].table = new tabela(ind, im, prez, predmet, brpr);
                    v.t->right->s[q].def = 'f';
                }
            }
            else{
                int q = v.t->left->vratislobodnu();
                if (q == this->k) {
                    this->insertKey(ind, im, prez, predmet, brpr);
                }
                else {
                    v.t->left->s[q].table = new tabela(ind, im, prez, predmet, brpr);
                    v.t->left->s[q].def = 'f';
                }
            }
            return true;
        }

    }
    return false;
}

bool HashTable2::deleteKey(int k)
{
    vracanje v = findKey(k, k % int(pow(2, this->p)));
    if (v.tab) {
        v.t->s[v.j].def = 'd';

        delete v.t->s[v.j].table;
        v.t->s[v.j].table = nullptr;
        int br = 0;
        HashTable2* x = v.t->parent;
        HashTable2* y=nullptr;
        if (x && x->left == v.t) y = x->right;
        else if (x) y = x->left;
        if (x && y && y->left == nullptr) {
            for (int i = 0; i < this->k; i++) {
                if (v.t->s[i].def == 'f') br++;
            }
            for (int i = 0; i < this->k; i++) {
                if (y->s[i].def == 'f') br++;
            }
            if (br <= this->k) {
                int r = 0;
                for (int i = 0; i < this->k; i++) {
                    if (v.t->s[i].def == 'f') {
                        x->s[r].table = v.t->s[i].table;
                        v.t->s[i].table = nullptr;
                        v.t->s[i].def = 'd';
                        x->s[r++].def = 'f';
                    }
                }
                delete v.t;//x
                for (int i = 0; i < this->k; i++) {
                    if (y->s[i].def == 'f') {
                        x->s[r].table = y->s[i].table;
                        y->s[i].table = nullptr;
                        y->s[i].def = 'd';
                        x->s[r++].def = 'f';
                    }
                }
                delete y;//x
                x->right = nullptr;
                x->left = nullptr;

            }
        }
        return true;

        
    }
    return false;
}

void HashTable2::clear() {
    stack<HashTable2*> stek;
    stek.push(this);
    while (!(stek.empty())) {
        HashTable2* tr = stek.top();
        stek.pop();
        if (tr->left != nullptr) {
            stek.push(tr->left);
            stek.push(tr->right);
        }
        delete tr;
    }
}

int HashTable2::keyCount()
{
    int br = 0;
    stack<HashTable2*> stek;
    stek.push(this);
    while (!(stek.empty())) {
        HashTable2* tr = stek.top();
        stek.pop();
        if (tr->left != nullptr) {
            stek.push(tr->left);
            stek.push(tr->right);
        }
        else {
            for (int i = 0; i < k; i++) {
                if (tr->s[i].def == 'f') br++;
            }
        }



    }
    return br;
}



void HashTable2::dodajispit(string i, int ind) {
    vracanje v = findKey(ind, ind % int(pow(this->p, 2)));
    if (v.tab) {
        v.t->s[v.j].table->dodajispit(i);
    }
}

void HashTable2::izbrisispit(string i, int ind) {
    vracanje v = findKey(ind, ind % int(pow(this->p, 2)));
    if (v.tab) {
        v.t->s[v.j].table->izbaciispit(i);
    }
}

ostream& operator<<(ostream& os, HashTable2& ht)
{
    stack<HashTable2*> stek;
    stek.push(&ht);
    HashTable2* tr=nullptr;
    while (!(stek.empty())) {
        tr = stek.top();
        stek.pop();
        if (tr->left != nullptr) {
            stek.push(tr->left);
            stek.push(tr->right);
        }
        else {
                HashTable2::tabela::predmeti* x = nullptr;
                for (int j = 0; j < tr->k; j++) {
                    if (tr->s[j].def == 'f') {
                        os << "[" << tr->s[j].table->ime <<
                            " " << tr->s[j].table->prezime << ", " << tr->s[j].table->indeks << " (";
                        HashTable2::tabela::predmeti* x = tr->s[j].table->head;
                        while (x && x->next) {
                            os << x->info << ", ";
                            x = x->next;

                        }
                        if (x)os << x->info << ")] ";
                        else os << ")] ";
                    }
                }
        }
    }
    
    return os<<endl;
}
