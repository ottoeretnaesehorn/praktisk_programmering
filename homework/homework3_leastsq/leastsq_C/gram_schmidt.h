void GS_decomposition (gsl_matrix * A, gsl_matrix * R);
void back_substitution (gsl_matrix * U, gsl_vector * c);
void GS_solve (gsl_matrix * Q, gsl_matrix * R, gsl_vector * b, gsl_vector * x);
void GS_inverse (gsl_matrix * Q, gsl_matrix * R, gsl_matrix * B);
