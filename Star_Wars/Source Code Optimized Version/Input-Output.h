#ifndef __INPUT_OUTPUT__
#define __INPUT_OUTPUT__

/*  Calculate the arithmetic mean from the margins created by the margins of
   the HEX values
		@return margin_aritmetic_mean */
void show_arithmetic_mean_of_byte_margins(int *line_elements_nr,
										  const int nr_lines,
										  int **pixel_matrix);

// Allocate the memory necessary and scan the matrix
void scan_matrix(int ***pixel_matrix, int *line_elements_nr,
				 const int nr_lines);

// Allocate the array that holds the number of elements on each line
void alloc_line_elements(int **line_elements_nr, const int nr_lines);

// Print the whole matrix
void print_matrix(int **pixel_matrix, const int nr_lines,
				  int *line_elements_nr);

// Release the memory
void free_mem(int **line_elements_nr, const int nr_lines, int ***pixel_matrix);

// Print on STDOUT the biggest black hole found
void display_biggest_black_hole(int **pixel_matrix, int *line_elements_nr,
								const int nr_lines);

// Create a square matrix from the specified matrix
int create_copy_square_matrix(int **pixel_matrix, int ***square_pixel_matrix,
							  const int nr_lines, int *line_elements_nr);

// Fill the group of adjacent 0 values to non_zero values
void flood_fill(int x, int y, int **matrix, int *count, const int max_elements,
				const int nr_lines);

// Print on STDOUT the biggest black hole found
void display_biggest_black_hole(int **pixel_matrix, int *line_elements_nr,
								const int nr_lines);

enum
{
	MEM_ALLOC_ERROR = -1,
	SUCCESS_FINISH = 0
};

#endif
