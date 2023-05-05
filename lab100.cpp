#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

class MojaKlasa {
	char** email;
	int ile;
	MojaKlasa* nast;
public:
	MojaKlasa(int x);
	MojaKlasa(MojaKlasa& mk);	// konstruktor kopiuj¹cy
	// void setmail(char* adres, ...
	void setemail(const char* adres, int idx) { strcpy(email[idx], adres); }
	char* getemail(int idx) { return email[idx]; }
	int getile() { return ile; }
	MojaKlasa* getnast() { return nast; }
	void setnast(MojaKlasa* nast) { this->nast = nast; }
};

MojaKlasa::MojaKlasa(int x) {
	email = new char* [ile = x];
	for (int i = 0; i < ile; i++) email[i] = new char[100];
}

/*
*/
MojaKlasa::MojaKlasa(MojaKlasa& mk) {
	email = mk.email;			// czy to jest OK?
}

/*
MojaKlasa::MojaKlasa(MojaKlasa& mk) {
	email = new char*[mk.ile];
	ile = mk.ile;
	for (int i=0;i<ile;i++) {
		email[i] = new char[100];
		strcpy(email[i],mk.email[i]);
	}
}
*/

class Wykladowca {
private:
	MojaKlasa* klasy; // lista klas danego wykladowcy
public:
	Wykladowca() : klasy(NULL) {};
	Wykladowca(const char* plik) {
		dodajKlase(plik);
	}
	Wykladowca(Wykladowca* w) {
		if (w->klasy == NULL) {
			klasy = NULL;
		}
		else {
			MojaKlasa* glowa = w->getKlasy();
			while(glowa != NULL){
				int l_osob = glowa->getile();
				MojaKlasa* kopia = new MojaKlasa(l_osob);
				kopia->setnast(NULL);
				for (int i = 0; i < l_osob; i++) {
					kopia->setemail(glowa->getemail(i), i);
				}
				if (klasy == NULL) klasy = kopia;
				else klasy->setnast(kopia);
				glowa = glowa->getnast();
			}
		}
	}
	~Wykladowca() {
		while (klasy != NULL) {
			MojaKlasa* tmp = klasy;
			klasy = klasy->getnast();
			delete tmp;
		}
	}
	MojaKlasa* getKlasy() { return klasy; }
	void wypisz() {
		MojaKlasa* glowa = klasy;
		while (glowa != NULL) {
			int liczba_osob = klasy->getile();
			for (int i = 0; i < liczba_osob - 1; i++) {
				printf("%s\n", klasy->getemail(i));
			}
			glowa = glowa->getnast();
		}
	}
	void dodajKlase(const char* plik) {
		FILE* file = nullptr;
		file = fopen(plik, "r");
		if (file == NULL) {
			printf("failed to open a file\n");
			exit(0);
		}
		else {
			printf("file is opened\n");
		}
		int ile = countLines(file);
		MojaKlasa* nowy = new MojaKlasa(ile);
		for (int i = 0; i < ile && !feof(file); i++) {
			char buf[100];
			fscanf(file, "%s", buf);
			nowy->setemail(buf, i);
		}
		klasy = nowy;
		fclose(file);
	}
private:
	int countLines(FILE* file) {
		int lines = 0;
		while (!feof(file)) {
			char buf[100];
			fscanf(file, "%s", buf);
			lines++;
		}
		rewind(file);
		return lines;
	}
};
int main() {
	/*
	MojaKlasa MK(3);
	MK.setemail("k.trojanowski@uksw.edu.pl", 0);
	MojaKlasa MK2(MK);
	printf("%s\n", MK2.getemail(0));
	MK.setemail("m.mikolajczyk@uksw.edu.pl", 1);
	printf("%s\n", MK2.getemail(1));
	*/
	Wykladowca* wykladowca = new Wykladowca("plik.txt");
	wykladowca->wypisz();
	Wykladowca* w1 = new Wykladowca(wykladowca);
	delete(wykladowca);
	w1->wypisz();


	
	return 0;
}