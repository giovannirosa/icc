#include "utils.h"

// Retorna tempo em segundos
double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return ((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0))*0.001;
}

int doublecmp(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}