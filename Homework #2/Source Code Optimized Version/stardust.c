#include <stdio.h>
#include <stdlib.h>
#include "Input-Output.h"
#include "Modify_matrix.h"

int main(void) {

	// The numbers of lines in the matrix
	int nr_lines = 0;
	scanf("%d",&nr_lines);

	// The numbers of elements on every line
	int* line_elements_nr = NULL;
	alloc_line_elements(&line_elements_nr, nr_lines);

	// The matrix that holds the scanned numbers
	int **pixel_matrix = NULL;
	scan_matrix(&pixel_matrix, line_elements_nr, nr_lines);

	// Task 1
	// Display the arithmetic mean calculated with the bytes on the margins
	show_arithmetic_mean_of_byte_margins(line_elements_nr,nr_lines,pixel_matrix);
	
	// Task 2
	// Execute the modifications
	printf("task 2\n");
	execute_modifications(&pixel_matrix, &line_elements_nr);

	// Display the matrix in HEX format
	print_matrix(pixel_matrix,nr_lines,line_elements_nr);

	// Task 3
	printf("task 3\n");

	// Release the memory
	free_mem(&line_elements_nr,nr_lines,&pixel_matrix);



	return SUCCESS_FINISH;
}
