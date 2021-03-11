// CHELCEA CLAUDIU MARIAN

#include <stdio.h>
#include <stdlib.h>
#define NMAX 100000

// Give answer
void display(int exit)
{
	if (exit == 0)
		printf("Eroare\n");
	else if (exit == 1)
		printf("Corect\n");
}

// Check columns
// a = nr of rows, b = nr cols, ngr = nr_goups_row, dim_row = dr
int check_cols(int a, int b, int n[a][b], int *ngr, int *dr)
{
	int is_true = 1;
	int group = 0, position = 0, nr_of_1 = 0;

	// Check each column element by element
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			group = 0;
			nr_of_1 = 0;
			// Skip the 0 gropus
			while (n[i][j] == 0 && j < b)
				j++;
			// Go to the end of the "1" group
			while (n[i][j] == 1 && j < b) {
				j++;
				nr_of_1++;
			}
			// If there are more groups than the allowed ones, exit
			if (nr_of_1 != 0 && group >= ngr[i]) {
				is_true = 0;
				break;
			}
			// If the size of the group is equal to the number of 1, count it
			if (nr_of_1 != 0 && nr_of_1 == dr[position]) {
				group++;
				position++;
			}
			// If we have 1. but it`s not in the same group, reiterate
			if (nr_of_1 != 0 && nr_of_1 != dr[position - 1]) {
				is_true = 0;
				break;
			}
		}
	}
	return is_true;
}

// Check each line, where: a = nr_rows, b =nr_col, nc = nr_groups_col
// ngr=nr_groups_row, dc = dim_col, dr = dim_rows
int check_rows(int a, int b, int n[a][b], int *ngc, int *ngr, int *dr, int *dc)
{
	int is_true = 0;
	is_true = check_cols(a, b, n, ngr, dr);
	int group = 0, nr_of_1 = 0, position = 0;
	for (int i = 0; i < b; i++) {
		for (int j = 0; j < a; j++) {
			group = 0;
			nr_of_1 = 0;
			
			// The same stages as earlier, but on rows
			while (n[j][i] == 0 && j < a) 
				j++;	
			while (n[j][i] == 1 && j < a) {
				j++;
				nr_of_1++;
			}
			
			if (nr_of_1 != 0 && group >= ngc[i]) {
				is_true = 0;
				break;
			}
			if (nr_of_1 != 0 && nr_of_1 == dc[position]) {
				group++;
				position++;
			}
			if (nr_of_1 != 0 && nr_of_1 != dc[position - 1]) {
				is_true = 0;
				break;
			}
		}
	}
	return is_true;
}

int main(void)
{
	// Defining and declaring the number of griddlers and the exit variable
	int nr_griddlers = 0, nr_l = 0, nr_c = 0, exit = 0;
	scanf("%d", &nr_griddlers);
	
	// Defining the number of groups on rows and cols
	int *nr_groups_row = NULL, *dim_r = NULL, *nr_groups_col = NULL, *dim_c = NULL;
	int dim_1=1;
	nr_groups_row = malloc(dim_1 * sizeof(int));
	int dim_2=1;
	dim_r = malloc(dim_2 * sizeof(int));
	int dim_3=1;
	nr_groups_col = malloc(dim_3 * sizeof(int));
	int dim_4=1;
	dim_c = malloc(dim_4 * sizeof(int));

	// The main loop executed for each griddler
	for (int index = 0; index < nr_griddlers; index++) {
		exit = 1;
		scanf("%d", &nr_l);
		fflush(stdin);
		scanf("%d", &nr_c);
		int q = 0, n = 0;
		int griddlers[nr_l][nr_c];

		// Save in nr_groups_row array the nr. of groups on those rows
     	// And in dim_r array we save their dimension. Ex: 2-> (2 1); 2->(1 1);
		for (int i = 0; i < nr_l; i++) {
			scanf("%d", &nr_groups_row[i]);
			dim_1++;
			nr_groups_row = realloc(nr_groups_row, dim_1 * sizeof(int));
			n = q;
			for (; q < (n + nr_groups_row[i]); q++) {
				scanf("%d", &dim_r[q]);
				dim_2++;
				dim_r = realloc(dim_r, dim_2 * sizeof(int));
			}
		}

		// The same method applies for the columns
		q = 0;
		for (int i = 0; i < nr_c; i++) {
			scanf("%d", &nr_groups_col[i]);
			dim_3++;
			nr_groups_col = realloc(nr_groups_col, dim_3 * sizeof(int));
			n = q;
			for (; q < (n + nr_groups_col[i]); q++) {
				scanf("%d", &dim_c[q]);
				dim_4++;
				dim_c = realloc(dim_c, dim_4 * sizeof(int));

			}
		}

		// Scanning the grid
		for (int i = 0; i < nr_l; i++)
			for (int j = 0; j < nr_c; j++)
				scanf("%d", &griddlers[i][j]);

		// Checking the grid
		exit = check_rows(nr_l, nr_c, griddlers, nr_groups_col, nr_groups_row, dim_r, dim_c);

		// Show result
		display(exit);

		// Loop again if there are more griddlers
	}

	// Free allocated space
	free(nr_groups_row);
	free(nr_groups_col);
	free(dim_r);
	free(dim_c);

	return 0;
}