#include "Input-Output.h"
#include <stdio.h>
#include <stdlib.h>

/*  Calculate the arithmetic mean from the margins created by the margins of
	the HEX values
	@return margin_aritmetic_mean */
void show_arithmetic_mean_of_byte_margins(int *line_elements_nr,const int nr_lines,
					  					  int **pixel_matrix)
{
	double arithmetic_mean = 0.00;
	int nr_of_elements = 0;

	// Check if the element is on the margin of the matrix
	for (int i = 0; i < nr_lines; i++) {
		for (int j = 0; j < line_elements_nr[i]; j++) {
			if (i == 0 || i == nr_lines - 1) {
				// The top and bottom rows
				char *p = NULL;
				p = (char *)&(pixel_matrix[i][j]);
				if (!p) {
					fprintf(stderr, "Couldn`t calculate arithmetic mean!");
					exit(MEM_ALLOC_ERROR);
				}
				arithmetic_mean += *p + *(p + 1) + *(p + 2) + *(p + 3);
			} else if (j == 0) {
				// Left column
				char *p = NULL;
				p = (char *)&(pixel_matrix[i][j]);
				if (!p) {
					fprintf(stderr, "Couldn`t calculate arithmetic mean!");
					exit(MEM_ALLOC_ERROR);
				}
				arithmetic_mean += *p;
				if (line_elements_nr[i] == 1) {
					arithmetic_mean += *(p + 3);
				}
			} else if (j == (line_elements_nr[i] - 1)) {
				// Right column
				char *p = NULL;
				p = (char *)&(pixel_matrix[i][j]);
				if (!p) {
					fprintf(stderr, "Couldn`t calculate arithmetic mean!");
					exit(MEM_ALLOC_ERROR);
				}
				arithmetic_mean += *(p + 3);
			}
		}
	}
	// The top and bottom elements * 4 (each int has 4 bytes) and the right
	// and left column only once
	nr_of_elements =
		(line_elements_nr[0] + line_elements_nr[nr_lines - 1]) * 4 +
		(nr_lines - 2) * 2;

	// Display the output on stdin
	printf("task 1\n%.8lf\n", (double)arithmetic_mean / (double)nr_of_elements);
}

// Allocate the memory necessary and scan the matrix
void scan_matrix(int ***pixel_matrix, int *line_elements_nr, const int nr_lines)
{
	// Allocate memory
	*pixel_matrix = NULL;
	*pixel_matrix = (int **)calloc(nr_lines, sizeof(int *));
	if (!pixel_matrix) {
		fprintf(stderr, "Memory allocation error creating matrix\n");
		exit(MEM_ALLOC_ERROR);
	}

	// Scan the number of elements on each line
	for (int i = 0; i < nr_lines; i++) {
		line_elements_nr[i] = 0;
		scanf("%d", &line_elements_nr[i]);

		// Then allocate memory for each line and scan it's elements
		(*pixel_matrix)[i] = NULL;
		(*pixel_matrix)[i] = (int *)calloc(line_elements_nr[i], sizeof(int));
		if (!(*pixel_matrix)[i]) {
			fprintf(stderr, "Memory allocation error scanning line\n");
			exit(MEM_ALLOC_ERROR);
		}
		for (int j = 0; j < line_elements_nr[i]; j++)
			scanf("%X", &(*pixel_matrix)[i][j]);
	}
}

// Allocate the array that holds the number of elements on each line
void alloc_line_elements(int **line_elements_nr, const int nr_lines)
{
	*line_elements_nr = NULL;
	*line_elements_nr = (int *)calloc(nr_lines, sizeof(int));
	if (!(*line_elements_nr)) {
		fprintf(stderr, "Memory allocation error creating line elements\n");
		exit(MEM_ALLOC_ERROR);
	}
}

// Print the whole matrix
void print_matrix(int **pixel_matrix, const int nr_lines, int *line_elements_nr)
{
	for (int i = 0; i < nr_lines; i++) {
		for (int j = 0; j < line_elements_nr[i]; j++)
			printf("%.8X ", pixel_matrix[i][j]);
		printf("\n");
	}
}

// Release the memory
void free_mem(int **line_elements_nr, const int nr_lines, int ***pixel_matrix)
{
	free(*line_elements_nr);
	for (int i = 0; i < nr_lines; i++)
		free((*pixel_matrix)[i]);
	free(*pixel_matrix);
}

// Create a square matrix from the specified matrix
int create_copy_square_matrix(int **pixel_matrix, int ***square_pixel_matrix,
							  const int nr_lines, int *line_elements_nr)
{
	// Allocate memory
	(*square_pixel_matrix) = (int **)calloc(nr_lines, sizeof(int *));
	if (!(*square_pixel_matrix)) {
		fprintf(stderr, "Memory allocation error creating square matrix\n");
		exit(MEM_ALLOC_ERROR);
	}

	// Find the maximum size
	int max = nr_lines;
	for (int i = 0; i < nr_lines; i++) {
		if (max < line_elements_nr[i])
			max = line_elements_nr[i];
	}

	// Then allocate memory for each line and  copy elements
	// if the square matrix has more elemnts than the normal matrix
	// fill the extra elements with '1'
	for (int i = 0; i < nr_lines; i++) {
		(*square_pixel_matrix)[i] = NULL;
		(*square_pixel_matrix)[i] = (int *)malloc(max * sizeof(int));
		if ((*square_pixel_matrix)[i] == NULL) {
			fprintf(stderr,
					"Memory allocation error copying matrix elements\n");
			exit(MEM_ALLOC_ERROR);
		}
		for (int j = 0; j < line_elements_nr[i]; j++)
			(*square_pixel_matrix)[i][j] = pixel_matrix[i][j];
		for (int j = line_elements_nr[i]; j < max; j++)
			(*square_pixel_matrix)[i][j] |= (~0);
	}

	return max;
}

// Fill the group of adjacent '00' values to non_zero values
void flood_fill(int x, int y, int **matrix, int *count, const int max_elements,
				const int nr_lines)
{
	// Check the bounds
	if (x < 0 || x >= nr_lines || y < 0 || y >= max_elements * 4)
		return;

	// Start at the end of the line and then move to the corresponding 'y' byte
	char *p = (char *)&matrix[x][0];
	p += y;

	// If it's '00', change to minus one and check adjacent elements
	if (*p == 0) {
		*p = 0xFF;
		(*count)++;
		flood_fill(x + 1, y, matrix, count, max_elements, nr_lines);
		flood_fill(x - 1, y, matrix, count, max_elements, nr_lines);
		flood_fill(x, y + 1, matrix, count, max_elements, nr_lines);
		flood_fill(x, y - 1, matrix, count, max_elements, nr_lines);
	}
}

// Print on STDOUT the biggest black hole found
void display_biggest_black_hole(int **pixel_matrix, int *line_elements_nr,
								const int nr_lines)
{

	// Allocate memory for square matrix
	int **square_pixel_matrix = NULL;
	int max_elements = 0;

	// Create a replacement for our matrix
	max_elements = create_copy_square_matrix(pixel_matrix, &square_pixel_matrix,
											 nr_lines, line_elements_nr);

	int count = 0, max = 0, coord_x = 0, coord_y = 0;

	// Fill each "00" group with "FF" and count the number of "00" in the group
	// to find the biggest "00" group
	for (int i = 0; i < nr_lines; i++) {
		for (int j = 0; j < max_elements * 4; j++) {
			if (*(((char *)&(square_pixel_matrix[i][j / 4]) + j % 4)) == 0) {
				count = 0;
				flood_fill(i, j, square_pixel_matrix, &count, max_elements,
						   nr_lines);
				if (max < count) {
					max = count;
					coord_x = i;
					coord_y = j;
				}
			}
		}
	}

	// Release the sqaure matrix's memory
	for (int i = 0; i < nr_lines; i++)
		free(square_pixel_matrix[i]);
	free(square_pixel_matrix);

	// Display the output
	printf("%d %d %d\n", coord_x, coord_y, max);
}
