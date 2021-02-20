#include <stdio.h>
#include <stdlib.h>
#include "Input-Output.h"

// Allocate the memory necessary and scan the matrix
void scan_matrix(int *** pixel_matrix,int* line_elements_nr, const int nr_lines)
{
	// Allocate memory
	*pixel_matrix = NULL;
	*pixel_matrix = (int**) malloc(nr_lines * sizeof(int*));
	if(!pixel_matrix) {
		fprintf(stderr,"Memory allocation error");
		exit(MEM_ALLOC_ERROR);
	}

	// Scan the number of elements on each line
	for(int i=0;i<nr_lines;i++) {
		scanf("%d",&line_elements_nr[i]);

		// Then allocate memory for each line and scan it's elements
		(*pixel_matrix)[i] = NULL;
		(*pixel_matrix)[i] = (int*) malloc(line_elements_nr[i] * sizeof(int));
		if(!(*pixel_matrix)[i])  {
			fprintf(stderr,"Memory allocation error");
			exit(MEM_ALLOC_ERROR);
		}
		for(int j=0;j<line_elements_nr[i];j++)
			scanf("%X",&(*pixel_matrix)[i][j]);
	}
}



// Allocate the array that holds the number of elements on each line
void alloc_line_elements(int ** line_elements_nr, const int nr_lines)
{
	*line_elements_nr = NULL;
	*line_elements_nr = (int*) malloc(nr_lines * sizeof(int));
	if(!(*line_elements_nr)) {
		fprintf(stderr,"Memory allocation error");
		exit(MEM_ALLOC_ERROR);

	}
}

// Print the whole matrix
void print_matrix(int ** pixel_matrix, const int nr_lines,
				  int* line_elements_nr)
{
	for(int i=0;i<nr_lines;i++) {
		for(int j=0;j<line_elements_nr[i];j++)
			printf("%.8X ",pixel_matrix[i][j]);
	printf("\n");
	}

}

// Release the memory
void free_mem(int ** line_elements_nr, const int nr_lines, int *** pixel_matrix ){
	free(*line_elements_nr);
	for(int i=0;i<nr_lines;i++)
		free((*pixel_matrix)[i]);
	free(*pixel_matrix);
}

