#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "examples.h"
#define NAN 123456789


struct lp {
	float* obj_func;
	float** constraints;
	float** matrix;
	int n_cols;
	int n_rows;
	float* original_obj_func;
	bool is_max;
	bool is_degenerate;
};

struct lp s;

void init_lp(struct lp* lp, float* obj_func, float** constraints,
		int n_vars, int n_consts, const bool is_max) {	

	lp->obj_func = obj_func;
	lp->constraints = constraints;
	lp->n_cols = n_vars + n_consts + 1;
	lp->n_rows = n_consts + 1;
	lp->is_max = is_max;
    lp->original_obj_func = malloc(sizeof(float)*lp->n_cols);

	// init matrix 
	lp->matrix = (float**)malloc((lp->n_rows + 1) * sizeof(float*));

	lp->matrix[0] = obj_func;

	for (int i = 0; i < lp->n_rows; i++) { 
		lp->matrix[i+1] = constraints[i];
    }

	if (lp->is_max) {
		for (int i = 0; i < lp->n_cols; i++)
			lp->obj_func[i] *= -1.0;
    }

	memcpy(lp->original_obj_func, obj_func, sizeof(float)*lp->n_cols);

	/* checking degeneracy  */
	lp->is_degenerate = false;
	for (int i = 0; i < n_consts; i++)
		if (lp->constraints[i][lp->n_cols-1] == 0.0) {
			lp->is_degenerate = true;
			break;
		}
}

int get_entering_var() {
	int idx = 0;
	for (int i = 1; i < s.n_cols; i++) {
		if (s.obj_func[i] <  s.obj_func[idx])
			idx = i;
    }
	return idx;
}

int ratio_test(int e) {
	float ratios[s.n_rows-1], ratio;
	for (int i = 0; i < s.n_rows - 1; i++) {
		if (s.constraints[i][e] <= 0) {
			ratio = NAN;
		} else {
			ratio = s.constraints[i][s.n_cols - 1] / s.constraints[i][e];
        }

		if (ratio >= 0) {
			ratios[i] = ratio;
		} else {
			ratios[i] = NAN;
        }
		// printf("%f / %f = %f\n", s.constraints[i][s.n_cols - 1], s.constraints[i][e],ratio);
	}

	int idx = 0;
	for (int i = 1; i < s.n_rows - 1; i++) {    
		if (ratios[i] < ratios[idx]) {
			idx = i;
		} 
    }

	return ratios[idx] != NAN ? idx+1 : -1;
}

bool exists_negative_nbv() {
	for (int i = 0; i < s.n_cols; i++)
		if (s.obj_func[i] < 0)
			return true;
	return false;
}

bool compare_to_original() {
	for (int i = 0; i < s.n_cols; i++)
		if (s.original_obj_func[i] != s.obj_func[i]) 
			return false;
	return true;
}

void pivot(int col_idx, int row_idx) {
   float* enter_row = s.matrix[row_idx];
   float reciprocal = 1 / enter_row[col_idx];
   for (int i = 0; i < s.n_cols; i++)
      enter_row[i] *= reciprocal;

    for (int i = 0; i < s.n_rows; i++) {
        if (i != row_idx) {
            float* row = s.matrix[i];
            double factor = -row[col_idx];
            for (int j = 0; j < s.n_cols; j++) {
                row[j] += factor * enter_row[j];
            }
        }
    }

}

void print_matrix(float** matrix, int rows, int cols) {
    printf("\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
			printf("%.2f\t", matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void free_memory() {
    free(s.matrix);
    free(s.original_obj_func);
}

int main() {


	 init_lp(&s, dakota_obj_func, dakota_constraints, dakota_n_vars, dakota_n_consts, dakota_is_max);
	// init_lp(&s, cycling_obj_func, cycling_constraints, cycling_n_vars, cycling_n_consts, cycling_is_max);
	// init_lp(&s, giapetto_obj_func, giapetto_constraints, giapetto_n_vars, giapetto_n_consts, giapetto_is_max);
	// init_lp(&s, unbounded_obj_func, unbounded_constraints, unbounded_n_vars, unbounded_n_consts, unbounded_is_max);
	// init_lp(&s, degen_no_cycle_obj_func, degen_no_cycle_constraints, degen_no_cycle_n_vars, degen_no_cycle_n_consts, degen_no_cycle_is_max);

	print_matrix( s.matrix, s.n_rows, s.n_cols);

	while(exists_negative_nbv()) {
		// row
		int enter_var_idx = get_entering_var();
		// col
		int leave_var_idx = ratio_test(enter_var_idx);

		if (leave_var_idx == -1) {
			printf("\nRatio test failed. (LP unbounded)\n");
            free_memory();
            return 1;
		}

		pivot(enter_var_idx, leave_var_idx);


		if (s.is_degenerate && compare_to_original()) {
			printf("Cycling detected. Terminating at initial tableau\n");
            free_memory();
			return 1;
		}
				
        print_matrix(s.matrix, s.n_rows, s.n_cols);
	}

	printf("An optimal solution has been reached, Z = %f\n", s.obj_func[s.n_cols-1]);

    free_memory();
	return 0;
}

