// Chelcea Claudiu Marian
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Power function
int power (int x, int y) {
	if (y == 0)
		return 1;
	return x * power (x, y - 1);
}

// Reverse array of int function
void reverse_array (int* v, int n) {
	int aux;
	for (int i = 0; i < n; i++) {
		aux      = v[i];
		v[i]     = v[n - 1];
		v[n - 1] = aux;
		n--;
	}
}
// Reverse array of char function
void reverse_array_char (char* v, int n) {
	char aux;
	for (int i = 0; i < n; i++) {
		aux      = v[i];
		v[i]     = v[n - 1];
		v[n - 1] = aux;
		n--;
	}
}

// Reverse a vector by 4
void reverse_4 (char* v) {
	char* aux = (char*)malloc (8 * sizeof (char));
	aux[0]    = v[4];
	aux[1]    = v[5];
	aux[2]    = v[6];
	aux[3]    = v[7];
	aux[4]    = v[0];
	aux[5]    = v[1];
	aux[6]    = v[2];
	aux[7]    = v[3];
	memmove (v, aux, 8);
	free (aux);
}

// Reverse an array of 8 elements by 2
// 01 23 54 24
// 10 32 45 42
void reverse_by_2 (char* v) 
{
	char* aux = (char*)malloc (8 * sizeof (char));
	aux[0]    = v[6];
	aux[1]    = v[7];
	aux[2]    = v[4];
	aux[3]    = v[5];
	aux[4]    = v[2];
	aux[5]    = v[3];
	aux[6]    = v[0];
	aux[7]    = v[1];
	memmove (v, aux, 8);
	free (aux);
}

// Reverse a short type by 4
// 0000 1111 --> 1111 0000
void change_short (char* v) {
	char* aux = (char*)malloc (8 * sizeof (char));
	for (int re = 0; re < 8; re++)
		aux[re] = v[re];

	for (int i = 0; i < 4; i++)
		v[i] = aux[i + 4];
	for (int i = 0; i < 4; i++)
		v[i + 4] = aux[i];
	free (aux);
}

// Swap two chars
void swap (char* a, char* b) {
	char temp = *a;
	*a        = *b;
	*b        = temp;
}

// Swap two ints
void swap_int (int* a, int* b) {
	int temp = *a;
	*a       = *b;
	*b       = temp;
}

// Reverse an int by 2 eleemnts
// 02 34 53 23 -> 23 53 34 02
void change_int (char* v, int n) {

	char* aux = (char*)malloc (8 * sizeof (char));
	memmove (aux, v, 8);
	for (int i = 0; i < 8; i = i + 2)
		swap (&v[i], &v[i + 1]);
	reverse_array_char (v, n);
	free (aux);
}

// Total reverse for int
void reverse_int (int* v) {

	int* aux = (int*)malloc (8 * sizeof (int));
	aux[0]   = v[6];
	aux[1]   = v[7];
	aux[2]   = v[4];
	aux[3]   = v[5];
	aux[4]   = v[2];
	aux[5]   = v[3];
	aux[6]   = v[0];
	aux[7]   = v[1];
	for (int i = 0; i < 8; i++)
		v[i] = aux[i];
	free (aux);
}

// Fill a matrix by Flood FIll algorithm
void Fill_Matrix (int** mx, int li, int cl, int i, int f, int e, int nr_lin) {

	if (li < 0 || li >= nr_lin || cl < 0 || cl >= e)
		return;
	if (mx[li][cl] != i)
		return;
	if (mx[li][cl] == f)
		return;

	mx[li][cl] = f;

	Fill_Matrix (mx, li + 1, cl, i, f, e, nr_lin);
	Fill_Matrix (mx, li - 1, cl, i, f, e, nr_lin);
	Fill_Matrix (mx, li, cl + 1, i, f, e, nr_lin);
	Fill_Matrix (mx, li, cl - 1, i, f, e, nr_lin);
}

// Turn byte to int
int BYTE_to_INT (char bit) {
	int elem_1 = 0;
	switch (bit) {
	case '0': elem_1 = 0; break;
	case '1': elem_1 = 1; break;
	case '2': elem_1 = 2; break;
	case '3': elem_1 = 3; break;
	case '4': elem_1 = 4; break;
	case '5': elem_1 = 5; break;
	case '6': elem_1 = 6; break;
	case '7': elem_1 = 7; break;
	case '8': elem_1 = 8; break;
	case '9': elem_1 = 9; break;
	case 'A': elem_1 = 10; break;
	case 'B': elem_1 = 11; break;
	case 'C': elem_1 = 12; break;
	case 'D': elem_1 = 13; break;
	case 'E': elem_1 = 14; break;
	case 'F': elem_1 = 15; break;
	default: elem_1 = 0;
	}
	return elem_1;
}

// Turn a byte to int
// 00 -> 0 || 01 -> 1 || FF = -1 || FE = -2
int converter (char bit1, char bit2) {
	int* v = (int*)malloc (4 * sizeof (int));

	int elem_1 = 0, elem_2 = 0, result = 0;

	// "elem_1" will take the value of the first byte
	// "elem_2" will take the value of the second byte
	elem_1 = BYTE_to_INT (bit1);
	elem_2 = BYTE_to_INT (bit2);

	v[0] = elem_1;
	v[1] = elem_2;
	reverse_array (v, 2);

	for (int i = 0; i < 2; i++)
		result += (v[i] * power (16, i));

	// Sign number
	if (result > 127)
		result = (result - 256);

	free (v);

	return result;
}

void init_p_int (int** pointer, int dimensiune) {
	*pointer = NULL;
	*pointer = malloc (dimensiune * sizeof (int));
}

void init_char_pointer (char** pointer, int dimensiune) {
	*pointer = NULL;
	*pointer = malloc (dimensiune * sizeof (char));
}

void init_pointer_2_pointer (char*** pointer, int dimensiune) {
	*pointer = NULL;
	*pointer = malloc (dimensiune * sizeof (char*));
}
void init_matrix_2_pointers (int*** pointer, int dimensiune) {
	*pointer = NULL;
	*pointer = malloc (dimensiune * sizeof (int*));
}

// Reverse each element: 00 10 01 11 --> 11 01 10 00
void reverse_an_element (int q, char** list) {

	char* aux = NULL;
	init_char_pointer (&aux, 8);

	for (int i = 0; i < q; i++) {
		aux[0] = list[i][6];
		aux[1] = list[i][7];
		aux[2] = list[i][4];
		aux[3] = list[i][5];
		aux[4] = list[i][2];
		aux[5] = list[i][3];
		aux[6] = list[i][0];
		aux[7] = list[i][1];
		for (int re = 0; re < 8; re++)
			list[i][re] = aux[re];
	}

	free (aux);
}

// Get the arithmetic mean of the margins
double margin_arithmetic_mean (int** nr_el_on_rows, char*** list, int nr_lin) {

	// TOp row
	int sum = 0, count = 0;
	for (int i = 0; i < nr_el_on_rows[0][0]; i++) {
		for (int j = 0; j < 8; j = j + 2) {
			sum += converter (list[0][i][j], list[0][i][j + 1]);
			count++;
		}
	}

	// First column without first and top rows
	int count2 = 1;
	for (int i = (nr_el_on_rows[0][count2 - 1]); count2 < nr_lin - 1;
		 i     = i + nr_el_on_rows[0][count2 - 1]) {
		count2++;
		for (int j = 0; j < 2; j = j + 2) {
			sum += converter (list[0][i][j], list[0][i][j + 1]);
			count++;
		}
	}

	// Last rows
	int poz = 0;
	for (int k = 0; k < (nr_lin - 1); k++) {
		poz += nr_el_on_rows[0][k];
	}

	for (int i = poz; i < (poz + nr_el_on_rows[0][nr_lin - 1]); i++) {
		for (int j = 0; j < 8; j = j + 2) {
			sum += converter (list[0][i][j], list[0][i][j + 1]);
			count++;
		}
	}

	// Right margin
	int count3 = 1;
	for (int i = (nr_el_on_rows[0][0] + nr_el_on_rows[0][1] - 1);
		 count3 < (nr_lin - 1); i = i + nr_el_on_rows[0][count3]) {
		count3++;
		sum += converter (list[0][i][6], list[0][i][7]);
		count++;
	}

	return (double)sum / count;
}

// Find the dimension of each element
int el_dim_by_type (char tip) {
	switch (tip) {
	case 'C': return 1;
	case 'S': return 2;
	case 'I': return 4;
	default: return 0;
	}
}

// How many int elements to add
int how_much_to_add (int* nr_el_on_rows, int row, int dim_el, int idx) {

	int my_bytes = nr_el_on_rows[row - 1] * 4;
	int needed_bytes;
	int needed_ints = 0;
	needed_bytes   = dim_el * idx;
    // Count how many ints to add if needed
	while (needed_bytes > my_bytes) { 
		my_bytes += 4;
		needed_ints++;
	}
	return needed_ints;
}

// Find the starting position
int find_poz_mat (int dim_el, int idx, int poz_mat) {
	if (dim_el == 1) {
		while ((idx - 4) >= 0) {
			poz_mat += 1;
			idx = idx - 4;
		}
	} else if (dim_el == 2) {
		while ((idx - 2) >= 1) {
			poz_mat += 1;
			idx = idx - 2;
		}
	} else if (dim_el == 4) {
		while ((idx - 1) >= 1) {
			poz_mat += 1;
			idx = idx - 1;
		}
	}

	return poz_mat;
}

// Find the index of an element, which part of it to modify
int find_index (int dim_el, int idx, int poz_mat) {
	if (dim_el == 1) {
		while ((idx - 4) >= 1) {
			poz_mat += 1;
			idx = idx - 4;
		}
	} else if (dim_el == 2) {
		while ((idx - 2) >= 1) {
			poz_mat += 1;
			idx = idx - 2;
		}
	} else if (dim_el == 4) {
		while ((idx - 1) >= 1) {
			poz_mat += 1;
			idx = idx - 1;
		}
	}

	return idx;
}

// Modify matrix by element type
void modify_matrix (int d_el, int idx, char*** list, char* val, int poz_mat, char tip) {
	if (d_el == 1) { // CHAR
		if (idx == 1) { // first part
			list[0][poz_mat][0] = val[6];
			list[0][poz_mat][1] = val[7];
		} else if (idx == 2) {
			list[0][poz_mat][2] = val[6];
			list[0][poz_mat][3] = val[7];
		} // second part
		else if (idx == 3) {
			list[0][poz_mat][4] = val[6];
			list[0][poz_mat][5] = val[7];
		} // third part
		else if (idx == 4) {
			poz_mat -= 1;
			list[0][poz_mat][6] = val[6];
			list[0][poz_mat][7] = val[7];
		} // fourth part

	} else if (d_el == 2) {
		if (idx == 1) { // SHORT
			char a = list[0][poz_mat][7];
			char b = list[0][poz_mat][6];
			char c = list[0][poz_mat][5];
			char d = list[0][poz_mat][4];
			reverse_by_2 (list[0][poz_mat]);
			list[0][poz_mat][4] = val[6]; // 3rd el
			list[0][poz_mat][5] = val[7]; // 4th el
			list[0][poz_mat][6] = val[4]; // 1st el
			list[0][poz_mat][7] = val[5]; // 2nd el
			list[0][poz_mat][0] = d; 
			list[0][poz_mat][1] = c; 
			list[0][poz_mat][2] = b; 
			list[0][poz_mat][3] = a; 

			reverse_4 (list[0][poz_mat]);

			return;
		} else if (idx == 2) { // SHORT
			char a = list[0][poz_mat][3];
			char b = list[0][poz_mat][2];
			char c = list[0][poz_mat][1];
			char d = list[0][poz_mat][0];
			reverse_by_2 (list[0][poz_mat]);
			list[0][poz_mat][0] = val[6]; // 3rd el
			list[0][poz_mat][1] = val[7]; // 4th el
			list[0][poz_mat][2] = val[4]; // 1st el
			list[0][poz_mat][3] = val[5]; // 2nd el
			list[0][poz_mat][4] = b;
			list[0][poz_mat][5] = c; 
			list[0][poz_mat][6] = d; 
			list[0][poz_mat][7] = a; 

			swap (&list[0][poz_mat][4], &list[0][poz_mat][6]);
			reverse_4 (list[0][poz_mat]);
			return;
		}

	} else if (d_el == 4) { // INT
		for (int i = 0; i < 8; i++)
			list[0][poz_mat][i] = val[i];
	}

	if (tip == 'S') {
		change_short (list[0][poz_mat]);
	} else if (tip == 'I') {
		change_int (list[0][poz_mat], 8);
	}
}

// Function to delete characters (replace with 0)
void delete_characters (int dim_el, int idx, int poz_mat, char*** list) {
	if (dim_el == 1) {
		while (idx > 4) {
			poz_mat += 1;
			idx -= 4;
		}
		if (idx == 1) {
			list[0][poz_mat][0] = '0';
			list[0][poz_mat][1] = '0';
		} else if (idx == 2) {
			list[0][poz_mat][2] = '0';
			list[0][poz_mat][3] = '0';
		} else if (idx == 3) {
			list[0][poz_mat][4] = '0';
			list[0][poz_mat][5] = '0';
		} else if (idx == 4) {
			list[0][poz_mat - 1][6] = '0';
			list[0][poz_mat - 1][7] = '0';
		}
	} else if (dim_el == 2) {
		while (idx > 2) {
			poz_mat += 1;
			idx -= 2;
		}
		if (idx == 1) {
			for (int iqp = 0; iqp < 4; iqp++)
				list[0][poz_mat][iqp] = '0';
		} else if (idx == 2) {
			for (int iqp = 4; iqp < 8; iqp++)
				list[0][poz_mat][iqp] = '0';
		}
	} else if (dim_el == 4) {
		while (idx > 1) {
			poz_mat += 1;
			idx -= 1;
		}
		for (int iqp = 0; iqp < 8; iqp++)
			list[0][poz_mat][iqp] = '0';
	}
}

// Function to rotate characters
void rotate_characters (int dim_el, int idx, int poz_mat, char*** list) {

	if (dim_el == 2) {
		while (idx >= 2) {
			poz_mat += 1;
			idx -= 2;
		}
		if (idx == 0) {

			char* auxi = NULL;
			auxi       = (char*)malloc (8 * sizeof (char));
			auxi[0]    = list[0][poz_mat][2];
			auxi[1]    = list[0][poz_mat][3];
			auxi[2]    = list[0][poz_mat][0];
			auxi[3]    = list[0][poz_mat][1];
			for (int ipr = 4; ipr < 8; ipr++)
				auxi[ipr] = list[0][poz_mat][ipr];
			for (int re = 0; re < 8; re++)
				list[0][poz_mat][re] = auxi[re];
			free (auxi);
		} else if (idx == 1) {
			reverse_by_2 (list[0][poz_mat]);
			char* auxi = NULL;
			auxi       = (char*)malloc (8 * sizeof (char));
			auxi[0]    = list[0][poz_mat][6];
			auxi[1]    = list[0][poz_mat][7];
			auxi[2]    = list[0][poz_mat][4];
			auxi[3]    = list[0][poz_mat][5];
			for (int ipr = 0; ipr < 4; ipr++)
				auxi[ipr + 4] = list[0][poz_mat][ipr];
			for (int re = 0; re < 8; re++)
				list[0][poz_mat][re] = auxi[re];
			free (auxi);
		}
	}

	else if (dim_el == 4) {
		// Ii gasim pozitia
		while (idx > 0) {
			poz_mat += 1;
			idx -= 1;
		}
		reverse_by_2 (list[0][poz_mat]);
	}
}

// Task 2 display
void afisare_task_2 (int numbers, int* temp, char*** list) {
	int ln = 0;
	for (int i = 0; i < numbers; i++) {
		if (i == temp[ln]) {
			printf ("\n");
			ln++;
			temp[ln] += temp[ln - 1];
		}
		for (int re = 0; re < 8; re++)
			printf ("%c", list[0][i][re]);
		printf (" ");
	}
}

// Find the maximum element of a list
int find_max (int* nr_el_on_rows, int nr_lin) {
	int maximum = 0;
	maximum     = nr_el_on_rows[0];
	for (int i = 1; i < nr_lin; i++) {
		if (maximum < nr_el_on_rows[i])
			maximum = nr_el_on_rows[i];
	}

	return maximum;
}

// Convert char list to int list
void draw_matrix (int nr_lin,
int elements,
int*** mat_bonus,
int* nr_el_on_rows,
char** list) {
	// Initialize the matrix with 1
	for (int i = 0; i < nr_lin; i++) {
		for (int j = 0; j < elements; j++) {
			mat_bonus[0][i][j] = 1;
		}
	}

	int lin = -1, cl = 0;
	for (int i = 0; i < nr_lin; i++)
		for (int j = 0; j < elements; j++) {
			if (j >= (nr_el_on_rows[i] * 4))
				continue;
			if (j % 4 == 0)
				lin++;
			mat_bonus[0][i][j] = converter (
			list[lin][cl], list[lin][cl + 1]);
			cl += 2;
			if (cl == 8)
				cl = 0;
		}

	// The elements that are not equal to 0 become 1
	for (int i = 0; i < nr_lin; i++) {
		for (int j = 0; j < elements; j++)
			if (mat_bonus[0][i][j] != 0)
				mat_bonus[0][i][j] = 1;
	}

	// Change positions by 4
	for (int j = 0; j < elements; j += 4)
		for (int i = 0; i < nr_lin; i++) {
			swap_int (&mat_bonus[0][i][j], &mat_bonus[0][i][j + 3]);
			swap_int (&mat_bonus[0][i][j + 1], &mat_bonus[0][i][j + 2]);
		}
}

// Calculate the number of 0 in a matrix
int how_many_0 (int nr_lin, int elements, int** mat_bonus) {
	int nr_de_0_inainte = 0;
	for (int i = 0; i < nr_lin; i++)
		for (int j = 0; j < elements; j++)
			if (mat_bonus[i][j] == 0)
				nr_de_0_inainte++;
	return nr_de_0_inainte;
	;
}

// Calculate supermassivity and store it
int pos (int l, int b, int*** m, int** v, int c, int d, int** r, int rc, int x)
{ 	
    int nr0d=0;
	int nr0i=0;
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < b; j++) {
			nr0d = 0;
			// Check each element
			if (m[0][i][j] != 0)
				continue;

			// If it`s 0, fill it with 1
			Fill_Matrix (m[0], i, j, 0, 1, b, l);

			// Take its position, because it is equal to 0
			v[0][c]     = i;
			v[0][c + 1] = j;
			c += 2;
			d += 2;
			v[0] = realloc (
			v[0], d * sizeof (int));

			// Count how many 0 are left
			nr0d = how_many_0 (l, b, m[0]);

			// The difference is equal to the suoermassivity
			r[0][rc] = nr0i- nr0d;
			x++;
			r[0] = realloc (r[0], x * sizeof (int));
			rc++;
			nr0i = nr0d;
		}
	}
	return rc;
}

