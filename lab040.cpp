#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define F 50 // max lenght of filename input 
#define L 15 // string lenght
#define M 5  // struct tab lenght

struct pair {
	char string[L];
	int num;
};

void take_file_name(char file[F]) {
	scanf_s("%s", file, F);
}

void isOpeningSuccessull(FILE* file) {
	if (file == NULL) {
		printf("error, cannot oepn a file\n");
	}
	else {
		printf("file is open\n");
	}
}

int is_vowel(char c) {
	char vowels[] = { 'a', 'e', 'i', 'o', 'u' };
	for (int i = 0; i < strlen(vowels); i++) {
		if (c == vowels[i]) return 1;
	}
	return 0; 
}

void encrypt(char string[L]) {
	int str_lenght = strlen(string);
	for (int i = 0; i < str_lenght; i++) {
		if (is_vowel(string[i])) {
			string[i] = '*';
		}
	}
}

void read(FILE* data, struct pair tab[L], int* word_counter, int* grade_counter, int* surnmae_counter) {
	char buf[30];
	fscanf(data, "%s", buf);
	if (!(*word_counter % 3 == 0)){ // read surnames and grades but skip indexes
		if (isdigit(buf[0])) {
			int ascii_num = (int)buf[0];
			int num = ascii_num - 48; // convert ascii num to digit representation
			tab[*grade_counter].num = num;
			(*grade_counter)++;
		}
		else {
			strcpy(tab[*surnmae_counter].string, buf);
			(*surnmae_counter)++;
		}
	}
}

int main() {
	char data_file_name[F];
	char result_file_name[F];
	struct pair tab[M];
	printf("Enter fullname of file with data: ");
	take_file_name(data_file_name);
	printf("Enter fullname of file to save the data to: ");
	take_file_name(result_file_name);

	FILE* data = fopen(data_file_name, "r");
	FILE* result = fopen(result_file_name, "w");
	isOpeningSuccessull(data);
	isOpeningSuccessull(result);

	int grade_counter = 0;
	int surname_counter = 0;
	int word_counter = 0;
	while (!feof(data)) {
		read(data, tab, &word_counter, &grade_counter, &surname_counter); 
		word_counter++;
	}
	// print data
	for (int i = 0; i < 5; i++) {
		printf("%s ", tab[i].string);
		printf("%d\n", tab[i].num);
	}

	// write data to file
	for (int i = 0; i < M; i++) {
		encrypt(tab[i].string);
		fprintf(result, "%s %d\n", tab[i].string, tab[i].num);
	}
}