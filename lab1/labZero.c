#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "ZeroFuncao.h"

int main ()
{
  Polinomio *p = (Polinomio*) malloc(sizeof(Polinomio));
  printf("Entre com o grau do polinômio: ");
  scanf("%d", &(p->grau));
  double numero;
  int i = 0;
  p->p = (double*) malloc(sizeof(double)*(p->grau+1));
  while (i <= p->grau) {
    printf("\nEntre com o próximo coeficiente do polinômio: ");
    // p->p[i] = (double*) malloc(sizeof(double));
    scanf("%lf", &p->p[i++]);
  }
  
  // printf("\n\nGrau do Polinomio: %d", p->grau);
  // for (i = 0; i <= p->grau; i++)
  //   printf("\nCoeficiente: %lf", p->p[i]);
  
  // printf("\nEquação: ");
  // for (i = 0; i <= p->grau; i++) {
  //   printf("%lfx(%d)", p->p[i], p->grau-i);
  //   if (i != p->grau) printf(" + ");
  // }
  
  // printf("\nDeu boa!\n\n");

  // RAPIDO --------------------------------------------------------------------------
  // printf("\n--------------------------------------------------------------------------\n");
  // printf("Utilizando o método rápido para cálculo do polinômio\n");

  double *pxBis = (double*) malloc(sizeof(double));
  double *epsBis = (double*) malloc(sizeof(double));
  int *itBis = (int*) malloc(sizeof(int));
  printf("\nMétodo Bissecção");
  printf("\nEntre com o valor de a: ");
  double a;
  scanf("%lf", &a);
  printf("\nEntre com o valor de b: ");
  double b;
  scanf("%lf", &b);
  double startBis = timestamp();
  bisseccao(*p,a,b,epsBis,itBis,pxBis,1);
  double timeBis = timestamp() - startBis;
  // printf("\nResultado da Bissecção: %lf Tempo gasto: %lf\n\n", *pxBis, timeBis);


  double *pxNew = (double*) malloc(sizeof(double));
  double *epsNew = (double*) malloc(sizeof(double));
  int *itNew = (int*) malloc(sizeof(int));
  printf("\nMétodo NewtonRaphson");
  printf("\nEntre com o valor de x0: ");
  double x0;
  scanf("%lf", &x0);
  double startNew = timestamp();
  int retNew = newtonRaphson(*p,x0,epsNew,itNew,pxNew,1);
  double timeNew = timestamp() - startNew;
  // if (retNew == 0)
  //   printf("\nResultado do NewtonRaphson: %lf Tempo gasto: %lf\n\n", *pxNew, timeNew);
  // else {
  //   printf("\nNão foi possível chegar a uma raíz com o método NewtonRaphson\n");
  //   // return 1;
  // }

  double *pxSec = (double*) malloc(sizeof(double));
  double *epsSec = (double*) malloc(sizeof(double));
  int *itSec = (int*) malloc(sizeof(int));
  printf("\nMétodo Secante");
  printf("\nEntre com o valor de x0: ");
  double y0;
  scanf("%lf", &y0);
  printf("\nEntre com o valor de x1: ");
  double y1;
  scanf("%lf", &y1);
  double startSec = timestamp();
  int retSec = secante(*p,y0,y1,epsSec,itSec,pxSec,1);
  double timeSec = timestamp() - startSec;
  // if (retSec == 0)
  //   printf("\nResultado da Secante: %lf Tempo gasto: %lf\n", *pxSec, timeSec);
  // else {
  //   printf("\nNão foi possível chegar a uma raíz com o método Secante\n");
  //   // return 1;
  // }

  // LENTO --------------------------------------------------------------------------
  // printf("\n--------------------------------------------------------------------------\n");
  // printf("Utilizando o método lento para cálculo do polinômio\n");

  double *pxBisLen = (double*) malloc(sizeof(double));
  double *epsBisLen = (double*) malloc(sizeof(double));
  int *itBisLen = (int*) malloc(sizeof(int));
  double startBisLen = timestamp();
  bisseccao(*p,a,b,epsBisLen,itBisLen,pxBisLen,0);
  double timeBisLen = timestamp() - startBisLen;
  // printf("\nResultado da Bissecção: %lf Tempo gasto: %lf\n\n", *pxBisLen, timeBisLen);


  double *pxNewLen = (double*) malloc(sizeof(double));
  double *epsNewLen = (double*) malloc(sizeof(double));
  int *itNewLen = (int*) malloc(sizeof(int));
  double startNewLen = timestamp();
  int retNewLen = newtonRaphson(*p,x0,epsNewLen,itNewLen,pxNewLen,0);
  double timeNewLen = timestamp() - startNewLen;
  // if (retNewLen == 0)
  //   printf("\nResultado do NewtonRaphson: %lf Tempo gasto: %lf\n\n", *pxNewLen, timeNewLen);
  // else {
  //   printf("\nNão foi possível chegar a uma raíz com o método NewtonRaphson\n");
  //   // return 1;
  // }

  double *pxSecLen = (double*) malloc(sizeof(double));
  double *epsSecLen = (double*) malloc(sizeof(double));
  int *itSecLen = (int*) malloc(sizeof(int));
  double startSecLen = timestamp();
  int retSecLen = secante(*p,y0,y1,epsSecLen,itSecLen,pxSecLen,0);
  double timeSecLen = timestamp() - startSecLen;
  // if (retSecLen == 0)
  //   printf("\nResultado da Secante: %lf Tempo gasto: %lf\n", *pxSecLen, timeSecLen);
  // else {
  //   printf("\nNão foi possível chegar a uma raíz com o método Secante\n");
  //   // return 1;
  // }

  printf("\n--------------------------------------------------------------------------\n");
  printf("Utilizando o método rápido para cálculo do polinômio\n");

  printf("\nMétodo\t\tRaiz\t\tErro\t\tIterações\tTempo\n");
  printf("Bissecção\t%lf\t%lf\t%d\t\t%lf\n", *pxBis, *epsBis, *itBis, timeBis);
  printf("NewtonRaphson\t%lf\t%lf\t%d\t\t%lf\n", *pxNew, *epsNew, *itNew, timeNew);
  printf("Secante\t\t%lf\t%lf\t%d\t\t%lf\n", *pxSec, *epsSec, *itSec, timeSec);

  printf("\n--------------------------------------------------------------------------\n");
  printf("Utilizando o método lento para cálculo do polinômio\n");

  printf("\nMétodo\t\tRaiz\t\tErro\t\tIterações\tTempo\n");
  printf("Bissecção\t%lf\t%lf\t%d\t\t%lf\n", *pxBisLen, *epsBisLen, *itBisLen, timeBisLen);
  printf("NewtonRaphson\t%lf\t%lf\t%d\t\t%lf\n", *pxNewLen, *epsNewLen, *itNewLen, timeNewLen);
  printf("Secante\t\t%lf\t%lf\t%d\t\t%lf\n", *pxSecLen, *epsSecLen, *itSecLen, timeSecLen);

  // double *px = (double*) malloc(sizeof(double));
  // double *dpx = (double*) malloc(sizeof(double));
  // printf("\nEntre com o valor de x: ");
  // double x;
  // scanf("%lf", &x);
  // calcPolinomio_rapido(*p,x,px,dpx);
  // printf("\nResultado do Polinomio rápido: %lf Derivada: %lf\n", *px, *dpx);
  // calcPolinomio_lento(*p,x,px,dpx);
  // printf("\nResultado do Polinomio lento: %lf Derivada: %lf\n", *px, *dpx);

  return 0;
}

