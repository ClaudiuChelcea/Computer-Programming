#ifndef __Modify_matrix__
#define __Modify_matrix__

// Execute all the modifications given
void execute_modifications(int ***pixel_matrix, int **line_elements_nr);

// Return the element size in octets
int element_size(const char type);

// Return the number of elements that need to be inserted for the current
// modification
int nr_inserted_elements(int *line_elements_nr, const int targeted_line,
						 const int element_position, const char type);

// Return the number of int elements on the current line
int get_current_line_size(int *line_elements_nr, const int targeted_line);

// Allocate the memory to insert int values in the matrix
void insert_int_values(int ***pixel_matrix, const int targeted_line,
					   const int to_insert, int **line_elements_nr);

// Apply the replacement value
void modify_matrix(int ***pixel_matrix, const int targeted_line,
				   const int element_position, const int replacement,
				   const char type);

// Apply the modify modification
void execute_modify(int ***pixel_matrix, int **line_elements_nr,
					const char type);

// Apply the swap modification
void execute_swap(int ***pixel_matrix, const char type);

// Apply the delete modification
void execute_delete(int ***pixel_matrix, const char type);

enum
{
	MEM_ALLOC_ERROR2 = -1,
};

#endif
