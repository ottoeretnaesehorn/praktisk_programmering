#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

int is_matrix_symmetric (gsl_matrix * A);

void apply_jacobi_right (gsl_matrix * A, int p, int q, double theta);
void apply_jacobi_left (gsl_matrix * A, int p, int q, double theta);

void jacobi_diagonalisation (gsl_matrix * A, gsl_matrix * V);
