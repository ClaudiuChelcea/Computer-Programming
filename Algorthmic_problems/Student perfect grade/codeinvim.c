// CHELCEA CLAUDIU MARIAN

#include <stdio.h>

#define NMAX 100

// Interchange two values
void interchange(int *var1, int *var2)
{
	int temp = *var1;
	*var1 = *var2;
	*var2 = temp;
}

// Calculate the curent score
int curent_score(int nr_of_subjects, int v[], int c[])
{
	int points_stud = 0;
	for (int k = 0; k < nr_of_subjects; k++)
		points_stud += v[k] * c[k];
	return points_stud;
}

// Find the most valuable subject, returned as max. A subject is
// the most valuable if (10 - your_grade) * nr of credits is the biggest
int find_best_choice(int n, int v[], int c[])
{
	int poz = 0;
	int temp[NMAX], max = 0;
	for (int k = 0; k < n; k++)
		temp[k] = ((10 - v[k]) * c[k]);

	max = temp[0];
	for (int k = 1; k < n; k++)
		if (max < temp[k]) {
			max = temp[k];
			poz = k;
		}

	interchange(&v[poz], &v[n - 1]);
	interchange(&c[poz], &c[n - 1]);
	for (int k = 0; k < n; k++)
		temp[k] = 0;
	return max;
}

int main(void)
{
	int nr_of_subjects, index, x[NMAX], c[NMAX], minimum_score,
	int number_of_aditions = 0, points_stud = 0;

	// Get the number of the subjects
	scanf("%d", &nr_of_subjects);

	// Grt the grades
	for (index = 0; index < nr_of_subjects; index++)
		scanf("%d", &x[index]);

	// Get the credits
	for (index = 0; index < nr_of_subjects; index++)
		scanf("%d", &c[index]);

	// Get the minimum points needed
	scanf("%d", &minimum_score);


	// If the current number of points is greater or equal than needed
	// Then we need to pass 0 subjects to get a scholarship
	points_stud = curent_score(nr_of_subjects, x, c);
	if (points_stud > minimum_score) {
		printf("%d\n", number_of_aditions);
		return 0;
	}

	// As long as our score is less than the needed one, we add the most
	// valuable subject. If our score reaches our target, we quit the loop
	// If there are not enough points available, we quit
	while (points_stud < minimum_score && nr_of_subjects != 0) {
		points_stud = points_stud + find_best_choice(nr_of_subjects, x, c);
		number_of_aditions++;
		nr_of_subjects--;
	}

	// Display result
	// We reached target
	if (number_of_aditions != 0 && nr_of_subjects == 0 && points_stud > minimum_score) {
		printf("%d\n", number_of_aditions);
	// Impossible target
	} else if (nr_of_subjects == 0) {
		number_of_aditions = -1;
		printf("%d\n", number_of_aditions);
	} else {
		printf("%d\n", number_of_aditions);
	}

	return 0;
}
