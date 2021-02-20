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

// Return the element size in octets
int element_size(const char type)
{
	// Decide the case and return the size for the element type
	switch(type) {
		case 'I':
			return (int) sizeof(int);
		case 'S':
			return (int) sizeof(short);
		default:
			return (int) sizeof(char);
	}
}

// Return the number of elements that need to be inserted for the current modification
int nr_inserted_elements(int * line_elements_nr, const int targeted_line,
 						 const int element_position, const char type)
{
	// The number of int values to insert in the matrix
	int nr_of_int_to_insert = 0;

	// The current number of int values on the targeted line
	int current_int_elements_on_line = line_elements_nr[targeted_line];
	
	// The number of needed int values on the targeted line
	int needed_int_elements_on_line = (element_position * element_size(type)) /  sizeof(int);
	if( (element_position * element_size(type)) /  sizeof(int)!=0) 
		needed_int_elements_on_line +=1;
	
	// Calculate the number of int values that need to be added
	nr_of_int_to_insert =  (needed_int_elements_on_line - current_int_elements_on_line);
	
	return nr_of_int_to_insert;
}

// Return the number of int elements on the current line
int get_current_line_size(int *line_elements_nr, const int targeted_line) {
	return line_elements_nr[targeted_line];
}

// Allocate the memory to insert int values
void insert_int_values(int *** pixel_matrix, const int targeted_line, const int to_insert, int ** line_elements_nr) {
	(*pixel_matrix)[targeted_line] = (int*) realloc((*pixel_matrix)[targeted_line], (get_current_line_size(*line_elements_nr,targeted_line) + to_insert)  * sizeof(int));
	if(!((*pixel_matrix)[targeted_line])) {
		fprintf(stderr, "Error reallocating int values\n");
		exit(MEM_ALLOC_ERROR);
	}
	(*line_elements_nr)[targeted_line] += to_insert;
	
}

// Apply the replacement value
void modify_matrix(int *** pixel_matrix, const int targeted_line, const int element_position, const int replacement, const char type) {
	
	// Decide on which column of the matrix is our element that we need to replace
	int my_column = 0;
	printf("\n\nElempos:%d\n\n",element_position);
	if(type == 'C') {
		my_column = element_position / 4;
	}
	else if(type == 'S') {
		my_column = element_position / 2;
	}
	else {
		my_column = element_position -1;
	}

	(*pixel_matrix)[targeted_line][my_column] = replacement;
}

// Apply the modify modification
void execute_modify(const int nr_lines, int *** pixel_matrix, int ** line_elements_nr, const char type) {
	
	// Get the targeted matrix line
	int targeted_line;
	scanf("%d",&targeted_line);

	// Get the targeted element position
	int element_position;
	scanf("%d",&element_position);

	// Get the new number that will replace our elements
	int replacement;
	scanf("%X",&replacement);
	

	// If needed, insert int values
	int to_insert = nr_inserted_elements(*line_elements_nr, targeted_line, element_position, type);
	if(to_insert > 0)
		insert_int_values(pixel_matrix, targeted_line, to_insert, line_elements_nr);

	// Apply the modification
	modify_matrix(pixel_matrix, targeted_line, element_position, replacement, type);
	
	printf("Modify: %c %d %d %X\n",type,targeted_line-1,element_position,replacement);
}

// Apply the swap modification
void execute_swap(const int nr_lines, int *** pixel_matrix, int ** line_elements_nr, const char type) {

	// Get the targeted matrix line
	int targeted_line;
	scanf("%d",&targeted_line);
	targeted_line +=1;

	// Get the targeted element position
	int element_position;
	scanf("%d",&element_position);
	element_position -=1;

	printf("Swap: %c %d %d\n",type,targeted_line-1,element_position+1);
}

// Apply the delete modification
void execute_delete(const int nr_lines, int *** pixel_matrix, int ** line_elements_nr, const char type) {
	
	// Get the targeted matrix line
	int targeted_line;
	scanf("%d",&targeted_line);
	targeted_line +=1;

	// Get the targeted element position
	int element_position;
	scanf("%d",&element_position);
	element_position -=1;

	printf("Delete: %c %d %d\n",type,targeted_line-1,element_position+1);
}

// EXecute all the modifications given
void execute_modifications(const int nr_lines, int *** pixel_matrix, int ** line_elements_nr)
{
	// The number of modifications performed on the matrix
	int nr_of_modifications;
	char modification_type, element_type;
	scanf("%d",&nr_of_modifications);
	
	// For each type of modification call the corresponding function
	for(int i=0;i<nr_of_modifications;i++) {
		scanf(" %c %c ",&modification_type, &element_type);
		
		// Decide the function needed to be called and call it
		if(modification_type == 'M') {
			execute_modify(nr_lines, pixel_matrix, line_elements_nr, element_type);
			if(i==2)
				break;
		}
		else if(modification_type == 'S') {	
			execute_swap(nr_lines, pixel_matrix, line_elements_nr, element_type);
		}
		else if(modification_type == 'D') {
			execute_delete(nr_lines, pixel_matrix, line_elements_nr, element_type);
		}
	}
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
	//	show_arithmetic_mean_of_byte_margins(line_elements_nr,nr_lines,pixel_matrix);
	
	// Task 2

	// Execute the modifications
	printf("task 2\n");
	execute_modifications(nr_lines, &pixel_matrix, &line_elements_nr);

	// Task 3








	// Display the matrix in HEX format
	print_matrix(pixel_matrix,nr_lines,line_elements_nr);

	// Release the memory
	free_mem(&line_elements_nr,nr_lines,&pixel_matrix);



	return SUCCESS_FINISH;
}
