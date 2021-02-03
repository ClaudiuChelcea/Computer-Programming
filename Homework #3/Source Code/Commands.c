// Chelcea Claudiu Marian

#include "Memory.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LENGTH_MAX 100

// This function loads the image from the file
// and keeps the width and the height.
unsigned char **LOAD(const char *file_name, int *width, int *height, int *x1,
		     int *y1, int *x2, int *y2, int *color_image,
		     int *my_image_max, char *type)
{
	FILE *file = fopen(file_name, "rt");
	if (!file) {
		printf("Failed to load %s\n", file_name);
		return (unsigned char **)ERR;
	}

	char first_character, second_character; // Get type
	fscanf(file, "%c %c", &first_character, &second_character);
	// Check for text files
	if (second_character == '2') {	// GRAYSCALE - ASCII
		get_values(my_image_max, file, width, height); // set image size
		unsigned char **pixels = NULL;	// Copy the image
		pixels = read_pixels(*width, *height, file, file_name);

		// Set new values for coordinates, dimensions and color
		*x1 = 0; *y1 = 0; *x2 = *height; *y2 = *width;
		*color_image = 0; *type = '2';
		if (fclose(file) == EOF)
			return (unsigned char **)FILE_CLOSE_ERROR; // Close file
		return pixels;

	} else if (second_character == '3') {			   // RGB - ASCII
		get_values(my_image_max, file, width, height); // set image size
		*width = *width * 3;
		unsigned char **pixels = NULL; // Copy image
		pixels = read_pixels(*width, *height, file, file_name);

		// Set new values for coordinates, dimensions and color;
		*x1 = 0; *y1 = 0; *x2 = *height; *y2 = *width;
		*color_image = 1; *type = '3';
		if (fclose(file) == EOF)
			return (unsigned char **)FILE_CLOSE_ERROR; // Close file
		return pixels;

	} else { // Check for binary files

		ungetc(first_character, file);	// Put the read characters
		ungetc(second_character, file); // back into the file

		if (fclose(file) == EOF)
			return (unsigned char **)FILE_CLOSE_ERROR; // Close the file
		FILE *file_bin = NULL; // Open the same file, but as binary
		file_bin = fopen(file_name, "rb");

		// Get the type of file and the image restrictions
		char file_type2[2];
		fscanf(file_bin, "%s", file_type2);
		get_values(my_image_max, file, width, height); // set image size

		// Decide which file type it is
		if (strcmp("P5", file_type2) == 0) { // Binary GRAYSCALE
			unsigned char **pixels = NULL;	 // Read the image
			pixels = read_pixels_binary(*width, *height, file, file_name);

			// Set new coordinates
			*x1 = 0; *y1 = 0; *x2 = *height; *y2 = *width;
			*color_image = 0; *type = '5';

			if (fclose(file_bin) == EOF)
				return (unsigned char **)FILE_CLOSE_ERROR; // Close the file
			return pixels;

		} else {						   // Binary RGB
			unsigned char **pixels = NULL; // Read the image
			*width = *width * 3;
			pixels = read_pixels_binary(*width, *height, file, file_name);

			// Modify the dimensions
			*x1 = 0; *y1 = 0; *x2 = *height; *y2 = *width;
			*color_image = 1; *type = '6';
			if (fclose(file_bin) == EOF)
				return (unsigned char **)FILE_CLOSE_ERROR; // Close the file
			return pixels;
		}
	}
	return (unsigned char **)SUCC;
}

// This function selects a part of the area.
void SELECT(int *x1, int *y1, int *x2, int *y2, int width, int height,
	    int *correct, int color_image)
{
	if (color_image == 1)
		width /= 3;

	// Check if the coordinates are valid
	if (*x1 < 0 || *x2 < 0 || *y1 < 0 || *y2 < 0) {
		printf("Invalid set of coordinates\n");
		*correct = 0;
		return;
	} else if (*x1 > width || *x2 > width) {
		printf("Invalid set of coordinates\n");
		*correct = 0;
		return;
	} else if (*x1 == *y1 && *y1 == *x2 && *x2 == *y2) {
		printf("Invalid set of coordinates\n");
		*correct = 0;
		return;
	} else if (*y1 == *y2 || *x1 == *x2) {
		printf("Invalid set of coordinates\n");
		*correct = 0;
		return;
	} else if (*y1 > height || *y2 > height) {
		printf("Invalid set of coordinates\n");
		*correct = 0;
		return;

		// Keep the width and height coordinates in ascending order
	} else {
		int aux;
		if (*x1 > *x2) {
			aux = *x1;
			*x1 = *x2;
			*x2 = aux;
		}
		if (*y1 > *y2) {
			aux = *y1;
			*y1 = *y2;
			*y2 = aux;
		}
		*correct = 1;
		printf("Selected %d %d %d %d\n", *x1, *y1, *x2, *y2);
	}
}

// This function selects the whole area.
void SELECT_ALL(int *width, int *height, int *x1, int *y1, int *x2, int *y2,
		int has_been_cropped, int *px1, int *py1)
{
	if (!has_been_cropped) {
		*x1 = 0;
		*y1 = 0;
		*x2 = *height;
		*y2 = *width;
		printf("Selected ALL\n");
		return;
	} else if (has_been_cropped) {
		*x2 = *px1 + *height;
		*y2 = *py1 + *width;
		*x1 = *px1;
		*y1 = *py1;
		printf("Selected ALL\n");
		return;
	}
}

// This functions swaps the values of two variables
void swap(int *var1, int *var2)
{
	int aux = *var1;
	*var1 = *var2;
	*var2 = aux;
}

// This function rotates a square selection of a pgm image at 90 degrees
void rotate90_pgm_not_whole_map(unsigned char ***image, int *x1, int *y1,
				int *x2, int *y2)
{
	// Get the minimum square matrix necessary
	int new_height = (*x2 - *x1);
	int new_width = (*y2 - *y1);
	int max_size = new_height;
	if (max_size < new_width)
		max_size = new_width;

	// Memory allocation for rotation
	unsigned char **pixels =
		(unsigned char **)calloc(max_size, sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixels[i] = (unsigned char *)calloc(max_size,
						    sizeof(unsigned char));

	// Copy values in the clone matrix
	for (int i = 0; i < new_height; i++)
		for (int j = 0; j < new_width; j++)
			pixels[i][j] = (*image)[*x2 - 1 - i][*y1 + j];

	// Save changes accordingly
	for (int i = 0; i < new_width; i++)
		for (int j = 0; j < new_height; j++)
			(*image)[*x1 + j][*y1 + i] = pixels[i][j];

	free_pixels((*x2 - *x1), &pixels);
}

// This function rotates a square selection of a pgm image at 180 degrees
void rotate180_pgm_not_whole_map(unsigned char ***image, int *x1, int *y1,
				 int *x2, int *y2)
{
	// Get the minimum square matrix necessary
	int max_size = (*y2 - *y1);
	if (max_size < (*x2 - *x1))
		max_size = (*x2 - *x1);

	// Memory allocation for rotation
	unsigned char **pixels = (unsigned char **)malloc(max_size *
							  sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixels[i] = (unsigned char *)malloc(max_size *
						   sizeof(unsigned char));

	// Copy values in the matrix copy
	for (int i = 0; i < (*x2 - *x1); i++)
		for (int j = 0; j < (*y2 - *y1); j++)
			pixels[i][j] = (*image)[*x1 + i][*y1 + j];

	// Put the correct values in the original matrix
	for (int i = 0; i < (*y2 - *y1); i++)
		for (int j = 0; j < (*x2 - *x1); j++)
			(*image)[*x1 + i][*y1 + j] =
				pixels[(*x2 - *x1) - 1 - i][(*y2 - *y1) - 1 - j];

	// Free the matrix copy
	free_pixels(max_size, &pixels);
}

// This function rotates a square selection of a pgm image at 270 degrees
void rotate270_pgm_not_whole_map(unsigned char ***image, int *x1, int *y1,
				 int *x2, int *y2)
{
	// Get the minimum square matrix necessary
	int new_height = (*x2 - *x1);
	int new_width = (*y2 - *y1);
	int max_size = new_height;
	if (max_size < new_width)
		max_size = new_width;

	// Memory allocation for rotation
	unsigned char **pixels =
		(unsigned char **)calloc(max_size, sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixels[i] = (unsigned char *)calloc(max_size,
						    sizeof(unsigned char));

	// Copy values in the clone matrix
	for (int i = 0; i < new_height; i++)
		for (int j = 0; j < new_width; j++)
			pixels[i][j] = (*image)[*x1 + i][*y1 + j];

	// Save changes accordingly
	for (int i = 0; i < new_width; i++)
		for (int j = 0; j < new_height; j++)
			(*image)[*x1 + i][*y1 + j] =
				pixels[j][new_width - 1 - i];

	free_pixels((*x2 - *x1), &pixels);
}

// This function rotates a square selection of a ppm image at 90 degrees
void rotate90_ppm_not_whole_map(unsigned char ***image, int *x1, int *y1,
				int *x2, int *y2)
{
	// Get the minimum square matrix necessary
	int new_height = (*y2 - *y1) / 3;
	int new_width = (*x2 - *x1) * 3;
	int max_size = new_height;
	if (max_size < new_width)
		max_size = new_width;

	// Memory allocation for rotation
	unsigned char **pixel_matrix =
		(unsigned char **)calloc(max_size,
		sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)calloc(max_size,
							  sizeof(unsigned char));

	// Copy values in the clone matrix
	int p = (*x2 - *x1) - 1, k = 0, keep_pos = 0;

	for (int i = 0; i < new_height; i++) {
		p = (*x2 - *x1) - 1;
		k = keep_pos;
		for (int j = 0; j < new_width; j++) {
			pixel_matrix[i][j] = (*image)[*x1 + p][*y1 + k];
			k++;
			if (k == (keep_pos + 3)) {
				p--;
				k = keep_pos;
			}
		}
		keep_pos += 3;
	}

	for (int i = 0; i < new_height; i++)
		for (int j = 0; j < new_width; j++)
			(*image)[*x1 + i][*y1 + j] = pixel_matrix[i][j];

	free_pixels(max_size, &pixel_matrix);
}

// This function rotates a square selection of a ppm image at 180 degrees
void rotate180_ppm_not_whole_map(unsigned char ***image, int *x1, int *y1,
				 int *x2, int *y2)
{
	// Get the minimum square matrix necessary
	int max_size = (*x2 - *x1);
	if (max_size < (*y2 - *y1))
		max_size = (*y2 - *y1);

	// Memory allocation for rotation
	unsigned char **pixel_matrix = (unsigned char **)malloc(max_size *
								sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)malloc(max_size *
							  sizeof(unsigned char));

	// Copy values in the matrix copy
	for (int i = 0; i < (*x2 - *x1); i++)
		for (int j = 0; j < (*y2 - *y1); j++)
			pixel_matrix[i][j] = (*image)[*x1 + i][*y1 + j];

	// Put the correct values in the original matrix
	int p = (*x2 - *x1) - 1;
	int k = (*y2 - *y1) - 3;
	int limit = (*y2 - *y1);

	for (int i = 0; i < (*x2 - *x1); i++) {
		for (int j = 0; j < (*y2 - *y1); j++) {
			(*image)[*x1 + i][*y1 + j] = pixel_matrix[p][k];
			k++;
			if (k == limit) {
				k = k - 6;
				limit -= 3;
			}
		}
		p--;
		k = (*y2 - *y1) - 3;
		limit = (*y2 - *y1);
	}

	// Free the matrix copy
	free_pixels(max_size, &pixel_matrix);
}

// This function rotates a square selection of a ppm image at 270 degrees
void rotate270_ppm_not_whole_map(unsigned char ***image, int *x1, int *y1,
				 int *x2, int *y2)
{
	// Get the minimum square matrix necessary
	int new_height = (*y2 - *y1) / 3;
	int new_width = (*x2 - *x1) * 3;
	int max_size = new_height;
	if (max_size < new_width)
		max_size = new_width;

	// Memory allocation for rotation
	unsigned char **pixel_matrix =
		(unsigned char **)calloc(max_size,
			sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)calloc(max_size,
							  sizeof(unsigned char));

	// Copy values in the clone matrix
	int p = 0, k = 0, keep_pos = 0;
	for (int i = new_height - 1; i >= 0; i--) {
		k = keep_pos;
		p = 0;
		for (int j = 0; j < new_width; j++) {
			pixel_matrix[i][j] = (*image)[*x1 + p][*y1 + k];
			k++;
			if (k == (keep_pos + 3)) {
				p++;
				k = keep_pos;
			}
		}
			keep_pos += 3;
	}

	for (int i = 0; i < new_height; i++)
		for (int j = 0; j < new_width; j++)
			(*image)[*x1 + i][*y1 + j] = pixel_matrix[i][j];

	free_pixels(max_size, &pixel_matrix);
}

// This function rotates a pgm image at 90 degrees
void rotate90_pgm_whole_map_selected(unsigned char ***image, int *x1, int *y1,
				     int *x2, int *y2, int *width, int *height,
				     int *px1, int *px2, int *py1, int *py2)
{
	// Get the minimum square matrix necessary
	int max_size = *width;
	if (max_size < *height)
		max_size = *height;

	// Memory allocation for rotation
	unsigned char **pixel_matrix =
		(unsigned char **)calloc(max_size,
			sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)calloc(max_size,
							  sizeof(unsigned char));

	// Copy values in the clone matrix
	int k = 0, count = 0;
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {
			pixel_matrix[i][j] =
				(*image)[*px2 - 1 - count][*py1 + k];
			count++;
			if (count == *height) {
				k++;
				count = 0;
			}
		}
	}

	// Save and change coordinates accordingly
	*image = pixel_matrix;
	*width = (*x2 - *x1);
	*height = (*y2 - *y1);

	*px2 -= *px1;
	*py2 -= *py1;
	swap(py2, px2);
	*px1 = 0;
	*py1 = 0;
	*x1 = *px1;
	*y1 = *py1;
	*x2 = *px2;
	*y2 = *py2;
}

// This function rotates a ppm image at 90 degrees
void rotate90_ppm_whole_map_selected(unsigned char ***image, int *x1, int *y1,
				     int *x2, int *y2, int *width, int *height,
				     int *px1, int *px2, int *py1, int *py2)
{
	// Get the minimum square matrix necessary
	int new_height = *width / 3;
	int new_width = *height * 3;
	int max_size = new_height;
	if (max_size < new_width)
		max_size = new_width;

	// Memory allocation for rotation
	unsigned char **pixel_matrix =
		(unsigned char **)calloc(max_size,
			sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)calloc(max_size,
							  sizeof(unsigned char));

	// Copy values in the clone matrix
	int p = *px2 - 1, k = 0, keep_pos = 0;

	for (int i = 0; i < new_height; i++) {
		p = *px2 - 1;
		k = keep_pos;
		for (int j = 0; j < new_width; j++) {
			pixel_matrix[i][j] = (*image)[p][k];
			k++;
			if (k == (keep_pos + 3)) {
				p--;
				k = keep_pos;
			}
		}
		keep_pos += 3;
	}

	// Save and change coordinates accordingly
	*image = pixel_matrix;
	*width = (*x2 - *x1) * 3;
	*height = (*y2 - *y1) / 3;

	*px2 -= *px1;
	*py2 -= *py1;
	swap(py2, px2);
	*px1 = 0;
	*py1 = 0;
	*py2 *= 3;
	*px2 /= 3;
	*x1 = *px1;
	*y1 = *py1;
	*x2 = *px2;
	*y2 = *py2;
}

// This function rotates a pgm image at 180 degrees
void rotate180_pgm_whole_map_selected(unsigned char ***image, int *width, int *height)
{
	// Get the minimum square matrix necessary
	int max_size = *height;
	if (max_size < *width)
		max_size = *width;

	// Memory allocation for rotation
	unsigned char **pixel_matrix = (unsigned char **)malloc(max_size *
								sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)malloc(max_size *
							  sizeof(unsigned char));

	// Copy values in the matrix copy
	for (int i = 0; i < *height; i++)
		for (int j = 0; j < *width; j++)
			pixel_matrix[i][j] = (*image)[i][j];

	// Put the correct values in the original matrix
	for (int i = 0; i < *height; i++) {
		for (int j = 0; j < *width; j++) {
			(*image)[i][j] =
				pixel_matrix[*height - 1 - i][*width - 1 - j];
		}
	}

	// Free the matrix copy
	free_pixels(max_size, &pixel_matrix);
}

// This function rotates a ppm image at 180 degrees
void rotate180_ppm_whole_map_selected(unsigned char ***image, int *width, int *height)
{
	// Get the minimum square matrix necessary
	int max_size = *height;
	if (max_size < *width)
		max_size = *width;

	// Memory allocation for rotation
	unsigned char **pixel_matrix = (unsigned char **)malloc(max_size *
								sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)malloc(max_size *
							  sizeof(unsigned char));

	// Copy values in the matrix copy
	for (int i = 0; i < *height; i++)
		for (int j = 0; j < *width; j++)
			pixel_matrix[i][j] = (*image)[i][j];

	// Put the correct values in the original matrix
	int p = *height - 1;
	int k = *width - 3;
	int limit = *width;
	for (int i = 0; i < *height; i++) {
		for (int j = 0; j < *width; j++) {
			(*image)[i][j] = pixel_matrix[p][k];
			k++;
			if (k == limit) {
				k = k - 6;
				limit -= 3;
			}
		}
		p--;
		k = *width - 3;
		limit = *width;
	}

	// Free the matrix copy
	free_pixels(max_size, &pixel_matrix);
}

// This function rotates a pgm image at 270 degrees
void rotate270_pgm_whole_map_selected(unsigned char ***image, int *x1, int *y1,
				      int *x2, int *y2, int *width, int *height,
				      int *px1, int *px2, int *py1, int *py2)
{
	// Get the minimum square matrix necessary
	int max_size = *width;
	if (max_size < *height)
		max_size = *height;

	// Memory allocation for rotation
	unsigned char **pixel_matrix =
		(unsigned char **)calloc(max_size,
			sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)calloc(max_size,
							  sizeof(unsigned char));

	// Copy values in the clone matrix
	int k = 0, count = 0;
	for (int i = 0; i < *width; i++) {
		for (int j = 0; j < *height; j++) {
			pixel_matrix[i][j] =
				(*image)[*px1 + k][*py2 - 1 - count];
			k++;
			if (*px1 + k == *px2) {
				k = 0;
				count++;
			}
		}
	}

	// Save and change coordinates accordingly
	*image = pixel_matrix;
	*width = (*x2 - *x1);
	*height = (*y2 - *y1);

	*px2 -= *px1;
	*py2 -= *py1;
	swap(py2, px2);
	*px1 = 0;
	*py1 = 0;
	*x1 = *px1;
	*y1 = *py1;
	*x2 = *px2;
	*y2 = *py2;
}

// This function rotates a ppm image at 270 degrees
void rotate270_ppm_whole_map_selected(unsigned char ***image, int *x1, int *y1,
				      int *x2, int *y2, int *width, int *height,
				      int *px1, int *px2, int *py1, int *py2)
{
	// Get the minimum square matrix necessary
	int new_height = *width / 3;
	int new_width = *height * 3;
	int max_size = new_height;
	if (max_size < new_width)
		max_size = new_width;

	// Memory allocation for rotation
	unsigned char **pixel_matrix =
		(unsigned char **)calloc(max_size, sizeof(unsigned char *));
	for (int i = 0; i < max_size; i++)
		pixel_matrix[i] = (unsigned char *)calloc(max_size,
							  sizeof(unsigned char));

	// Copy values in the clone matrix
	int k = 0, count = 0, new_lim = *py2;

	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			pixel_matrix[i][j] =
				(*image)[*px1 + k][new_lim - 3 + count];
			count++;
			if (count == 3) {
				k++;
				count = 0;
			}
		}
		k = 0;
		count = 0;
		new_lim -= 3;
	}

	// Save and change coordinates accordingly
	*image = pixel_matrix;
	*width = new_width;
	*height = new_height;

	*px2 -= *px1;
	*py2 -= *py1;
	swap(py2, px2);
	*px1 = 0;
	*py1 = 0;
	*py2 *= 3;
	*px2 /= 3;
	*x1 = *px1;
	*y1 = *py1;
	*x2 = *px2;
	*y2 = *py2;
}

// This function rotates the image or a selection of pixels from the image by a
// certain angle.
void ROTATE(int angle, unsigned char ***image, int *x1, int *y1, int *x2,
	    int *y2, const int whole_map_selected, int *width, int *height,
	    const int color_image, int *px1, int *py1, int *px2, int *py2)
{
	// Case one: only a part of the image is selected (a square submatrix)
	if (!whole_map_selected && color_image == 0) {
		// Rotate to 90/-270 degrees
		if (angle == 90 || angle == -270)
			rotate90_pgm_not_whole_map(image, x1, y1, x2, y2);

		// Rotate to 180/-180 degrees
		else if (angle == 180 || angle == -180)
			rotate180_pgm_not_whole_map(image, x1, y1, x2, y2);

		// Rotate to -90/270 degrees
		else if (angle == -90 || angle == 270)
			rotate270_pgm_not_whole_map(image, x1, y1, x2, y2);

	} else if (!whole_map_selected && color_image == 1) {
		// Rotate to 90/-270 degrees
		if (angle == 90 || angle == -270)
			rotate90_ppm_not_whole_map(image, x1, y1, x2, y2);

		// Rotate to 180/-180 degrees
		else if (angle == 180 || angle == -180)
			rotate180_ppm_not_whole_map(image, x1, y1, x2, y2);

		// Rotate to -90/270 degrees
		else if (angle == -90 || angle == 270)
			rotate270_ppm_not_whole_map(image, x1, y1, x2, y2);

	// Case two: the whole map is selected (it might not be a square matrix)
	} else if (whole_map_selected) {
		// Rotate to 90/-270 degrees a pgm image
		if ((angle == 90 || angle == -270) && color_image == 0)
			rotate90_pgm_whole_map_selected(image, x1, y1, x2, y2, width,
							height, px1, px2, py1, py2);

		// Rotate to 90/-270 degrees a ppm image
		else if ((angle == 90 || angle == -270) && color_image == 1)
			rotate90_ppm_whole_map_selected(image, x1, y1, x2, y2, width,
							height, px1, px2, py1, py2);

		// Rotate to 180/-180 degrees a pgm image
		else if ((angle == 180 || angle == -180) && color_image == 0)
			rotate180_pgm_whole_map_selected(image, width, height);

		// Rotate to 180/-180 degrees a ppm image
		else if ((angle == 180 || angle == -180) && color_image == 1)
			rotate180_ppm_whole_map_selected(image, width, height);

		// Rotate to 270/-90 degrees a pgm image
		else if ((angle == 270 || angle == -90) && color_image == 0)
			rotate270_pgm_whole_map_selected(image, x1, y1, x2, y2, width,
							 height, px1, px2, py1, py2);

		// Rotate to 270/-90 degrees a ppm image
		else if ((angle == 270 || angle == -90) && color_image == 1)
			rotate270_ppm_whole_map_selected(image, x1, y1, x2, y2, width,
							 height, px1, px2, py1, py2);
	}
	printf("Rotated %d\n", angle);
}

// This function crops the image.
void CROP(int *x1, int *y1, int *x2, int *y2, int *width, int *height,
	  const int color_image, int *cropped, int *has_been_cropped)
{
	if (color_image == 0) {
		*height = *x2 - *x1;
		*width = *y2 - *y1;
	} else if (color_image == 1) {
		*height = *x2 - *x1;
		*width = *y2 - *y1;
	}
	*cropped = 1;
	*has_been_cropped = 1;
	printf("Image cropped\n");
}

// This function will turn the image to grayscale format.
void GRAYSCALE(int *x1, int *y1, int *x2, int *y2, unsigned char ***image)
{
	double R, G, B;
	int R_int, G_int, B_int;
	for (int i = *x1; i < *x2; i++)
		for (int j = *y1; j < *y2; j = j + 3) {
			// Formula for RGB to GRAYSCALE
			R = (double)((*image)[i][j] + (*image)[i][j + 1] +
						 (*image)[i][j + 2]) / 3.0;
			G = R;
			B = R;

			R_int = round(R);
			G_int = round(G);
			B_int = round(B);

			// Apply the new colors
			(*image)[i][j] = R_int;
			(*image)[i][j + 1] = G_int;
			(*image)[i][j + 2] = B_int;
		}

	printf("Grayscale filter applied\n");
}

// This functions returns the lowest value from the comparison of two values
int minimum_value(int first_value, int second_value)
{
	if (first_value > second_value)
		return second_value;
	return first_value;
}

// This function will turn the image to sepia format.
void SEPIA(int *x1, int *y1, int *x2, int *y2, unsigned char ***image,
	   const int my_image_max)
{
	double R, G, B;
	int R_int, G_int, B_int;

	for (int i = *x1; i < *x2; i++)
		for (int j = *y1; j < *y2; j = j + 3) {
			// Formula for SEPIA red color.
			R = 0.393 * (*image)[i][j] + 0.769 * (*image)[i][j + 1] +
				0.189 * (*image)[i][j + 2];
			R_int = round(R);
			if (R_int > my_image_max)
				R_int = minimum_value(R_int, my_image_max);

			// Formula for SEPIA green color.
			G = 0.349 * (*image)[i][j] + 0.686 * (*image)[i][j + 1] +
				0.168 * (*image)[i][j + 2];
			G_int = round(G);
			if (G_int > my_image_max)
				G_int = minimum_value(G_int, my_image_max);

			// Formula for SEPIA blue color.
			B = 0.272 * (*image)[i][j] + 0.534 * (*image)[i][j + 1] +
				0.131 * (*image)[i][j + 2];
			B_int = round(B);
			if (B_int > my_image_max)
				B_int = minimum_value(B_int, my_image_max);

			// Apply the new colors
			(*image)[i][j] = R_int;
			(*image)[i][j + 1] = G_int;
			(*image)[i][j + 2] = B_int;
		}

	printf("Sepia filter applied\n");
}

// This function saves the current image to a file in the specified format.
void SAVE(const char *file_name, unsigned char **image, int width,
	  const int height, const int binary, const char type, int my_image_max,
 	  int x1, int y1, int x2, int y2)
{
	FILE *new_file;
	// Save in binary mode
	if (binary == 1) {
		new_file = fopen(file_name, "wb");
		if (!new_file)
			return;

		if (type == '5') {
			char px_type[2] = "P5";
			printf_binary(px_type, new_file, width, height, my_image_max,
						  x1, x2, y1, y2, image);

		} else if (type == '6') {
			char px_type[2] = "P6";
			printf_binary(px_type, new_file, width / 3, height, my_image_max,
						  x1, x2, y1, y2, image);

		} else if (type == '2') {
			char px_type[2] = "P5";
			printf_binary(px_type, new_file, width, height, my_image_max,
						  x1, x2, y1, y2, image);

		} else if (type == '3') {
			char px_type[2] = "P6";
			printf_binary(px_type, new_file, width / 3, height, my_image_max,
						  x1, x2, y1, y2, image);
		}

	// Save in ascii mode
	} else if (binary == 0) {
		new_file = fopen(file_name, "wt"); // open text file
		if (!new_file)
			return;

		if (type == '2') {
			char px_type[2] = "P2";
			printf_ascii(px_type, new_file, width, height, my_image_max,
						 x1, x2, y1, y2, image);

		} else if (type == '3') {
			char px_type[2] = "P3";
			printf_ascii(px_type, new_file, width / 3, height, my_image_max,
						 x1, x2, y1, y2, image);
		}

		else if (type == '5') {
			char px_type[2] = "P2";
			printf_ascii(px_type, new_file, width, height, my_image_max,
						 x1, x2, y1, y2, image);
		}

		else if (type == '6') {
			char px_type[2] = "P3";
			printf_ascii(px_type, new_file, width / 3, height, my_image_max,
						 x1, x2, y1, y2, image);
		}
	}
	printf("Saved %s\n", file_name);
}

// This function checks if the conditions for the load function
// are met and calls the function if true
void call_load_function(char *first_command, char *file_name,
			int *image_status, int *width, int *height,
			int *x1, int *y1, int *x2, int *y2, int *color_image,
			int *my_image_max, char *type, int *whole_map_selected,
			int *px1, int *py1, int *px2, int *py2,
			unsigned char ***image, char **input)
{
	// Get file name
	if (sscanf(*input, "%s %s", first_command, file_name) == 0)
		return;

	// Load the image in a dynamic matrix
	*image_status = DOWNN;
	*image = LOAD(file_name, width, height, x1, y1, x2, y2, color_image,
		      my_image_max, type);

	// Keep the starting values of the image for printing reasons
	*px1 = *x1; *py1 = *y1; *px2 = *x2; *py2 = *y2;
	*whole_map_selected = 1;

	// Check image status
	if (*image == (unsigned char **)ERR)
		*image_status = DOWNN;
	else if (*image)
		*image_status = UPP;
}

// This function checks if the conditions for the select function
// are met and calls the function if true
void call_select_function(int *image_status, int *correct, int *replace1,
			  int *replace2, int *replace3, int *replace4,
			  int *width, int *height, int *color_image,
			  int *whole_map_selected, int *px1, int *px2,
			  int *py1, int *py2, int *x1, int *x2, int *y1,
			  int *y2, char **input, char *first_command)
{
	if (sscanf(*input, "%s %d %d %d %d", first_command, replace1,
			   replace2, replace3, replace4) == 5) {
		if (*image_status == UPP) {
			*correct = 0;
			SELECT(replace1, replace2, replace3, replace4, *width,
			       *height, correct, *color_image);

			// If valid coordinates are given (coordinates are valid
			// if they are within the limits of the image)
			if (*correct == 1 && *color_image == 0) {
				*y1 = *replace1 + *px1;
				*x1 = *replace2 + *py1;
				*y2 = *replace3 + *px1;
				*x2 = *replace4 + *py1;
				*correct = 0;
				if (*x1 == *px1 && *y1 == *py1 && *x2 == *px2 &&
					*y2 == *py2) {
					*whole_map_selected = 1;
				} else {
					*whole_map_selected = 0;
				}
			} else if (*correct == 1 && *color_image == 1) {
				*y1 = (*replace1 + *px1) * 3;
				*x1 = *replace2 + *py1 / 3;
				*y2 = (*replace3 + *px1) * 3;
				*x2 = *replace4 + *py1 / 3;
				*correct = 0;
				if (*x1 == *px1 && *y1 == *py1 && *x2 == *px2 &&
					*y2 == *py2)
					*whole_map_selected = 1;
				else
					*whole_map_selected = 0;
			}
		} else {
			printf("No image loaded\n");
		}
	} else {
		printf("Invalid command\n");
	}
}

// This function checks if the conditions for the select all function
// are met and calls the function if true
void call_select_all_function(int *image_status, int *width, int *height,
			      int *x1, int *y1, int *x2, int *y2,
			      int *has_been_cropped, int *px1, int *py1,
			      int *whole_map_selected)
{
	if (*image_status == UPP) {
		SELECT_ALL(width, height, x1, y1, x2, y2, *has_been_cropped, px1,
			   py1);
		*whole_map_selected = 1;
	} else {
		printf("No image loaded\n");
	}
}

// This function checks if the conditions for the crop function
// are met and calls the function if true
void call_crop_function(int *image_status, int *x1, int *y1, int *x2, int *y2,
			int *width, int *height, int *color_image,
			int *cropped, int *has_been_cropped, int *px1,
			int *py1, int *px2, int *py2, int *whole_map_selected)
{
	if (*image_status == UPP) {
		CROP(x1, y1, x2, y2, width, height, *color_image, cropped,
			 has_been_cropped);
		*px1 = *x1; *py1 = *y1; *px2 = *x2; *py2 = *y2;
		*whole_map_selected = 1;
	} else {
		printf("No image loaded\n");
	}
}

// This function checks if the conditions for the grayscale function
// are met and calls the function if true
void call_grayscale_function(int *image_status, int *color_image, int *x1,
			     int *y1, int *x2, int *y2, unsigned char ***image)
{
	if (*image_status == UPP) {
		// Apply GRAYSCALE filter only if the image is a color one
		if (*color_image == 1)
			GRAYSCALE(x1, y1, x2, y2, image);
		else
			printf("Grayscale filter not available\n");
	} else {
		printf("No image loaded\n");
	}
}

// This function checks if the conditions for the sepia function
// are met and calls the function if true
void call_sepia_function(int *image_status, int *color_image, int *x1,
			 int *y1, int *x2, int *y2, unsigned char ***image,
			 int *my_image_max)
{
	if (*image_status == UPP) {
		// Apply SEPIA filter only if the image is a color one
		if (*color_image == 1)
			SEPIA(x1, y1, x2, y2, image, *my_image_max);
		else
			printf("Sepia filter not available\n");
	} else {
		printf("No image loaded\n");
	}
}

// This function checks if the conditions for the rotate function
// are met and calls the function if true
void call_rotate_function(char *first_command, int *image_status,
			  int *color_image, int angle, int *x1, int *x2,
			  int *y1, int *y2, int *whole_map_selected,
			  unsigned char ***image, int *width, int *height,
			  int *px1, int *py1, int *px2, int *py2, char **input)
{
	if (sscanf(*input, "%s %d", first_command, &angle) == 2) {
		if (*image_status == UPP) {// If the image is loaded execute this.
			if (*color_image == 0) {
				// Check for valid angle
				if (angle != 90 && angle != -90 && angle != 180 &&
					angle != -180 && angle != 270 && angle != -270 &&
					angle != 360 && angle != -360 && angle != 0) {
					printf("Unsupported rotation angle\n");

				} else if (angle == 360 || angle == -360 || angle == 0) {
					printf("Rotated %d\n", angle);

					// Check if the coordinates form a square image
				} else if ((*x2 - *x1) != (*y2 - *y1) &&
						*whole_map_selected == 0) {
					printf("The selection must be square\n");

				} else {
					ROTATE(angle, image, x1, y1, x2, y2,
					       *whole_map_selected, width, height, *color_image,
					       px1, py1, px2, py2);
				}
			}

			else if (*color_image == 1) {
				// Check for valid angle
				if (angle != 90 && angle != -90 && angle != 180 &&
					angle != -180 && angle != 270 && angle != -270 &&
					angle != 360 && angle != -360 && angle != 0) {
					printf("Unsupported rotation angle\n");

				} else if (angle == 360 || angle == -360 || angle == 0) {
					printf("Rotated %d\n", angle);

					// Check if the coordinates form a square image
				} else if ((*x2 - *x1) != (*y2 - *y1) &&
						(*x2 - *x1) != ((*y2 - *y1) / 3) &&
						*whole_map_selected == 0) {
					printf("The selection must be square\n");

				} else {
					ROTATE(angle, image, x1, y1, x2, y2,
					       *whole_map_selected, width, height, *color_image,
					       px1, py1, px2, py2);
				}
			}
		} else { //Else display "No image loaded"
			printf("No image loaded\n");
		}
	}
}

// This function checks if the conditions for the save function
// are met and calls the function if true
void call_save_function(char *first_command, char *new_file, char *print_type,
			char **input, int *binary, int *image_status,
			unsigned char ***image, int *width, int *height,
			char *type, int *my_image_max, int *px1, int *py1,
			int *px2, int *py2)
{
	if (sscanf(*input, "%s %s %s", first_command, new_file, print_type) != 0) {
		if (strcmp(print_type, "ascii") == 0)
			*binary = 0;
		else
			*binary = 1;
		free(print_type);

		if (*image_status == UPP) {
			SAVE(new_file, *image, *width, *height, *binary, *type,
			     *my_image_max, *px1, *py1, *px2, *py2);
		} else {
			printf("No image loaded\n");
		}
	}
}

// This function closes the program and frees the memory.
void EXIT(unsigned char ***image, const int height)
{
	free_pixels(height, image);
	exit(EXIT_SUCCESS);
}

// This functions checks if an valid command has been received
// and, if true, executes the corresponding function
void check_command(int command_value, int *width, int *height,
		   int *image_status, int *x1, int *y1, int *x2, int *y2,
	 	   unsigned char ***image, char **input, int *color_image,
	 	   char *type, int *my_image_max, int *whole_map_selected,
		   int *correct, int *cropped, int *has_been_cropped, int *px1,
		   int *py1, int *px2, int *py2)
{
	*correct = 1; // Declare variables
	int replace1, replace2, replace3, replace4, angle = 0, binary = 0;
	char *file_name = (char *)malloc(NAME_LENGTH_MAX * sizeof(char));
	char *new_file = (char *)malloc(LENGTH_MAX * sizeof(char));
	char *print_type = (char *)malloc(LENGTH_MAX * sizeof(char));
	char *first_command = (char *)malloc(MAX_COMMAND_SIZE * sizeof(char));

	switch (command_value) { // Switch based on the command_value variable
	case 0: // FUNCTION: LOAD
		call_load_function(first_command, file_name, image_status, width,
				   height, x1, y1, x2, y2, color_image, my_image_max,
				   type, whole_map_selected, px1, py1, px2, py2,
				    image, input);
		free(first_command); break;
	case 1: // FUNCTION: SELECT
		call_select_function(image_status, correct, &replace1, &replace2,
				    &replace3, &replace4, width, height,
				    color_image, whole_map_selected, px1, px2, py1,
				    py2, x1, x2, y1, y2, input, first_command); break;
	case 2: // FUNCTION: SELECT ALL
		call_select_all_function(image_status, width, height, x1, y1, x2, y2,
					 has_been_cropped, px1, py1,
					 whole_map_selected); break;
	case 3: // FUNCTION: ROTATE
		call_rotate_function(first_command, image_status, color_image,
				     angle, x1, x2, y1, y2, whole_map_selected, image,
				     width, height, px1, py1, px2, py2, input); break;
	case 4: // FUNCTION: CROP
		call_crop_function(image_status, x1, y1, x2, y2, width, height,
				     color_image, cropped, has_been_cropped, px1,
				     py1, px2, py2, whole_map_selected); break;
	case 5: // FUNCTION: GRAYSCALE
		call_grayscale_function(image_status, color_image, x1, y1, x2, y2,
								image); break;
	case 6: // FUNCTION: SEPIA
		call_sepia_function(image_status, color_image, x1, y1, x2, y2,
				    image, my_image_max); break;
	case 7: // FUNCTION: SAVE
		call_save_function(first_command, new_file, print_type, input, &binary,
				   image_status, image, width, height, type,
				   my_image_max, px1, py1, px2, py2); break;
	case 8: // FUNCTION: EXIT
		if (*image_status == UPP) {
			EXIT(image, *height);
		} else {
			printf("No image loaded\n");
			exit(EXIT_SUCCESS);
		}
		break;
	default: // NO RECOGNIZED FUNCTION: "INVALID COMMAND"
		printf("Invalid command\n");
		break;
	}
}
