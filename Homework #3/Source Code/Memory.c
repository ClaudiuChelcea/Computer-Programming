// Chelcea Claudiu Marian

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exit status
enum { MALLOC_FAIL = 2, REALLOC_FAIL = 3 };

// Commands sizes
enum { MAX_COMMAND_SIZE = 100, DEFINED_COMMANDS = 9 };

// This function allocates the space necessary for a command.
char *user_input(void)
{
	char *input = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));

	if (!input)
		return (char *)MALLOC_FAIL;

	return input;
}

// This function returns a value between 0 - 8 representing
// the position in the command list of the received command
// and returns -1 if it doesn't exist
int find_command_value(const char *commands[], char *input)
{
	// Receive command
	int command_value = -1;
	char *first_command = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
	if (!first_command)
		return MALLOC_FAIL;
	char *second_command = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));
	if (!second_command)
		return MALLOC_FAIL;
	if (sscanf(input, "%s %s", first_command, second_command) == 0)
		return 0;

	// Check if the command is in the list
	for (int i = 0; i < DEFINED_COMMANDS; i++)
		if (strcmp(commands[i], first_command) == 0) {
			command_value = i;
			break;
		}
	if (command_value == 1 && (strcmp(second_command, "ALL") == 0))
		command_value = 2;

	free(first_command);
	free(second_command);

	return command_value;
}

// This functions allocates the memory for the image pixels
// and saves the pixels in a matrix shape, reading from an ASCII file
unsigned char **read_pixels(const int my_image_width, const int my_image_height,
			    FILE *file, const char *file_name)
{
	// Allocate memory
	unsigned char **pixel_matrix =
		(unsigned char **)malloc(my_image_height * sizeof(unsigned char *));
	for (int i = 0; i < my_image_height; i++)
		pixel_matrix[i] =
			(unsigned char *)malloc(my_image_width * sizeof(unsigned char));

	// Scan values from ASCII file
	for (int i = 0; i < my_image_height; i++)
		for (int j = 0; j < my_image_width; j++)
			fscanf(file, "%hhu", &pixel_matrix[i][j]);

	if (pixel_matrix)
		printf("Loaded %s\n", file_name);

	return pixel_matrix;
}

// This functions allocates the memory for the image pixels
// and saves the pixels in a matrix shape, reading from an binary file
unsigned char **read_pixels_binary(const int my_width, const int my_height,
				   FILE *file, const char *file_name)
{
	// Allocate memory
	unsigned char **pixels =
		(unsigned char **)malloc(my_height * sizeof(unsigned char *));

	for (int i = 0; i <= my_height; i++)
		pixels[i] = (unsigned char *)malloc(my_width * sizeof(unsigned char));

	// Scan values from ASCII file
	for (int i = 0; i < my_height; i++)
		for (int j = 0; j < my_width; j++)
			fread(&pixels[i][j], sizeof(unsigned char), 1, file);

	if (pixels)
		printf("Loaded %s\n", file_name);

	return pixels;
}

// This functions creates a copy of the current selection
unsigned char **copy_pixels_selection(const int x1, const int y1, const int x2,
				      const int y2, unsigned char ***image)
{
	// Find the width and the height of the image
	int my_image_width = y2 - y1;
	int my_image_height = x2 - x1;

	// Memory allocation
	unsigned char **pixel_matrix =
		(unsigned char **)malloc((my_image_width) * sizeof(unsigned char *));
	for (int i = 0; i < my_image_height; i++)
		pixel_matrix[i] =
			(unsigned char *)malloc((my_image_height) * sizeof(unsigned char));

	// Copy values
	for (int i = 0; i < my_image_height; i++)
		for (int j = 0; j < my_image_width; j++)
			pixel_matrix[i][j] = (*image)[x1 + i][y1 + j];

	return pixel_matrix;
}

// This functions frees the memory from the currently loaded image.
void free_pixels(const int my_image_height, unsigned char ***pixel_matrix)
{
	// Free every line
	for (int i = 0; i < my_image_height; i++)
		free((*pixel_matrix)[i]);

	// Free the main pointer
	free(*pixel_matrix);
}

// This function gets the initial values the file
void get_values(int *my_image_max, FILE *file, int *width, int *height)
{
	// Get the values while ignoring comments
	char *comment_line = (char *)malloc(100 * sizeof(char));
	int my_width = -1, my_height = -1;
	*my_image_max = -1;

	while (fgets(comment_line, 100, file)) {
		if (comment_line[0] == '#' || comment_line[0] < '0' ||
			comment_line[0] > '9') {
			continue;
		} else if (my_width == -1 && my_height == -1) {
			if (sscanf(comment_line, "%d %d", &my_width, &my_height) == 0)
				return;
		} else {
			if (sscanf(comment_line, "%d", my_image_max) == 0)
				return;
			break;
		}
	}

	// Set the size of the image
	*height = my_height;
	*width = my_width;

	free(comment_line);
}

// This function ascii values in the new file
void printf_ascii(char *px_type, FILE *new_file, int width, int height,
		  int my_image_max, int x1, int x2, int y1, int y2,
		  unsigned char **image)
{
	fprintf(new_file, "%s\n%d %d\n%d\n", px_type, width, height, my_image_max);

	for (int i = x1; i < x2; i++) {
		for (int j = y1; j < y2; j++)
			fprintf(new_file, "%hhu ", image[i][j]);
		fprintf(new_file, "\n");
	}

	if (fclose(new_file) == EOF)
		return;
}

// This function binary values in the new file
void printf_binary(char *px_type, FILE *new_file, int width, int height,
		   int my_image_max, int x1, int x2, int y1, int y2,
		   unsigned char **image)
{
	fprintf(new_file, "%s\n%d %d\n%d\n", px_type, width, height, my_image_max);

	for (int i = x1; i < x2; i++)
		for (int j = y1; j < y2; j++)
			fwrite(&image[i][j], sizeof(unsigned char), 1, new_file);

	if (fclose(new_file) == EOF)
		return;
}
