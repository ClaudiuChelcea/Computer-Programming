#include <stdio.h>
#include <stdlib.h>
#include "Modify_matrix.h"

// Execute all the modifications given
void execute_modifications(int *** pixel_matrix, int ** line_elements_nr)
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
			execute_modify(pixel_matrix, line_elements_nr, element_type);
			//printf("Execut modify %c %d\n",element_type,i);
		}
		else if(modification_type == 'S') {	
			execute_swap(pixel_matrix, element_type);
			//printf("Execut swap %c %d\n",element_type,i);
		}
		else if(modification_type == 'D') {
			execute_delete(pixel_matrix, element_type);
			//printf("Execut delete %c %d\n",element_type,i);
		}
	}
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
	int needed_int_elements_on_line = (element_position * element_size(type)) / sizeof(int);
	if((element_position * element_size(type)) %sizeof(int) !=0)
		needed_int_elements_on_line +=1;

	// Calculate the number of int values that need to be added
	nr_of_int_to_insert = (needed_int_elements_on_line - current_int_elements_on_line);
	
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
		exit(MEM_ALLOC_ERROR2);
	}
	(*line_elements_nr)[targeted_line] += to_insert;
	
}

// Apply the replacement value
void modify_matrix(int *** pixel_matrix, const int targeted_line, const int element_position, const int replacement, const char type) {

	
	//printf("VOm modifica %d %d %.8X\n\n",targeted_line,element_position,replacement);
	// Decide on which column of the matrix is our element that we need to replace
	if(type == 'C') {
		int my_column = 0;
		my_column = element_position / 4;
		char * my_element = (char*) &((*pixel_matrix)[targeted_line][my_column]);
		*(my_element +  element_position % 4 - 1) = replacement;
	}
	// 00 00 00 01
	// 01 00 00 00
	else if(type == 'S') {//printf("Am primit %d %c\n",targeted_line,type);
		if(element_position % 2 == 1) {	
			int my_column = element_position/2;
			char * my_element = (char*) &(*pixel_matrix)[targeted_line][my_column];
			//printf("%.8X %d %d\n\n",(*pixel_matrix)[targeted_line][my_column],targeted_line,my_column);
			char * new_element = (char*) &replacement;
			//printf("LA pozitia %d %d\\n\n",targeted_line,element_position);
 			*(my_element+0) = *(new_element + 0);
			*(my_element+1) = *(new_element + 1);
		}
		else if(element_position % 2 == 0) {
			//printf("%.8X %d %d/n",(*pixel_matrix)[targeted_line][element_position / 2 - 1],targeted_line,element_position/2-1);
				char * my_element = (char*) &(*pixel_matrix)[targeted_line][element_position / 2 - 1];
				char * new_element = (char*) &replacement;
 				*(my_element+2) = *(new_element);
				*(my_element+3) = *(new_element+1);
		}		
	}
	else if(type == 'I') {
		int my_column = 0 ;
		my_column = element_position - 1;
		(*pixel_matrix)[targeted_line][my_column] = replacement;
	}
}

// Apply the modify modification
void execute_modify(int *** pixel_matrix, int ** line_elements_nr, const char type) {

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
	
	//printf("Modify: %c %d %d %X\n",type,targeted_line,element_position,replacement);
}

// Apply the swap modification
void execute_swap(int *** pixel_matrix, const char type) {

	// Get the targeted matrix line
	int targeted_line;
	scanf("%d",&targeted_line);

	// Get the targeted element position
	int element_position;
	scanf("%d",&element_position);

	// Swap by element type
	if(type=='C') {
		// Do nothing
	}
	else if(type == 'S') {

		// Get the element
		char * p = (char*) &((*pixel_matrix)[targeted_line][element_position/2]);

		// Swap octets
		if(element_position % 2 == 0) {
			char temp = *p, temp1 =*(p+1);
			*(p+1) = temp, *p = temp1;
		}
		else {
			char temp2 = *(p+2),temp3= *(p+3);
			*(p+3) = temp2, *(p+2) = temp3;
		}
	}
	else if(type=='I') {

		// Get the element
		char * p = (char*) &((*pixel_matrix)[targeted_line][element_position]);
	
		// Get each octet
		char temp = *p, temp1 = *(p+1);
		char temp2 = *(p+2), temp3= *(p+3);

		// Swap the number's octets
		*p = temp3, *(p+1) = temp2;
		*(p+2) = temp1, *(p+3) = temp;
	}

	//printf("Swap: %c %d %d\n",type,targeted_line,element_position);
}

// Apply the delete modification
void execute_delete(int *** pixel_matrix, const char type) {
	
	// Get the targeted matrix line
	int targeted_line;
	scanf("%d",&targeted_line);

	// Get the targeted element position
	int element_position;
	scanf("%d",&element_position);

	if(type == 'C') {
	
		char * p = (char*) &(*pixel_matrix)[targeted_line][element_position / 4];
		// if(element_position % 4 != 0)
		// 	p = (char*) &(*pixel_matrix)[targeted_line][element_position / 4 + 1];
		// a b c d
		// d c b a
		if(element_position%4 == 0) {
			p  = (char*) &(*pixel_matrix)[targeted_line][element_position / 4 - 1];
			*(p+3) = 0;
		}
		else if(element_position%4 == 1) {
			*p = 0;
		}
		else if(element_position%4 == 2) {
			*(p+1) = 0;
		}
		else if(element_position%4 == 3) {
			*(p+2) = 0;
		}

	}

	else if(type=='S') {
		
		int my_column = element_position / 2 + element_position % 2;
		
		if(element_position %2 ==1) {//printf("%d %d %.8X\n\n",targeted_line,my_column,(*pixel_matrix)[targeted_line][my_column-1]);
			char * p = (char*) &((*pixel_matrix)[targeted_line][my_column-1]);
			*(p+4-element_position%2-2) = 0;
			*(p+4-element_position%2-3) = 0;
			
		}
		else {
			//printf("%d %d %.8X 2222\n\n",targeted_line,my_column,(*pixel_matrix)[targeted_line][my_column-1]);
			char * p = (char*) &((*pixel_matrix)[targeted_line][my_column-1]);
			*(p+4-element_position%2-2) = 0;
			*(p+4-element_position%2-1) = 0;
		}
	}
	else {
	
		char * p = (char*) &((*pixel_matrix)[targeted_line][element_position-1]);
		
		*(p) = 0;
		*(p + 1) = 0;
		*(p + 2) = 0;
		*(p + 3) = 0;
		
	}

	//printf("Delete: %c %d %d\n",type,targeted_line,element_position);
}
