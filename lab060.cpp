#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct meassurement {
	unsigned int meassurement_number;
	unsigned int sensor_number;
	char date_time[20];
	double temp;
	struct meassurement* next;
};

struct meassurement* init() {
	struct meassurement* m = (struct meassurement*)malloc(sizeof(struct meassurement));
	if (m == NULL) {
		printf("Memory error;");
		exit(0);
	}
	return m;
}

int main() {
	char file_name[20] = "data.txt";
	FILE* f;
	if (fopen_s(&f, file_name, "r") != 0) {
		printf("cannot open a file\n");
		exit(0);
	}
	else {
		printf("file is opened\n");
	}

	unsigned int meassurement_number;
	unsigned int sensor_number;
	char date_time[20];
	double temp;
	struct meassurement* head, * last_added_item, * new_item;
	head = last_added_item = new_item = NULL;

	while (fscanf_s(f, "%d %d %s %lf", &meassurement_number, &sensor_number, date_time, (unsigned(sizeof(date_time))), &temp) == 4) {
		if (head == NULL) { // first element 
			head = init();
			head->meassurement_number = meassurement_number;
			head->sensor_number = sensor_number;
			strcpy_s(head->date_time, sizeof(head->date_time), date_time);
			head->temp = temp;
			head->next = NULL;
			last_added_item = init();
			last_added_item = head;
		}
		else { // add element 
			new_item = init();
			last_added_item->next = new_item;
			new_item->meassurement_number = meassurement_number;
			new_item->sensor_number = sensor_number;
			strcpy_s(new_item->date_time, date_time);
			new_item->temp = temp;
			new_item->next = NULL;
			last_added_item = new_item;
		}
	}
	FILE* r1, * r2, * r3, * r4;
	char file_name_input[40];
	char full_name_file[80];
	printf("Enter file name header: ");
	while (scanf_s("%s", file_name_input, 40) != 1) {
		printf("invalid data, enter again: ");
		while (getchar() != '\n')
			;
	}
	for (int i = 1; i < 5; i++) {
		sprintf_s(full_name_file, "%s%d.txt", file_name_input, i);
		if (i == 1) {
			if (fopen_s(&r1, full_name_file, "w") != 0) printf("file is opened\n");
			else printf("cannot open file\n");
		}
		if (i == 2) {
			if (fopen_s(&r1, full_name_file, "w") != 0) printf("file is opened\n");
			else printf("cannot open file\n");
		}
		if (i == 3) {
			if (fopen_s(&r1, full_name_file, "w") != 0) printf("file is opened\n");
			else printf("cannot open file\n");
		}
		if (i == 4) {
			if (fopen_s(&r1, full_name_file, "w") != 0) printf("file is opened\n");
			else printf("cannot open file\n");
		}
	}

	struct meassurement* sensor1_head, * sensor2_head, * sensor3_head, * sensor4_head;
	sensor1_head = sensor2_head = sensor3_head = sensor4_head = NULL;
	struct meassurement* current = head;
	int sensor1_counter, sensor2_counter, sensor3_counter, sensor4_counter;
	sensor1_counter = sensor2_counter = sensor3_counter = sensor4_counter = 0;
	while (current->next != NULL) {
		if (current->sensor_number == 1) {
			sensor1_head = init();
			sensor1_head->meassurement_number = current->meassurement_number;
			sensor1_head->sensor_number = current->sensor_number;
			strcpy_s(sensor1_head->date_time, sizeof(sensor1_head->date_time), current->date_time);
			sensor1_head->temp = current->temp;
			sensor1_head->next = NULL;
			sensor1_head = current;
			sensor1_counter++;
		}
		else if (current->sensor_number == 2) {
			sensor2_head = init();
			sensor2_head->meassurement_number = current->meassurement_number;
			sensor2_head->sensor_number = current->sensor_number;
			strcpy_s(sensor2_head->date_time, sizeof(sensor2_head->date_time), current->date_time);
			sensor2_head->temp = current->temp;
			sensor2_head->next = NULL;
			sensor2_head = current;
			sensor2_counter++;
		}
		if (current->sensor_number == 3) {
			sensor3_head = init();
			sensor3_head->meassurement_number = current->meassurement_number;
			sensor3_head->sensor_number = current->sensor_number;
			strcpy_s(sensor3_head->date_time, sizeof(sensor3_head->date_time), current->date_time);
			sensor3_head->temp = current->temp;
			sensor3_head->next = NULL;
			sensor3_head = current;
			sensor3_counter++;
		}
		if (current->sensor_number == 4) {
			sensor4_head = init();
			sensor4_head->meassurement_number = current->meassurement_number;
			sensor4_head->sensor_number = current->sensor_number;
			strcpy_s(sensor4_head->date_time, sizeof(sensor4_head->date_time), current->date_time);
			sensor4_head->temp = current->temp;
			sensor4_head->next = NULL;
			sensor4_head = current;
			sensor4_counter++;
		}
		current = current->next;
	}
	printf("sensor 1: %d\n", sensor1_counter);
	printf("sensor 2: %d\n", sensor2_counter);
	printf("sensor 3: %d\n", sensor3_counter);
	printf("sensor 4: %d\n", sensor4_counter);
}