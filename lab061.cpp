#include<stdlib.h>
#include<stdio.h>
#include<string.h>


struct meassurement {
	unsigned int meassurement_number;
	unsigned int sensor_number;
	char date_time[20];
	double temp;
	struct meassurement* next;
};

struct result {
	struct meassurement* r1;
	struct meassurement* r2;
	struct meassurement* r3;
	struct meassurement* r4;
};

struct meassurement* init() {
	struct meassurement* m = (struct meassurement*)malloc(sizeof(struct meassurement));
	if (m == NULL) {
		printf("memory error");
		exit(0);
	} 
	return m;
}


struct meassurement* insert(struct meassurement* head, unsigned int meassurement_number, unsigned int sensor_number, char date_time[20], double temp) {
	struct meassurement* new_item = init();
	new_item->meassurement_number = meassurement_number;
	new_item->sensor_number = sensor_number;
	strcpy_s(new_item->date_time, sizeof(new_item->date_time), date_time);
	new_item->temp = temp;
	new_item->next = NULL;
	return new_item;
}

struct meassurement* min_max(struct meassurement* head) {
	struct meassurement* prev_max, * max_node, * current, * prev_min, * min_element;
	struct meassurement* max_element = min_element = head;
	prev_min = prev_max = NULL;
	current = head;
	while (current->next != NULL) {
		if (current->next->temp > max_element->temp) {
			prev_max = current;
			max_element = current->next;
		}
		if (current->next->temp < min_element->temp) {
			prev_min = current;
			min_element = current->next;
		}
		current = current->next;
	}
	if (max_element != head) {
		prev_max->next = max_element->next;
		max_element->next = head;
	}
	if (min_element != head) {
		prev_min->next = min_element->next;
		current->next = min_element;
		min_element->next = NULL;
	}
	return max_element;
}


struct result new_lists(struct meassurement* head) {
	struct meassurement* head_1, * head_2, * head_3, * head_4;
	struct meassurement* last_added_1, *last_added_2, *last_added_3, *last_added_4;
	struct meassurement* new_node = NULL;
	head_1 = head_2 = head_3 = head_4 = NULL;
	last_added_1 = last_added_2 = last_added_3 = last_added_4 = NULL;
	struct meassurement* current = head;
	while (current != NULL) {
		new_node = insert(new_node, current->meassurement_number, current->sensor_number, current->date_time, current->temp);
		if (current->sensor_number == 1) {
			if (head_1 == NULL) {
				head_1 = new_node;
				last_added_1 = head_1;
			}
			else {
				last_added_1->next = new_node;
				last_added_1 = new_node;
			}
		}
		else if (current->sensor_number == 2) {
			if (head_2 == NULL) {
				head_2 = new_node;
				last_added_2 = head_2;
			}
			else {
				last_added_2->next = new_node;
				last_added_2 = new_node;
			}
		}
		else if (current->sensor_number == 3) {
			if (head_3 == NULL) {
				head_3 = new_node;
				last_added_3 = head_3;
			}
			else {
				last_added_3->next = new_node;
				last_added_3 = new_node;
			}
		}
		else if (current->sensor_number == 4) {
			if (head_4 == NULL) {
				head_4 = new_node;
				last_added_4 = head_4;
			}
			else {
				last_added_4->next = new_node;
				last_added_4 = new_node;
			}
		}
		current = current->next;
	}
	struct result r;
	r.r1 = head_1;
	r.r2 = head_2;
	r.r3 = head_3;
	r.r4 = head_4;
	return r;
}

void count_meassurements(struct meassurement* head) {
	int s1, s2, s3, s4;
	s1 = s2 = s3 = s4 = 0;
	struct meassurement* current = head;
	while (current != NULL) {
		if (current->sensor_number == 1) s1++;
		else if (current->sensor_number == 2) s2++;
		else if (current->sensor_number == 3) s3++;
		else if (current->sensor_number == 4) s4++;
		printf("%d %d %s %f\n", current->meassurement_number, current->sensor_number, current->date_time, current->temp);
		current = current->next;
	}
	printf("1 sensor: %d\n", s1);
	printf("2 sensor: %d\n", s2);
	printf("3 sensor: %d\n", s3);
	printf("4 sensor: %d\n", s4);
}

struct meassurement* read_data_to_l_list(char filename[]) {
	FILE* data;
	if (fopen_s(&data, filename, "r") != 0) {
		printf("Cannot open the file");
		exit(0);
	}
	else printf("file is opened\n");
	unsigned int meassurement_number, sensor_number;
	char date_time[20];
	double temp;
	struct meassurement* head, * last_added_item, * new_item;
	head = last_added_item = new_item = NULL;

	while (!feof(data)) {
		fscanf_s(data, "%d %d %s %lf", &meassurement_number, &sensor_number, date_time, unsigned(sizeof(date_time)), &temp);
		if (head == NULL) {
			head = init();
			head->meassurement_number = meassurement_number;
			head->sensor_number = sensor_number;
			strcpy_s(head->date_time, sizeof(head->date_time), date_time);
			head->temp = temp;
			head->next = NULL;
			last_added_item = init();
			last_added_item = head;
		}
		else {
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
	fclose(data);
	return head;
}

int main() {
	char file_name[] = "test.txt";
	struct meassurement* head =  read_data_to_l_list(file_name);
	struct result r = new_lists(head);
	//count_meassurements(head);
	struct meassurement* new_head = min_max(head);
	count_meassurements(new_head);
}