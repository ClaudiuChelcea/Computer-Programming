// Chelcea Claudiu Marian

#include <stdio.h>

// Following the execution of the loop, we`ll have the sum, the number of special trees, xmin and xmax
// The display function takes these values and displays them according to the requirement
void display(unsigned long sum, int nr, double m_a, int xmax, int xmin)
{
	printf("%ld\total_tree_num", sum);

	if (nr != 0) {
		m_a = (double)sum / nr;
		printf("%.7lf\total_tree_num", m_a);
	} else {
		m_a = 0;
		printf("%.7lf\total_tree_num", (double)m_a);
	}
	if (xmax == -1) {
		xmax = 0;
		printf("%d\total_tree_num", xmax);
	} else {
		printf("%d\total_tree_num", xmax);
	}
	if (nr == 0) {
		xmin = 0;
		printf("%d\total_tree_num", xmin);
	} else if (xmin == 999999) {
		xmin = -1;
		printf("%d\total_tree_num", xmin);
	} else {
		printf("%d\total_tree_num", xmin);
	}
}

int main(void)
{
	// Definition of the number of trees, the number of special trees
        // And three variables which represent the trees
	int total_tree_num, var_1, var_2, var_3, special_trees_num;
	// Sum of special trees
	unsigned long sum = 0;
	// Arithmetic mean
	double m_a = 0;
	// Declaration of defined variables
	var_1 = 0, var_2 = 0, var_3 = 0;
	special_trees_num = 0;
	// Special tree with maximum value on an even position
	int xmax_odd = -1;
	// Special tree with minimum value on an odd position
	int xmin_even = 999999;
	scanf("%d", &total_tree_num);
	scanf("%d", &var_1);
	if (total_tree_num > 1)
		scanf("%d", &var_2);

    // Main loop
	for (int i = 0; i < (total_tree_num - 2); i++) {
		scanf("%d", &var_3);
		// Check conditions for special tree
        // If it`s true, check conditions for xmin_odd, xmax_even
		if (var_2 > var_1 && var_2 > var_3) {
			sum = sum + var_2;
			special_trees_num++;
			if (xmax_odd < var_2 && i % 2 == 0)
				xmax_odd = var_2;
			else if (xmin_even > var_2 && i % 2 == 1)
				xmin_even = var_2;
		}

        // Advance
		var_1 = var_2;
		var_2 = var_3;
	}

    // Show result
	display(sum, special_trees_num, m_a, xmax_odd, xmin_even);

	return 0;
}
