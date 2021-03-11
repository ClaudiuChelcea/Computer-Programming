// Chelcea Claudiu Marian

#include "Commands.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFINED_COMMANDS 9

// Image state
enum { DOWN = 0, UP = 1, NULL_LIST = 2 };

int main(void)
{
	// Set IMAGE
	unsigned char **image = NULL;
	int width = 0, height = 0, image_status = DOWN;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0, my_image_max = 0, cropped = 0;
	int print_x1 = 0, print_x2 = 0, print_y1 = 0, print_y2 = 0;
	int color_image = 0, whole_map_selected = 1, correct = 0,
		has_been_cropped = 0;
	char type = '0';

	// Set COMMAND
	const char *commands[DEFINED_COMMANDS] = {"LOAD", "SELECT", "SELECT ALL",
						  "ROTATE", "CROP", "GRAYSCALE",
						  "SEPIA", "SAVE", "EXIT"};
	char *input = user_input();

	// Receive commands and execute them
	while (UP) {
		
		fgets(input, MAX_COMMAND_SIZE, stdin);

		// Check what command is given and whether it exists or not.
		int command_value = find_command_value(commands, input);

		// If it exists, execute it.
		check_command(command_value, &width, &height, &image_status, &x1, &y1,
			      &x2, &y2, &image, &input, &color_image, &type,
			      &my_image_max, &whole_map_selected, &correct, &cropped,
			      &has_been_cropped, &print_x1, &print_y1, &print_x2,
			      &print_y2);
	}
	// Free memory
	free(commands);
	free(input);

	return SUCCESS;
}
