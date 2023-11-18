/******************** followsymtest.c ******************/
#include <stdio.h>
#include "symname.h"
#include "followsym.h"
int main()
{
  int i;
  symnameinit();
  followsyminit();
  for (i=0; i<symSYMMAX; i++)
  {
    if (factor[i] != 0)
      printf("factor[%s]=%d\n",names[i],factor[i]);
  }
  return 0;
}
