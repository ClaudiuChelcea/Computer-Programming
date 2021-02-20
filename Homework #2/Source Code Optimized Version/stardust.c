#include <stdio.h>
#include <stdlib.h>
#include "Input-Output.h"
#include "Modify_matrix.h"

/*  Calculate the arithmetic mean from the margins created by the margins of the HEX values
	@return margin_aritmetic_mean */
void show_arithmetic_mean_of_byte_margins(int* line_elements_nr, const int nr_lines, int ** pixel_matrix)
{
	double arithmetic_mean = 0.00;
	int nr_of_elements = 0;

	// Check if the element is on the margin of the matrix
	for(int i=0;i<nr_lines;i++) {
		for(int j=0;j<line_elements_nr[i];j++) {
			if(i==0 || j==0 || i==nr_lines-1) {

				// If it is on the margin, depending on his position
				// get the corresponding position in the matrix	
				char* p = (char*) &(pixel_matrix[i][j]); 		
				arithmetic_mean +=*p;
			}

			// Rigth margin
			else if(j==(line_elements_nr[i]-1)) {
				char* p = (char*) &(pixel_matrix[i][j]);
				arithmetic_mean +=*(p+3);
			}	
		}
	}

	// The number of elements on the top and bottom row
	nr_of_elements = line_elements_nr[0] + line_elements_nr[nr_lines -1];

	// The number on the left and right margin, excluding the top and the bottom row
	nr_of_elements += (nr_of_elements-2) * 2;

	// *2 because every hex number has two margins
	nr_of_elements  *=2;

	// Display the output on stdin
	printf("task 1\n%.8lf\n",(double)arithmetic_mean/(double)nr_of_elements);
}




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
	// show_arithmetic_mean_of_byte_margins(line_elements_nr,nr_lines,pixel_matrix);
	
	// Task 2

	// Execute the modifications
	printf("task 2\n");
	execute_modifications(&pixel_matrix, &line_elements_nr);

	// Task 3








	// Display the matrix in HEX format
	print_matrix(pixel_matrix,nr_lines,line_elements_nr);

	// Release the memory
	free_mem(&line_elements_nr,nr_lines,&pixel_matrix);



	return SUCCESS_FINISH;
}
