#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

/*  The main program calls procedures parse, partone, parttwo and bin which are not implemented here.
*/



int Fsize=50;  /*big enough for our formulas*/

int parse(char *g)
/* returns 0 for non-formulas, 1 for atoms, 2 for negations, 3 for binary connective fmlas, 4 for existential and 5 for universal formulas.*/
{
}

char *partone(char *g)
/*
Given a formula (A*B) this should return A
 */
{
}

char *parttwo(char *g)
/*
Given a formula (A*B) this should return B
 */
{
}

char bin(char *g)
/*
Given a formula (A*B) this should return the character *
 */
{
}


int main()
{
  /*Input a string and check if its a formula*/
  char *name=malloc(Fsize);
  printf("Enter a formula:");
  scanf("%s", name);
  int p=parse(name);
  switch(p)
    {case 0: printf("Not a formula");break;
    case 1: printf("An atomic formula");break;
    case 2: printf("A negated formula");break;
    case 3: printf("A binary connective formula");break;
    case 4: printf("An existential formula");break;
    case 5: printf("A universal formula");break;
    default: printf("Not a formula");break;
    }

  if (p==3)
    {printf("The first part is %s, the binary connective is %c, the second part is %s", partone(name), bin(name), parttwo(name));

  return(1);
}