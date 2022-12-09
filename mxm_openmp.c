//this will have openmp implementation of matmul.
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

int main ( void )
{
  int n = 5;
  double (*a)[n][n] = malloc(sizeof * a);
  double (*b)[n][n] = malloc(sizeof * b);
  double (*c)[n][n] = malloc(sizeof * c);

//  double a[500][500];
  double angle;
//  double b[500][500];
//  double c[500][500];
  int i;
  int j;
  int k;
  double pi = 3.141592653589793;
  double s;
  int thread_num;

//  thread_num = omp_get_max_threads ( );
thread_num = 1;

  s = 1.0 / sqrt ( ( double ) ( n ) );

#pragma omp parallel shared ( a, b, c, n, pi, s ) private ( angle, i, j, k )
{
  #pragma omp for
  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      angle = 2.0 * pi * i * j / ( double ) n;
      (*a)[i][j] = s * ( sin ( angle ) + cos ( angle ) );
    }
  }
/*
  Loop 2: Copy A into B.
*/
  #pragma omp for
  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      (*b)[i][j] = (*a)[i][j];
    }
  }
/*
  Loop 3: Compute C = A * B.
*/
  #pragma omp for
  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n; j++ )
    {
      (*c)[i][j] = 0.0;
      for ( k = 0; k < n; k++ )
      {
        (*c)[i][j] = (*c)[i][j] + (*a)[i][k] * (*b)[k][j];
      }
    }
  }

}
  printf ( "  C(100,100)  = %g\n", (*c)[99][99] );

  free(a);
  free(b);
  free(c);

  return 0;
}
