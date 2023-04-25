#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int** make_graph(int n) {
	int** graf, i, j;
	char* name;
	graf = malloc(sizeof(int*) * n);
	for (i = 0; i < n; i++) {
		graf[i] = malloc(sizeof(int) * n);
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			graf[i][j] = 0;
		}
	}
	return graf;
}
char* name_graph(int n) {
	int i;
	char* name;
	name = malloc(sizeof(char) * n);
	for (i = 0; i < n; i++) {
		printf("Unesi oznaku za cvor: ");
		scanf(" %c", &name[i]);
	}
	return name;
}
void add_branch(int*** graph, char* name, int n) {
	char a, b;
	int i, j;
	printf("Unesi oznaku za prvi cvor: ");
	scanf(" %c", &a);
	printf("Unesi oznaku za drugi cvor: ");
	scanf(" %c", &b);
	for (i = 0; i < n; i++) {
		if (name[i] == a) break;
	}
	for (j = 0; j < n; j++) {
		if (name[j] == b) break;
	}
	if (j == n || i == n) return;
	(*graph)[i][j] = 1;

}
void del_branch(int*** graph, char* name, int n) {
	char a, b;
	int i, j;
	printf("Unesi oznaku za prvi cvor: ");
	scanf(" %c", &a);
	printf("Unesi oznaku za drugi cvor: ");
	scanf(" %c", &b);
	for (i = 0; i < n; i++) {
		if (name[i] == a) break;
	}
	for (j = 0; j < n; j++) {
		if (name[j] == b) break;
	}
	if (j == n || i == n) return;
	(*graph)[i][j] = 0;
}
void add_node(int*** graph, char** name, int* n) {
	int i, k;
	char c;
	(*n)++;
	k = *n;
	(*name) = realloc((*name), k * sizeof(char));
	(*graph) = realloc((*graph), k * sizeof(int*));
	(*graph)[k - 1] = malloc(sizeof(int) * k);
	for (i = 0; i < k; i++) (*graph)[i] = realloc((*graph)[i], sizeof(int) * k);
	for (i = 0; i < k; i++) {
		(*graph)[i][(*n) - 1] = 0;
		(*graph)[(*n) - 1][i] = 0;
	}
	printf("Unesi oznaku za cvor: ");
	scanf(" %c", &c);
	(*name)[k - 1] = c;
}
void del_node(int*** graph, char** name, int* n) {
	char c;
	int i, j, k;
	printf("Unesi oznaku za cvor: ");
	scanf(" %c", &c);
	for (i = 0; i < (*n); i++) {
		if ((*name)[i] == c) break;
	}
	if (i == (*n)) return;
	k = i;
	for (i = k; i < (*n) - 1; i++) {
		for (j = 0; j < (*n); j++) {
			(*graph)[i][j] = (*graph)[i + 1][j];
		}
	}
	for (i = k; i < (*n) - 1; i++) {
		for (j = 0; j < (*n); j++) {
			(*graph)[j][i] = (*graph)[j][i + 1];
		}
	}
	for (i = k; i < (*n); i++) (*name)[i] = (*name)[i + 1];
	(*n)--;
	(*graph) = realloc((*graph), (*n) * sizeof(int*));
	for (i = 0; i < (*n); i++) (*graph)[i] = realloc((*graph)[i], (*n) * sizeof(int));
	(*name) = realloc((*name), (*n) * sizeof(char));
}
void print(int** graph, char* name, int n) {
	int i, j;
	putchar(' ');
	putchar(' ');
	for (i = 0; i < n; i++) printf("%c ", name[i]);
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%c ", name[i]);
		for (j = 0; j < n; j++) {
			printf("%d ", graph[i][j]);
		}
		putchar('\n');
	}
}
void delete_graph(int*** graph, char** name, int n) {
	int i;
	for (i = 0; i < n; i++)free((*graph)[i]);
	free((*graph));
	free((*name));
}
int is_prev(int** graph, int i, int j) {
	if (graph[i][j] == 1) return 1;
	return 0;

}
int is_posecen(int* poseceni, int i) {
	if (poseceni[i] == 1) return 1;
	return 0;
}
int is_sanja(int k) {
	int i = 0;
	while (i < k) {
		i += 1;
		if (i == k) return 1;
		i += 2;
	}
	if (i == k) return 1;
	return 0;
}
void bfs(int** graph, int n, int k, int k1, char* name, int brm) {
	int broj;
	int poseceni[100];
	int gotovo[100];
	int level[100];
	int red[100];
	int i;
	for (i = 0; i < n; i++) {
		poseceni[i] = 0; level[i] = 0; red[i] = -1;
	}
	gotovo[0] = k;
	int m = 0;
	poseceni[k] = 1;
	red[0] = k;
	broj = 1;
	i = 1;
	int ob, j;
	int s = 0;
	int l;
	int br;
	while (broj > 0) {
		s = 0;
		ob = red[0];
		broj--;
		for (l = 0; l < n - 1; l++) red[l] = red[l + 1];
		for (j = 0; j < n; j++) {
			if (is_prev(graph, ob, j) && (!(is_posecen(poseceni, j)))) {
				for (l = 0; gotovo[l] != ob; l++);
				poseceni[j] = 1;
				m++;
				level[m] = level[l] + 1;
				gotovo[m] = j;
				red[broj] = j;
				broj++;
			}
		}
	}
	for (i = 0; i < n && gotovo[i] >= 0; i++);
	int duz = i;
	for (j = 0; gotovo[j] != k1; j++);
	int kraj = j;
	int v = 0;
	int ispis[100];
	v = 1;
	int obidjeni1[100];
	for (i = 0; i < duz; i++) {
		ispis[i] = -1; obidjeni1[i] = 0;
	}
	m = kraj - 1;
	while (level[m] == level[kraj]) {
		obidjeni1[m] = -1;
		m--;
	}
	ispis[0] = k1;
	for (i = kraj; i > 0; i--) {
		if (obidjeni1[i] != -1) {
			for (j = i - 1; j > 0; j--) {
				if ((level[i] == level[j] + 1) && is_prev(graph, gotovo[j], gotovo[i]) && obidjeni1[j] == 0) {
					ispis[v] = gotovo[j];
					obidjeni1[j] = 1;
					v++;
				}
				else if (!(is_prev(graph, gotovo[j], gotovo[i])) && (level[i] == 1 + level[j]) && level[i] != level[i - 1]) obidjeni1[j] = -1;
			}
		}
	}
	ispis[v] = k;
	v++;
	int level1[100];
	for (i = 0; i < v; i++) {
		for (j = 0; j < duz; j++) {
			if (ispis[i] == gotovo[j]) {
				level1[i] = level[j];
				break;
			}
		}
	}
	printf("Svi Majini putevi: ");
	putchar(name[ispis[0]]);
	putchar('<');
	putchar('-');
	int r = 0;
	for (i = 1; i < v - 1; i++) {
		if (level1[i - 1] == level1[i] || level1[i] == level1[i + 1]) {
			putchar('('); putchar(name[ispis[i]]); putchar(')');
			putchar('-');
			r = 1;
		}
		else {
			if (r == 1) {
				putchar('<');
				putchar('-');
			}
			putchar(name[ispis[i]]);
			putchar('<');
			putchar('-');
			r = 0;
		}

	}
	if (r == 1) {
		putchar('<');
		putchar('-');
	}
	putchar(name[ispis[v - 1]]);
	putchar('\n');
	if (is_sanja(brm)) {
		printf("Svi Sanjini putevi: ");
		putchar(name[ispis[0]]);
		putchar('<');
		putchar('-');
		int r = 0;
		for (i = 1; i < v - 1; i++) {
			if (level1[i - 1] == level1[i] || level1[i] == level1[i + 1]) {
				putchar('('); putchar(name[ispis[i]]); putchar(')');
				putchar('-');
				r = 1;
			}
			else {
				if (r == 1) {
					putchar('<');
					putchar('-');
				}
				putchar(name[ispis[i]]);
				putchar('<');
				putchar('-');
				r = 0;
			}

		}
		if (r == 1) {
			putchar('<');
			putchar('-');
		}
		putchar(name[ispis[v - 1]]);
		putchar('\n');
	}
}
int all_zero(int** x, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (x[i][j] != 0) return 0;
		}
	}
	return 1;

}
int vrati(int** graph, int i);
void sanja(int** graph, int n, char* name, int poc, int kraj) {
	int*** matrica_puta = malloc(n * n * n * sizeof(int**));
	int i, j;
	for (i = 0; i < n * n * n; i++) matrica_puta[i] = malloc(n * sizeof(int*));
	for (i = 0; i < n * n * n; i++) {
		for (j = 0; j < n; j++) {
			matrica_puta[i][j] = malloc(n * sizeof(int));
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			matrica_puta[0][i][j] = graph[i][j];
		}
	}
	int s = 0;
	int k, m, a, b;
	while (1) {
		if (((matrica_puta[s][poc][kraj] != 0) && (is_sanja(s + 1))) || all_zero(matrica_puta[s], n) || s > n * n) break;
		s++;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				matrica_puta[s][i][j] = 0;
			}
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				k = i;
				m = j;
				for (a = 0; a < n; a++) matrica_puta[s][i][j] += matrica_puta[s - 1][k][a] * graph[a][m];
			}
		}

	}
	s += 1;
	if (all_zero(matrica_puta[s - 1], n) || s >= n * n) {
		printf("Sanja ne moze doci do cilja!\n");
	}
	else {
		int sanjini[200];
		int nivoi[200];
		nivoi[0] = 0;
		sanjini[0] = kraj;
		int pamcenje = kraj;
		i = 0; j = 1;
		int k = s - 2;
		int v = 1;
		while (k >= 0) {
			for (i = 0; i < n; i++) {
				if (matrica_puta[k][poc][i] != 0 && is_prev(graph, i, pamcenje)) {
					sanjini[j] = i;
					nivoi[j] = k;
					j++;
				}
			}
			pamcenje = sanjini[j - 1];
			k--;
		}
		sanjini[j] = poc;
		v = j + 1;
		printf("Jedan Sanjin put: ");
		putchar(name[sanjini[0]]);
		putchar('<');
		putchar('-');
		for (i = 1; i < j; i++) {
			if (nivoi[i] != nivoi[i + 1]) {
				putchar(name[sanjini[i]]);
				putchar('<');
				putchar('-');
			}
		}
		putchar(name[sanjini[i]]);
		putchar('\n');
		j = 0;
		i = 0;
		while (i < s) {
			i += 1;
			j += 1;
			if (i == s) break;
			i += 2;
			j += 1;
		}
		printf("Sanji je potrebno %d poteza.\n", j);
		printf("Svi Sanjini putevi: ");
		putchar(name[sanjini[0]]);
		putchar('<');
		putchar('-');
		int r = 0;
		for (i = 1; i < v - 1; i++) {
			if (nivoi[i - 1] == nivoi[i] || nivoi[i] == nivoi[i + 1]) {
				putchar('('); putchar(name[sanjini[i]]); putchar(')');
				putchar('-');
				r = 1;
			}
			else {
				if (r == 1) {
					putchar('<');
					putchar('-');
				}
				putchar(name[sanjini[i]]);
				putchar('<');
				putchar('-');
				r = 0;
			}

		}
		putchar(name[sanjini[i]]);
		putchar('\n');
	}
}
void maja(int** graph, int n, char* name) {
	int w[100][100], i, j, k, brm = 0;
	char t[100][100], a, b;

	k = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) w[i][j] = 0;
			else if (i != j && graph[i][j] == 1) w[i][j] = graph[i][j];
			else w[i][j] = RAND_MAX;
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j || w[i][j] == RAND_MAX) t[i][j] = ' ';
			else t[i][j] = name[i];
		}
	}
	int s = 0;
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (w[i][j] > w[i][k] + w[k][j]) {
					t[i][j] = t[k][j];
					w[i][j] = w[i][k] + w[k][j];
				}
			}
		}
	}
	printf("Unesi pocetni cvor: ");
	scanf(" %c", &a);
	printf("Unesi krajnji cvor: ");
	scanf(" %c", &b);
	for (i = 0; name[i] != a; i++) { if (i == n) break; }
	for (j = 0; name[j] != b; j++) { if (j == n) break; }
	if (j == n || i == n) printf("Takav cvor ne postoji!\n");
	else if (t[i][j] == ' ') printf("Takav put ne postoji!\n");
	else {
		int obidjeni[100];
		int k;
		int s = 0;
		printf("Jedan Majin put: ");
		putchar(b);
		putchar('<');
		putchar('-');
		while (t[i][j] != a) {
			brm++;
			putchar(t[i][j]);
			putchar('<');
			putchar('-');
			for (k = 0; name[k] != t[i][j]; k++);
			j = k;
			s++;

		}
		brm++;
		putchar(a);
		putchar('\n');
		printf("Maji je potrebno %d poteza.\n", brm);
		for (i = 0; name[i] != a; i++);
		for (j = 0; name[j] != b; j++);
		if (is_sanja(brm)) {
			j = 0;
			i = 0;
			while (i < brm) {
				i += 1;
				j += 1;
				if (i == brm) break;
				i += 2;
				j += 1;
			}
			s = 0;
			int l = j;
			for (i = 0; name[i] != a; i++);
			for (j = 0; name[j] != b; j++);
			printf("Jedan Sanjin put: ");
			putchar(b);
			putchar('<');
			putchar('-');
			while (t[i][j] != a) {
				putchar(t[i][j]);
				putchar('<');
				putchar('-');
				for (k = 0; name[k] != t[i][j]; k++);
				j = k;
				s++;
			}
			putchar(a);
			putchar('\n');
			printf("Sanji je potrebno %d poteza.\n", l);
		}
		else {
			sanja(graph, n, name, i, j);
		}
		for (i = 0; name[i] != a; i++);
		for (j = 0; name[j] != b; j++);
		bfs(graph, n, i, j, name, brm);
	}
}
int main() {
	int** graf = NULL;
	int n, i, j, izbor, ind = 0;
	char* name = NULL;
	printf("1.Napravi graf za dati broj cvorova!\n2.Dodaj cvor u graf!\n3.Izbrisi cvor iz grafa!\n"
		"4.Dodaj granu u graf!\n5.Izbrisi granu iz grafa!\n6.Ispisi graf!\n7.Izbrisi graf!\n8.Zapocni igru!\n9.Zavrsi program!\n");
	while (1) {
		printf("Unesi redni broj operacije: ");
		scanf("%d", &izbor);
		if (izbor == 1) {
			printf("Unesi broj cvorova: ");
			scanf("%d", &n);
			graf = make_graph(n);
			name = name_graph(n);
			ind = 1;
		}
		else if (izbor == 2 && graf != NULL) {
			add_node(&graf, &name, &n);
		}
		else if (izbor == 3 && graf != NULL) {
			del_node(&graf, &name, &n);
		}
		else if (izbor == 4 && graf != NULL) {
			add_branch(&graf, name, n);
		}
		else if (izbor == 5 && graf != NULL) {
			del_branch(&graf, name, n);
		}
		else if (izbor == 6 && graf != NULL) {
			print(graf, name, n);
		}
		else if (izbor == 7 && graf != NULL) {
			delete_graph(&graf, &name, n);
			graf = NULL;
		}
		else if (izbor == 8 && graf != NULL) {
			maja(graf, n, name);
		}
		else if (izbor == 9) break;
	}
}