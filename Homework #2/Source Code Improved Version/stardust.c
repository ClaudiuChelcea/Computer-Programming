#include <stdio.h>
#include <stdlib.h>

enum {
	MEM_ALLOC_ERROR=-1,
	SUCCESS_FINISH = 0
};

// Allocate the memory necessary and scan the matrix
void scan_matrix(int *** pixel_matrix,int* line_elements_nr, const int nr_lines)
{
	// Allocate memory
	*pixel_matrix = (int**) malloc(nr_lines * sizeof(int*));
	if(!pixel_matrix) {
		fprintf(stderr,"Memory allocation error");
		exit(MEM_ALLOC_ERROR);
	}

	// Scan the number of elements on each line
	for(int i=0;i<nr_lines;i++) {
		scanf("%d",&line_elements_nr[i]);

		// Then allocate memory for each line and scan it's elements
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
	int nr_lines;
	scanf("%d",&nr_lines);

	// The numbers of elements on every line
	int* line_elements_nr;
	alloc_line_elements(&line_elements_nr, nr_lines);

	// The matrix that holds the scanned numbers
	int **pixel_matrix;
	scan_matrix(&pixel_matrix, line_elements_nr, nr_lines);

	// Task 1

	// Display the arithmetic mean calculated with the bytes on the margins
	show_arithmetic_mean_of_byte_margins(line_elements_nr,nr_lines,pixel_matrix);
	
	// Task 2




	// Task 3








	// Display the matrix in HEX format
	print_matrix(pixel_matrix,nr_lines,line_elements_nr);

	// Release the memory
	free_mem(&line_elements_nr,nr_lines,&pixel_matrix);



	return SUCCESS_FINISH;
}
