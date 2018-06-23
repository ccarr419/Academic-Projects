/* clock example: countdown */
#include <stdio.h>
#include <time.h>

void waitFor ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

int main ()
{ printf("There are %d ticks of the system clock per second\n",CLOCKS_PER_SEC);
  int n;
  printf ("Starting countdown...\n");
  for (n=10; n>0; n--)
  {
    printf ("%d\n",n);
    waitFor (1);
  }
  printf ("FIRE!!!\n");
  return 0;
}

