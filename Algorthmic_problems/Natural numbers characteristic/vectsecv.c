//  Chelcea Claudiu Marian
#include <stdio.h>
#define NMAX 100

// SDescending sort of array
void selection_sort(int v[], int nr_el_period)
{
	int poz, aux;
	for (int i = 0; i < nr_el_period; i++) {
		poz = i;
		for (int j = i + 1; j < nr_el_period; j++)
			if (v[poz] < v[j])
				poz = j;
		aux = v[i];
		v[i] = v[poz];
		v[poz] = aux;
	}
}

int main(void)
{   
	// Declaration & Definitions
	int v[NMAX], i = 0, aux[NMAX], nr_of_differences, differences_array[NMAX], n;
	int period_start = 0, exit = 0, nr_el_period = 0;
	scanf("%d", &differences_array[0]);

	// Turn number n into an vector and sort its digits
	for (int index = 1;; index++) {
		n = differences_array[index - 1];
		while (n) {
			v[i] = n % 10;
			n = n / 10;
			i++;
		}

		selection_sort(v, i);
		// Turn the previos array into two numbers, n_ascening & n_descending
		int n_descending = 0, n_ascending = 0;
		for (int k = 0; k < i; k++)
			n_descending = n_descending * 10 + v[k];
		for (int k = i - 1; k >= 0; k--)
			if (v[k] != 0)
				n_ascending = n_ascending * 10 + v[k];
				
		// Clear arrays used content
		for (int q = 0; q < i; q++)
			v[q] = 0;
		
		// Save the differences in differences_array
		i = 0;
		differences_array[index] = n_descending - n_ascending;

		// In aux array we`ll save the period and check the exit condition
		for (int k = 0; k < index; k++) {
			for (int l = k + 1; l < index; l++)
				if (differences_array[k] == differences_array[l]) {
					period_start = k;
					nr_of_differences = k;
					exit = 1;
					for (int m = 0; m < (l - k); m++) {
						aux[m] = differences_array[period_start];
						period_start++;
						nr_el_period++;
					}
				}
		}

		// Display the number of differences before the start of the period
		// Display the period
		if (exit == 1) {
			if (differences_array[0] == differences_array[1]) {
				nr_of_differences = 0;
				printf("%d\n", nr_of_differences);
			} else {
				printf("%d\n", nr_of_differences - 1);
			}

			for (int contor = 0; contor < nr_el_period; contor++)
				printf("%d ", aux[contor]);
			break;
		}
		period_start = 0;
	}

	return 0;
}
