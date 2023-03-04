#include<stdio.h>
#pragma warning( disable : 4996 )
#pragma warning( disable : 6031 )

#define SIZE_A 5
#define SIZE_B 25

void fill_table(char A[][SIZE_A]) {
	char letter = 'a';
	for (int i = 0; i < SIZE_A; i++) {
		for (int j = 0; j < SIZE_A; j++) {
			if (letter == 'v') {
				A[i][j] = ++letter;
				letter++;
			} 
			else {
				A[i][j] = letter++;
			}
		}
	}
}

void fill_pointer_table(char* B[SIZE_B], char A[][SIZE_A], char input[SIZE_B], int *lenght) {
	for (int i = 0; i < SIZE_B; i++) {											
		for (int j = 0; j < SIZE_A; j++) {
			for (int k = 0; k < SIZE_A; k++){
				if (input[i] == A[j][k]) {
					B[i] = &A[j][k];
					(*lenght)++;
				}
			}
		}
	}
}

void print_table(char A[][SIZE_A]) {
	printf("\n");
	for (int i = 0; i < SIZE_A; i++) {
		for (int j = 0; j < SIZE_A; j++) {
			printf("%c ", A[i][j]);
		}
		printf("\n");
	}
}

void take_input(char input[SIZE_B]) {
	printf("Enter a word: ");
	scanf_s("%s", input, SIZE_B);
}

void encrypt(char *B[SIZE_B], char **C[SIZE_B], int length) {
	int c_index = 0; 
	for (int i = length - 1; i >= 0 && B[i] != NULL; i--) {
		C[c_index] = &B[i];
		c_index++;
	}
}

void print_pointed_value(char** C[SIZE_B]) {
	printf("\n");
	for (int i = 0; i < SIZE_B && C[i] != NULL; i++) {
		printf("%c", **C[i]);
	}
	printf("\n");
}

int main() {
	int lenght = 0; 
	char A[SIZE_A][SIZE_A];
	char* B[SIZE_B] = { NULL };
	char T[SIZE_B];
	char** C[SIZE_B] = { NULL };
	fill_table(A);
	print_table(A);
	take_input(T);
	fill_pointer_table(B, A, T, &lenght);
	encrypt(B, C, lenght);
	printf("encrypted: ");
	print_pointed_value(C);
}
