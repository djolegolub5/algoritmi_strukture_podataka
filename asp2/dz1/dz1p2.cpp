#include <iostream>
#include <cmath>
using namespace std;
int binarna(double& low, double& high, double err, double br, int &k) {
	double mid = (low + high) / 2;
	k += 1;
	cout <<k<<". " << mid << endl;
	if (abs(mid - br) <= err) return 1;
	if (br < mid) high = mid;
	else low = mid;
	return 0;
}

int main() {
	while (true) {
		cout << "\nUnesi redni broj stavke\n"
			"------------------------------------------\n"
			"1. Pokreni igru.\n"
			"2. Prekini program.\n"
			"------------------------------------------\n";
		int rb;
		cin >> rb;
		if (rb == 1) {
			double x, y, t, br;
			cout << "Unesi donju granicu: ";
			cin >> x;
			cout << "Unesi gornju granicu: ";
			cin >> y;
			if (y < x) {
				cout << "Gornja granica je manja od donje!\n"; continue;
			}
			cout << "Unesi tacnost: ";
			cin >> t;
			if (abs(x - y) < t) {
				cout << "Tacnost je takva da bi bilo koji broj mogao biti resenje.\n";
				continue;
			}
			cout << "Unesi zamisljeni broj: ";
			cin >> br;
			if (br<x || br>y) {
				cout << "Broj nije u zadatom opsegu.\n";
				continue;
			}
			cout << "Unesi verovatnocu da se kljuc nalazi blize gornjoj granici: ";
			double vr;
			cin >> vr;
			vr /= 100;
			double low = x;
			double high = y;
			double mid = (high - low) * vr + low;
			int ind = 0;
			int k = 1;
			cout << k << ". " << mid << endl;
			if (abs(mid - br) <= t) {
				cout << "Potreban broj koraka je: " << k;
				ind = 1;
			}
			else if (br < mid) high = mid;
			else low = mid;
			if (ind == 0) {
			while (low <= high) {
				int idn = binarna(low, high, t, br,k);
				if (idn == 1) break;
			}
			cout << "Potreban broj koraka je: " << k;
			}
		}
		else if (rb == 2) {
			break;

		}
		else {
			continue;
		}

	}
	return 0;
}