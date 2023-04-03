#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct pomiar {
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar* nast;
	struct pomiar* poprz;
};

struct lista {
	struct pomiar* glowa;
	struct pomiar* ogon;
};

struct listy_4 {
	struct pomiar* glowa1;
	struct pomiar* glowa2;
	struct pomiar* glowa3;
	struct pomiar* glowa4;
};

struct pomiar* init() {
	struct pomiar* p = (struct pomiar*) malloc(sizeof(struct pomiar));
	if (p == NULL) {
		printf("blad pamiec");
		exit(0);
	} 
	return p;
}

struct pomiar* dodaj(struct pomiar* head, unsigned int nr_pomiaru, unsigned int nr_czujnika, char data_i_czas[], double temp) {
	struct pomiar* nowy = init();
	nowy->nr_pomiaru = nr_pomiaru;
	nowy->nr_czujnika = nr_czujnika;
	strcpy_s(nowy->data_i_czas, sizeof(nowy->data_i_czas), data_i_czas);
	nowy->temp = temp;
	nowy->nast = NULL;
	nowy->poprz = NULL;
	return nowy;
}

struct lista wczytaj(char nazwa_pliku[]) {
	FILE* f = NULL;
	if (fopen_s(&f, nazwa_pliku, "r") != 0) {
		printf("cannot open a file");
		exit(0);
	}
	else {
		printf("file is opened\n");
	}
	unsigned int nr_pomiaru;
	unsigned int nr_czujnika;
	char data_i_czas[20];
	double temp;
	struct pomiar* glowa, * ostatni, *nowy;
	glowa = ostatni = nowy = NULL;

	while (!feof(f)) {
		if (fscanf_s(f, "%d %d %s %lf", &nr_pomiaru, &nr_czujnika, data_i_czas, unsigned(sizeof(data_i_czas)), &temp) == 4) {
			if (glowa == NULL) {
				glowa = dodaj(glowa, nr_pomiaru, nr_czujnika, data_i_czas, temp);
				ostatni = glowa;
			}
			else {
				nowy = dodaj(nowy, nr_pomiaru, nr_czujnika, data_i_czas, temp);
				nowy->poprz = ostatni;
				ostatni->nast = nowy;
				ostatni = nowy;
			}
		}
	}
	struct lista l;
	l.glowa = glowa;
	l.ogon = ostatni;
	return l;
}


struct listy_4 podziel(struct pomiar* glowa) {
	struct pomiar* glowa_1, * glowa_2, * glowa_3, * glowa_4;
	struct pomiar* ostatni_1, *ostatni_2, *ostatni_3, *ostatni_4;
	struct pomiar* nowy = NULL;
	glowa_1 = glowa_2 = glowa_3 = glowa_4 = NULL;
	ostatni_1 = ostatni_2 = ostatni_3 = ostatni_4 = NULL;
	struct pomiar* current = glowa;
	while (current != NULL) {
		nowy = dodaj(nowy, current->nr_pomiaru, current->nr_czujnika, current->data_i_czas, current->temp);
		if (current->nr_czujnika == 1) {
			if (glowa_1 == NULL) {
				glowa_1 = nowy;
				ostatni_1 = glowa_1;
			}
			else {
				ostatni_1->nast = nowy;
				nowy->poprz = ostatni_1;
				ostatni_1 = nowy;
			}
		}
		else if (current->nr_czujnika == 2) {
			if (glowa_2 == NULL) {
				glowa_2 = nowy;
				ostatni_2 = glowa_2;
			}
			else {
				ostatni_2->nast = nowy;
				nowy->poprz = ostatni_2;
				ostatni_2 = nowy;
			}
		}
		else if (current->nr_czujnika== 3) {
			if (glowa_3 == NULL) {
				glowa_3 = nowy;
				ostatni_3 = glowa_3;
			}
			else {
				ostatni_3->nast= nowy;
				nowy->poprz = ostatni_3;
				ostatni_3 = nowy;
			}
		}
		else if (current->nr_czujnika == 4) {
			if (glowa_4 == NULL) {
				glowa_4 = nowy;
				ostatni_4 = glowa_4;
			}
			else {
				ostatni_4->nast = nowy;
				nowy->poprz = ostatni_4;
				ostatni_4 = nowy;
			}
		}
		current = current->nast;
	}
	struct listy_4 l;
	l.glowa1 = glowa_1;
	l.glowa2 = glowa_2;
	l.glowa3 = glowa_3;
	l.glowa4 = glowa_4;
	return l;

}

void wypisz(struct pomiar* p) {
	struct pomiar* aktualny = p;
	struct pomiar* ostatni = NULL;

	while (aktualny != NULL) {
		printf("%d %d %s %.2f\n", aktualny->nr_pomiaru, aktualny->nr_czujnika, aktualny->data_i_czas, aktualny->temp);
		if (aktualny->nast == NULL) ostatni = aktualny;
		aktualny = aktualny->nast;
	}
	printf("\n od konca \n");
	while (ostatni != NULL) {
		printf("%d %d %s %.2f\n", ostatni->nr_pomiaru, ostatni->nr_czujnika, ostatni->data_i_czas, ostatni->temp);
		ostatni = ostatni->poprz;
	}
	
}

void max(struct pomiar* glowa) {
	struct pomiar* aktualny = glowa;
	struct pomiar* max_rekord = aktualny;
	struct pomiar* min_rekord = aktualny;
	struct pomiar* ostatni = NULL;
	while (aktualny != NULL) {
		if (aktualny->temp > max_rekord->temp) max_rekord = aktualny;
		if (aktualny->temp < min_rekord->temp) min_rekord = aktualny;
		if (aktualny->nast == NULL) ostatni = aktualny;
		aktualny = aktualny->nast;
	}
	struct pomiar* nowy = NULL;
	nowy = dodaj(nowy, max_rekord->nr_pomiaru, max_rekord->nr_czujnika, max_rekord->data_i_czas, max_rekord->temp);
	ostatni->nast = nowy;
	nowy->poprz = ostatni;;
	nowy->nast = NULL;
	ostatni = nowy;
	// min
	nowy = dodaj(nowy, min_rekord->nr_pomiaru, min_rekord->nr_czujnika, min_rekord->data_i_czas, min_rekord->temp);
	ostatni->nast = nowy;
	nowy->poprz = ostatni;;
	nowy->nast = NULL;
	ostatni = nowy;
}

void wypisz_od_konca(struct pomiar* p) {
	struct pomiar* aktualny = p;
	while (aktualny != NULL) {
		printf("%d %d %s %.2f\n", aktualny->nr_pomiaru, aktualny->nr_czujnika, aktualny->data_i_czas, aktualny->temp);
		aktualny = aktualny->poprz;
	}
	struct pomiar* ostatni = aktualny;
}

void policz(struct pomiar* glowa) {
	int ile = 0;
	struct pomiar* aktualny = glowa;
	while (aktualny != NULL) {
		ile++;
		aktualny = aktualny->nast;
	}
	printf("liczba pomiarow: %d\n", ile);

}

int main() {
	char nazwa_pliku[] = "test.txt";
	struct lista l = wczytaj(nazwa_pliku);
	struct pomiar* glowa = l.glowa;
	struct pomiar* ogon = l.ogon;
	policz(glowa);
	struct listy_4 listy = podziel(glowa);
	struct pomiar* g1 = listy.glowa1;
	struct pomiar* g2 = listy.glowa2;
	struct pomiar* g3 = listy.glowa3;
	struct pomiar* g4 = listy.glowa4;
	wypisz(g1);
	printf("\n");
	max(g1);
	wypisz(g1);
}




