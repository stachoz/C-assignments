#include<stdio.h>
#include<string.h>
#include<Windows.h>

#define size 5
#define string_size 10

struct s {
	char string[string_size];
	int num;
};

int main() {
	struct s tab[size];
	for (int i = 0; i < size; i++) {
		printf("Enter num: ");
		scanf_s("%d", &tab[i].num);
		printf("Enter word: ");
		scanf_s("%s", &tab[i].string, string_size);
	}
	int shortening_num = check_tab(tab);
	for (int i = 0; i < size; i++) {
		printf("%d %s\n", tab[i].num, tab[i].string);
	}
	printf("Strings were reduced %d times", shortening_num);
	//system("pause");
}

int check_tab(struct s tab[size]) {
	int shortening_num = 0;
	for (int i = 0; i < size; i++) {
		int lenght = strlen(tab[i].string);
		int num = tab[i].num;
		if(num < lenght){
			tab[i].string[num] = '\0';
			shortening_num++;
			for (int j = i + 1; j < string_size; j++) {
				tab[i].string[j] = NULL;
			}
		}
	}	
	return shortening_num;
}