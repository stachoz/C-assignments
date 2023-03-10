#include<stdio.h>
#pragma warning( disable : 4996 )
#pragma warning( disable : 6031 )

#define SIZE_A 5
#define SIZE_B 25

void fill_table(char A[][SIZE_A]) {
	char letter = 'a';
	for (int i = 0; i < SIZE_A; i++) {
		for (int j = 0; j < SIZE_A; j++) {
			if (letter == 'q') {
				A[j][i] = ++letter;
				letter++;
			} 
			else {
				A[j][i] = letter++;
			}
		}
	}
}

void fill_pointer_table(char* B[SIZE_B], char A[][SIZE_A], char input[SIZE_B]) {
	for (int i = 0; i < SIZE_B; i++) {											
		for (int j = 0; j < SIZE_A; j++) {
			for (int k = 0; k < SIZE_A; k++){
				if (input[i] == A[j][k]) {
					B[i] = &A[j][k];
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

void encrypt(char A[][SIZE_A]) {
	for (int i = 0; i < SIZE_A; i++) {
		// pierwszy element = ostatni
		A[0][i] = A[SIZE_A - 1][i];
		for (int j = 1; j < SIZE_A; j++) {
			if (A[j][i] != 'r') {
				A[j][i]--;
			}
			else {
				A[j][i] -= 2;
			}
		}
	}
}

void decrypt(char A[][SIZE_A]) {
	for (int i = 0; i < SIZE_A; i++) {
		// pierwszy element = drugi
		A[0][i] = A[1][i];
		for (int j = 1; j < SIZE_A; j++) {
			if (A[j][i] != 'p') {
				A[j][i]++;
			}
			else {
				A[j][i] += 2;
			}
		}
	}
}

void print_pointed_value(char* B[SIZE_B]) {
	printf("\n");
	for (int i = 0; i < SIZE_B; i++) {
		if (B[i] != NULL) printf("%c", *B[i]);
	}
	printf("\n");
}

int main() {
	char A[SIZE_A][SIZE_A];
	char* B[SIZE_B] = {NULL};
	char input[SIZE_B];
	fill_table(A);
	print_table(A);
	take_input(input);
	fill_pointer_table(B, A, input);

	encrypt(A);
	printf("encrypted: ");
	print_pointed_value(B);

	decrypt(A);
	printf("decrypted: ");
	print_pointed_value(B);
}