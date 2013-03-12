/* ============================================
 * Word Length Histogram v1.0 
 * ============================================
 *
 * Reads text file and prints histogram of the
 * frequencies of the word lengths in the file.
 *
 * Written by: Matthew Schmoyer
 * Date: March 11, 2013
 * ============================================
 */ 

#include <stdio.h>
#include <ctype.h>

#define LENGTH 16

/* Function to itialize count_a to all 0s */
void init_array(int count_a[]);

/* Prompts user asking if they want a vertical histogram.
 * Returns 1 if yes, 0 if no. */
int check_vert();

/* Reads text file f and fills count_a with frequencies
 * of the word lengths in f */
int fill_hist(int count_a[], char f[]);

/* Function to test if character is punctuation.
 * Returns 1 if ch is punctuation.  Returns 0 otherwise */
int pun_test(char ch);

/* Prints a horizontal histogram of values in count_a */
void print_hist_hor(int count_a[]);

/* Prints a vertical histogram of values in count_a */
void print_hist_ver(int count_a[]);

/* Returns max value in count_a */
int max_a(int count_a[]);

int main(int argc, char *argv[]) {
	int count_a[LENGTH]; /* Stores frequencies */
	int vert;
	init_array(count_a); /* Initialize count_a to all 0s */
	
	/* Check for passed file argument */
	if (argc != 2) {
		printf("Error: Missing argument.\n");
		return(-1);
	}
	else {
		if (fill_hist(count_a, argv[1])) {
			if (check_vert())
				print_hist_ver(count_a);
			else
				print_hist_hor(count_a);
		}
	}
	
	return(0);
}

void init_array(int count_a[]) {
	int i;
	for (i=0; i < LENGTH; i++)
		count_a[i] = 0;
}

int check_vert() {
	char vert;
	printf("Vertical histogram? [Y/n] ");
		vert = getchar();
		while (toupper(vert) != 'Y' && toupper(vert) != 'N') {
			printf("Invalid response.  Enter y or n: ");
			getchar();
			vert = getchar();
		}
	if (toupper(vert) == 'Y')
		return(1);
	else
		return(0);
}

int fill_hist(int count_a[], char f_path[]) {
	char ch;
	int count = 0;
	FILE *f_in = fopen(f_path, "r");
	if (f_in == 0)
		printf("Error: No File.\n");
	else {
		while ((ch = fgetc(f_in)) != EOF) {
			if (ch == ' ' || ch == '\n' || ch == '\t') {
				count_a[count]++;
				count = 0;
			}
			else
				if (!pun_test(ch))
					count++; 
		}
		fclose(f_in);
		return(1);
	}
	// File did not work
	return(0);
}

int pun_test(char ch) {
	switch (ch) {
		case '\'':
			return(1);
		case '.':
			return(1);
		case ',':
			return(1);
		case '\"':
			return(1);
		case '-':
			return(1);
		case '\?':
			return(1);
		case '!':
			return(1);
		default:
			return(0);
	}
	// Not punctuation
	return(0);
}

void print_hist_hor(int count_a[]) {
	int i, j;
	for (i=1; i < LENGTH; i++) {
		printf("%2d", i);
		printf(" ");
		for (j=0; j < count_a[i]; j++)
			printf("*");
		printf(" %d\n", count_a[i]);
	}
}

void print_hist_ver(int count_a[]) {
	int i, j;
	for (i = max_a(count_a); i > 0; i--) {
		for (j = 1; j < LENGTH; j++) {
			if (count_a[j] < i)
				printf(" ");
			else
				printf("*");
			if (j < 10)
				printf(" "); /* Spacing between columns */
			else
				printf("  ");
		}
		printf("\n");
	}
	for (i = 1; i < LENGTH; i++)
		printf("%d ",i);
	printf("\n");
}

int max_a(int count_a[]) {
	int i, max;
	max = count_a[1]; /* Don't count 0 length words */
	for (i=2; i < LENGTH; i++) {
		if (count_a[i] > max)
			max = count_a[i];
	}
	return(max);
}
