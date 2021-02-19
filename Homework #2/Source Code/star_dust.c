// Chelcea Claudiu Marian
#include "support.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define word 8
 
int main(void) {

	// TASK 1
	int nr_of_rows = 0, dim = 0;                               
	scanf("%d", &nr_of_rows);

	// Initializare valori
	int *nr_el_lin = NULL;
	init_p_int(&nr_el_lin, nr_of_rows);
	char *input = NULL;
	init_char_pointer(&input, 9);
	char **list_el = NULL;
	init_pointer_2_pointer(&list_el, dim);

	// Save in nr_el_lin[i] = 4 3 1 2 -- the number of elements on rows
	// Save in list_el[nr_el] this number
	// nr_el will represent the number of elements, p is auxiliar
	int p = 0, nr_el = 0;
	for (int i = 0; i < nr_of_rows; i++) {
		scanf("%d", &nr_el_lin[i]);
		p = nr_el;
		for (; nr_el < (p + nr_el_lin[i]); nr_el++) {
			dim += 1;
			list_el = realloc(list_el, dim * sizeof(char *));
			scanf("%s", input);
			list_el[nr_el] = (char *)malloc(word * sizeof(char));
			for (int re = 0; re < word; re++)
				list_el[nr_el][re] = input[re];
		}
	}

	// Reverse all elements
	reverse_an_element(nr_el, list_el);

	// Show task 1 results
	printf("task 1\n");
	printf("%.8lf\n", margin_arithmetic_mean(&nr_el_lin, &list_el, nr_of_rows));

	// Free
	free(input);

	// TASK 2
	printf("task 2\n");
	int nr_commands = 0, poz_mat = 0, dim_el = 0, necessary_ints = 0, row = 0,
		idx = 0, new_nr_el = 0, dif = 0, stop = -1, sum1 = 0,
		sum2 = 0;

	// Definitions
	char *val = NULL;
	init_char_pointer(&val, 9);
	char *vect_null = NULL;
	init_char_pointer(&vect_null, word);

	char key, type, empty_space;
	scanf("%d", &nr_commands); // Number of commands (M / S / D)
	scanf("%c", &empty_space); // Get rid of the first space

	// Start
	for (int contor = 0; contor < nr_commands; contor++) {
		// For each key
		if (contor >= 1)
			for (int qp = 0; qp < 2; qp++)
				scanf("%c", &key); // Take space, then key
		else
			scanf("%c", &key); // If there is no space, get only the key
		for (int i = 0; i < 2; i++)
			scanf("%c", &type); // Get key type

		// 3 possible cases: M, S, D

		switch (key) {
		case 'M': // Modify():
			scanf("%d %d", &row, &idx);
			scanf("%s", val); // The value we want to modify with
			poz_mat = 0;
			necessary_ints = 0;
			dim_el = 0;
			new_nr_el = 0;
			dif = 0;
			sum1 = 0;
			sum2 = 0;
			row += 1; 

			// Find the position of the first element
			for (int repet = 0; repet < (row - 1); repet++) {
				poz_mat += (int)nr_el_lin[repet];
			}

			// Dimensiuon of the element: INT -> 4, SHORT -> 2, CHAR -> 1
			dim_el = el_dim_by_type(type);

			// How many int elements are needed
			necessary_ints = how_much_to_add(nr_el_lin, row, dim_el, idx);

			// For the modify operation there are 4 cases:

			// CASE 1 (We need to add "0" and we are not on the last row):
			if (necessary_ints != 0 && row != nr_of_rows) {
				// nr_el = number of initial elements
				// new_nr_el = nr_el + the number of "00000000" added
				nr_el = dim;

				// Make space at the end of the list
				for (int i = nr_el; i < (nr_el + necessary_ints); i++) {
					dim += 1;
					list_el = realloc(list_el, dim * sizeof(char *));
					list_el[i] = (char *)malloc(word * sizeof(char));
					for (int re = 0; re < word; re++)
						list_el[i][re] = vect_null[re];
					new_nr_el = i + 1;
				}

				// The number of "00000000" needed
				dif = new_nr_el - nr_el;

				// We add it to the last row
				nr_el_lin[nr_of_rows - 1] += dif;

				// How many elements are between the end and our position
				for (int i = row; i < nr_of_rows; i++)
					sum1 += nr_el_lin[i];

				// Shift everything to the right by "dif" positions
				for (int j = 0; j < dif; j++) {
					stop = -1;
					for (int i = (dim - 1);; i--) {
						stop++;
						if ((sum1 - stop - 1) == 0)
							break;
						for (int re = 0; re < word; re++)
							list_el[i][re] = list_el[i - 1][re];
					}
				}

				// Get the pos where we want to insert our element
				for (int i = 0; i < row; i++)
					sum2 += nr_el_lin[i];

				for (int i = sum2; i < (sum2 + dif); i++) {
					for (int re = 0; re < word; re++)
						list_el[i][re] = '0';
				}

				// Change rows dimensions
				nr_el_lin[row - 1] += dif;
				nr_el_lin[nr_of_rows - 1] -= dif;

				// In function of our modifications, we want to apply it 
				// to the matrix
				dim_el = el_dim_by_type(type);
				poz_mat = find_poz_mat(dim_el, idx, poz_mat);
				idx = find_index(dim_el, idx, poz_mat);

				// Reverse by element type
				modify_matrix(dim_el, idx, &list_el, val, poz_mat, type);

				// CASE 2 (we need to add "0" and we are on the last row")

			} else if (necessary_ints != 0 && row == nr_of_rows) {
				// The same method, only that we no longer need to insert
				// in the middle
				nr_el_lin[row - 1] += necessary_ints;

				// MAke the needed space
				for (int i = nr_el; i < (nr_el + necessary_ints); i++) {
					dim += 1;
					list_el = realloc(list_el, dim * sizeof(char *));
					list_el[i] = (char *)malloc(word * sizeof(char));
					for (int re = 0; re < word; re++)
						list_el[i][re] = '0';
					new_nr_el = i + 1;
				}

				// Find position
				dim_el = el_dim_by_type(type);
				poz_mat = find_poz_mat(dim_el, idx, poz_mat);
				idx = find_index(dim_el, idx, poz_mat);

				// Modify
				modify_matrix(dim_el, idx, &list_el, val, poz_mat, type);

			// CASE 3 (We dont need to insert and we are on the last row)
			} else if (necessary_ints == 0 && row == nr_of_rows) {

				dim_el = el_dim_by_type(type);
				poz_mat = find_poz_mat(dim_el, idx, poz_mat);
				idx = find_index(dim_el, idx, poz_mat);

				// Modify
				modify_matrix(dim_el, idx, &list_el, val, poz_mat, type);

			// CASE 4 (We dont need to insert and we are not on the last row)
			} else if (necessary_ints == 0 && row != nr_of_rows) {

				dim_el = el_dim_by_type(type);
				poz_mat = find_poz_mat(dim_el, idx, poz_mat);
				idx = find_index(dim_el, idx, poz_mat);

				// Modify
				modify_matrix(dim_el, idx, &list_el, val, poz_mat, type);
			}
			// Update the number of elements to the new number of elements
			nr_el = new_nr_el;
			break;

		case 'D': // Delete()

			dim_el = poz_mat = 0;
			scanf("%d %d", &row, &idx);
			row += 1;

			// Find the position
			for (int repet = 0; repet < (row - 1); repet++)
				poz_mat += (int)nr_el_lin[repet];

			// Find the type and values
			dim_el = el_dim_by_type(type);
			poz_mat = find_poz_mat(dim_el, idx, poz_mat);
			idx = find_index(dim_el, idx, poz_mat);

			// Delete
			delete_characters(dim_el, idx, poz_mat, &list_el);
			break;

		case 'S': // SWAP()

			dim_el = poz_mat = 0;
			scanf("%d %d", &row, &idx);
			row += 1;

			// Find the starting position
			for (int repet = 0; repet < (row - 1); repet++)
				poz_mat += (int)nr_el_lin[repet];

			// Find the type and values
			dim_el = el_dim_by_type(type);
			poz_mat = find_poz_mat(dim_el, idx, poz_mat);
			idx = find_index(dim_el, idx, poz_mat);

			// Swap it
			rotate_characters(dim_el, idx, poz_mat, &list_el);
			break;

		default:
			break;
		}
	}

	// Save in "numbers_final" the final number of elements
	int numbers_final = 0;
	for (int i = 0; i < nr_of_rows; i++)
		numbers_final += nr_el_lin[i];
	for (int i = 0; i < numbers_final; i++)
		reverse_by_2(list_el[i]);

	// Prepare space for display
	int *temp = NULL;
	init_p_int(&temp, nr_of_rows);

	// Temp is a copy of the matrix
	for (int i = 0; i < nr_of_rows; i++)
		temp[i] = nr_el_lin[i];

	// Display
	afisare_task_2(numbers_final, temp, &list_el);

	// Free
	free(val);
	free(vect_null);


	// TASK 3
	printf("\ntask 3\n");

	// Get the maximum number of elements on a row
	int maximum = 0;
	maximum = find_max(nr_el_lin, nr_of_rows);

	// We create mat_int as a replacement for our char matrix
	// And make it a square matrix, filling the NULLs with 1
	int **mat_int = NULL;
	init_matrix_2_pointers(&mat_int, (maximum * maximum));
	for (int i = 0; i < nr_of_rows; i++) init_p_int(&mat_int[i], 4 * maximum);

	// The total number of elements after the expansion | Adding the "1"
	int nr_el_int = 4 * maximum;
	draw_matrix(nr_of_rows, nr_el_int, &mat_int, nr_el_lin, list_el);

	// In keep we hold the suppermasivities of the black holes
	int *keep = NULL;
	int dim_r = 1, nr_cnt = 0;
	init_p_int(&keep, dim_r);

	// In vpoz[i], vpoz[i+1] we keep the position of the black holes
	int *vpoz = NULL;
	int dim_vp = 2;
	init_p_int(&vpoz, dim_vp);

	// Start saving the positions and fill the matrix untill there
	// are no longer black holes (only 1, no 0)
	int a = nr_of_rows;
	int b = nr_el_int;
	int clk = 0;
	int e = dim_vp;
	nr_cnt = pos(a, b, &mat_int, &vpoz, clk, e, &keep, nr_cnt, dim_r);

	// Now find the biggest supermassivity
	int sup_max = keep[0];
	int get_pozmax = 0;
	for (int i = 0; i < nr_cnt; i++) {
		if (sup_max < keep[i]) {
			sup_max = keep[i];
			get_pozmax = i;
		}
	}

	// Display it
	int t = get_pozmax;
	printf("%d %d %d\n", vpoz[t * 2], vpoz[t * 2 + 1], sup_max);

	// Free the memory
	free(temp);
	for (int i = 0; i < nr_of_rows; i++)
		free(mat_int[i]);
	free(mat_int);
	free(vpoz);
	free(keep);
	free(nr_el_lin);
	for (int i = 0; i < (dim); i++)
		free(list_el[i]);
	free(list_el);
	return 0;
}

