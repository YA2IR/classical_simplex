#include "examples.h"

/*
 *  most (if not all) of these examples are taken from 'Operations Research: Applications and Algorithms' by Winston 
 * */

float giapetto_obj_func[] = {3.0, 2.0, 0.0, 0.0, 0.0, 0.0};
float* giapetto_constraints[] = {
    (float[]){2.0, 1.0, 1.0, 0.0, 0.0, 100.0},
    (float[]){1.0, 1.0, 0.0, 1.0, 0.0, 80.0},
    (float[]){1.0, 0.0, 0.0, 0.0, 1.0, 40.0}
};
int giapetto_is_max = 1; 
int giapetto_n_vars = 2; 
int giapetto_n_consts = 3; 

float dakota_obj_func[] = {-60.0, -30.0, -20.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float* dakota_constraints[] = {
    (float[]){8.0, 6.0, 1.0, 1.0, 0.0, 0.0,0.0, 48.0},
    (float[]){4.0, 2.0, 1.5, 0.0, 1.0, 0.0,0.0, 20.0},
    (float[]){2.0, 1.5, 0.5, 0.0, 0.0, 1.0, 0.0,8.0},
    (float[]){0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 5.0}
};
int dakota_is_max = 0; 
int dakota_n_vars = 3; 
int dakota_n_consts = 4;

float unbounded_obj_func[] = {36.0, 30.0, -3.0, -4.0, 0.0, 0.0, 0.0};
float* unbounded_constraints[] = {
    (float[]){1.0, 1.0, -1.0, 0.0, 1.0, 0.0, 5.0},
    (float[]){6.0, 5.0, 0.0, -1.0, 0.0, 1.0, 10.0}
};
int unbounded_is_max = 1;
int unbounded_n_vars = 4;
int unbounded_n_consts = 2;

// degenrate LP with no cycling
 float degen_no_cycle_obj_func[] = {5.0, 2.0, 0.0, 0.0, 0.0};
 float* degen_no_cycle_constraints[] = {
    (float[]){1.0, 1.0, 1.0, 0.0, 6.0},
    (float[]){1.0, -1.0, 0.0, 1.0, 0.0}
};
int degen_no_cycle_is_max = 1; 
int degen_no_cycle_n_vars = 2;
int degen_no_cycle_n_consts = 2;


float cycling_obj_func[] = {10.0, -57.0, -9.0, -24.0, 0.0, 0.0, 0.0, 0.0};
float* cycling_constraints[] = {
    (float[]){0.5, -5.5, -2.5, 9.0, 1.0, 0.0, 0.0, 0.0},
    (float[]){0.5, -1.5, -0.5, 1.0, 0.0, 1.0, 0.0, 0.0},
    (float[]){1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0}
};
int cycling_is_max = 1; 
int cycling_n_vars = 3;
int cycling_n_consts = 3;


