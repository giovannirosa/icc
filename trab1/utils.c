#include "utils.h"
#define EPSILON 0.001

// Retorna tempo em milisegundos
double timestamp(void)
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

int doublecmp(double a, double b)
{
    return fabs(a - b) < EPSILON;
}