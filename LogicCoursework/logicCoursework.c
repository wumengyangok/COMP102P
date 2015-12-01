#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

/*  The main program calls procedures parse, partone, parttwo and bin which are not implemented here.
*/
// X[] - EA ^ v > () 
// check formula:
// for X: 
// only followed by [ is true
// after that 
// check xy pattern 
// wait for a ]
// for EA:
// only followed by x,y or z is true
// after that 
// check formula
// for (:
//   find the middle ^ v >
//   check formula1 and formula2
//   wait another )
// for -:
// eat it and then check formula


int Fsize=200;  /*big enough for our formulas*/
char * middle1;
char * tail1;
char * _middle;
int layer = 0;
char partOne[50];
int parseXYZ(char *g)
{
  if ((*g == '[') && ((*(g+1) == 'x') || (*(g+1) == 'y') || (*(g+1) == 'z')) && ((*(g+2) == 'x') || (*(g+2) == 'y') || (*(g+2) == 'z')) && (*(g+3) == ']'))
  {
    return 1;
  }else
  {
    return 0;
  }
}
int parseParenthesis(char *g)
{
    
    int height = 0;
    while((!((height == 1)&&((*g == '^')||(*g == 'v')||(*g == '>'))))&&(*g != '\0'))
    {
        if (*g == '(')
        {
            height++;
        }
        if (*g == ')')
        {
            if (height)
            {
                height--;
            }
            else
            {
                return 0;
            }
        }
        g++;
    }
    if (*g == '\0')
    {
        return 0;
    }else
    {
        middle1 = g;
    }
    g++;
    while((*g != '\0')&&(height>0))
    {
        if (*g == '(')
        {
            height++;
        }
        if (*g == ')')
        {
            if (height >= 0)
            {
                height--;
            }
            else
            {
                return 0;
            }
        }
        g++;
    }
    if ((*g == '\0')&&(*(g-1) == ')'))
    {
        tail1 = g-1;
        return 1;
    }else
    {
        return 0;
    }
}

int parse(char *g)
/* returns 0 for non-formulas, 1 for atoms, 2 for negations, 3 for binary connective fmlas, 4 for existential and 5 for universal formulas.*/
{
    char * middle;
    char * tail;
    char temp;
    switch(*g){
        case 'X':
            if (!parseXYZ(g+1))
                return 0;
            else
                return 1;
            break;
        case 'E':
            if ((*(g+1)=='x')||(*(g+1)=='y')||(*(g+1)=='z'))
            {
                g+=2;
                if(!parse(g))
                    return 0;
                else
                    return 4;
            }else
            {
                return 0;
            }
            break;
        case 'A':
            if ((*(g+1)=='x')||(*(g+1)=='y')||(*(g+1)=='z'))
            {
                g+=2;
                if(!parse(g))
                    return 0;
                else
                    return 5;
            }else
            {
                return 0;
            }
            break;
        case '-':
            g++;
            if (!parse(g))
                return 0;
            else
                return 2;
            break;
        case '(':
            if (parseParenthesis(g))
            {
                layer++;
                middle = middle1;
                if (layer == 1)
                {
                    _middle = middle;
                }
                tail = tail1;
                temp = *middle;
                *middle = '\0';
                *tail = '\0';
                g++;
                if(parse(g)&&parse(middle+1))
                {
                    *middle = temp;
                    *tail = ')';
                    return 3;
                }else
                {
                    return 0;
                }
            }else
            {
                return 0;
            }
            break;
        default:
            return 0;
    }
}


char *partone(char *g)
/*
Given a formula (A*B) this should return A
 */
{
  int i = 0;
  while(g != _middle)
  {
    partOne[i] = *g;
    i++;
    g++;
  }
  partOne[i] = '\0';
  return partOne;
}

char *parttwo(char *g)
/*
Given a formula (A*B) this should return B
 */
{
    g = _middle;
    g++;
    while(*g != '\0')
    {
        g++;
    }
    g--;
    *g = '\0';
    _middle++;
    return _middle;
}

char bin(char *g)
/*
Given a formula (A*B) this should return the character *
 */
{
  return *_middle;
}


int main()
{
  /*Input a string and check if its a formula*/
  char *name=malloc(Fsize);
  printf("Enter a formula:");
  scanf("%s", name);
  int p=parse(name);
  switch(p)
    {
    case 0: printf("Not a formula\n");break;
    case 1: printf("An atomic formula\n");break;
    case 2: printf("A negated formula\n");break;
    case 3: printf("A binary connective formula\n");break;
    case 4: printf("An existential formula\n");break;
    case 5: printf("A universal formula\n");break;
    default: printf("Not a formula\n");break;
    }

  if (p==3)
    {
      printf("The first part is %s, the binary connective is %c, the second part is %s\n", partone(name), bin(name), parttwo(name));
    }
  return(1);
}