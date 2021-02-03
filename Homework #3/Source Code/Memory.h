// Chelcea Claudiu Marian

#ifndef __MEMORY_H_
#define __MEMORY_H_
#include <stdio.h>

// This function allocates the space necessary for the commands.
char *user_input(void);

// This function returns a value between 0 - 8 representing
// the position in the command list of the received input
// and returns -1 if it doesn't exist
int find_command_value(const char *commands[], char *input);

// This functions allocates the memory for the image pixels
// and saves the pixels in a matrix shape, reading from an ASCII file
unsigned char **read_pixels(const int my_image_width, const int my_image_height,
			    FILE *file, const char *file_name);

// This functions allocates the memory for the image pixels
// and saves the pixels in a matrix shape, reading from an binary file
unsigned char **read_pixels_binary(const int my_width, const int my_height,
				   FILE *file, const char *file_name);

// This functions frees the memory from the currently loaded image.
void free_pixels(const int my_image_height, unsigned char ***pixel_matrix);

// This functions creates a copy of the current selection.
unsigned char **copy_pixels_selection(const int x1, const int y1, const int x2,
				      const int y2, unsigned char ***image);

// This function gets the initial values the file
void get_values(int *my_image_max, FILE *file, int *width, int *height);

// This function ascii values in the new file
void printf_ascii(char *px_type, FILE *new_file, int width, int height,
		  int my_image_max, int x1, int x2, int y1, int y2,
		  unsigned char **image);

// This function binary values in the new file
void printf_binary(char *px_type, FILE *new_file, int width, int height,
		   int my_image_max, int x1, int x2, int y1, int y2,
		   unsigned char **image);

// File status
enum { FILE_OPEN_ERROR = 4, FILE_CLOSE_ERROR = 5 };

// Predefined values
enum {
	NAME_LENGTH_MAX = 100,
	FALSE = 0,
	TRUE = 1,
	SUCC = 2,
	ERR = 3,
	UPP = 1,
	DOWNN = 0,
	MAX_COMMAND_SIZE = 100
};

#endif
