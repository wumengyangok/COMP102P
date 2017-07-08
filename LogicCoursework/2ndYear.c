#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>   /* malloc, free, rand */

int Fsize = 50;
int cases = 10;
char *middle;
char *tail;

int i;
int j;

/*typedef struct tableau tableau;*/

struct tableau {
  char *root;
  struct  tableau *left;
  struct tableau *right;
  struct tableau *parent;
} *tab, *node, *node1, *kid, *pa;

/*put all your functions here.  You will need
1.
int parse(char *g) which returns 1 if a proposition, 2 if neg, 3 if binary, ow 0
2. 
void complete(struct tableau *t)
which expands the root of the tableau and recursively completes any child tableaus.
3. 
int closed(struct tableau *t)
which checks if the whole tableau is closed.
Of course you will almost certainly need many other functions.

You may vary this program provided it reads 6 formulas in a file called "input.txt" and outputs in the way indicated below to a file called "output.txt".
*/

int is_letter(char c) {
    if (c >= 'a' && c <= 'z')
        return 1;
    else
        return 0;
}

char * copy(char * s, char * e) {
    char *ans = (char*) malloc (Fsize);
    char *g = s;
    char *a = ans;
    while (g != e) {
        *a = *g;
        a++;
        g++;
    }
    *a = '\0';
    return ans;
}

char * copy_till_end(char * s) {
    char *ans = (char*) malloc (Fsize);
    char *g = s;
    char *a = ans;
    while (*g != '\0') {
        *a = *g;
        a++;
        g++;
    }
    *(a-1) = '\0';
    return ans;
}

char * negate(char * s) {
    char *ans = (char*) malloc (Fsize);
    char * g = s;
    *ans = '-';
    char *a = ans;
    a++;
    while (*g != '\0') {
        *a = *g;
        a++;
        g++;
    }
    *a = '\0';
    return ans;
}

void insert_one(struct tableau *t, char * p1, char * p2) {
    if (t->left != NULL)
        insert_one(t->left, p1, p2);
    if (t->right != NULL)
        insert_one(t->right, p1, p2);
    if (t->left == NULL && t->right == NULL) {
        struct tableau * p = (struct tableau*)malloc(sizeof(struct tableau));
        p->parent = t;
        t->left = p;
        p->root = p1;
        p = (struct tableau*)malloc(sizeof(struct tableau));
        p->parent = t->left;
        t->left->left = p;
        p->root = p2;
    }
}

void insert_two(struct tableau *t, char * p1, char * p2) {
    if (t->left != NULL)
        insert_two(t->left, p1, p2);
    if (t->right != NULL)
        insert_two(t->right, p1, p2);
    if (t->left == NULL && t->right == NULL) {
        struct tableau * p = (struct tableau*)malloc(sizeof(struct tableau));
        p->parent = t;
        t->left = p;
        p->root = p1;
        
        p = (struct tableau*)malloc(sizeof(struct tableau));
        p->parent = t;
        t->right = p;
        p->root = p2;
    }
}


/*
 
 -- a
 (p^q)
 -(pvq)
 -(p>q)
 --p
 
 -- b
 (pvq)
 (p>q)
 -(p^q)
 
 */


void complete(struct tableau *t) {
    char *g = t->root;
    char *s1;
    char *s2;
    if (*g == '(') {
        int stack = 0;
        while (*g != '\0') {
            if (*g == '(')
                stack++;
            else if (*g == ')')
                stack--;
            if ((stack == 1) && (*g == '>' || *g == '^' || *g == 'v')) {
                s1 = copy(t->root+1, g);
                s2 = copy_till_end(g+1);
                switch (*g) {
                    case '^' :
                        insert_one(t, s1, s2);
                        break;
                    case 'v' :
                        insert_two(t, s1, s2);
                        break;
                    case '>' :
                        s1 = negate(s1);
                        insert_two(t, s1, s2);
                        break;
                    default : break;
                }
                break;
            }
            g++;
        }
    } else if (*g == '-') {
        if (*(g+1) == '-') {
            t->root += 2;
            complete(t);
        } else if (*(g+1) == '(') {
            g++;
            int stack = 0;
            while (*g != '\0') {
                if (*g == '(')
                    stack++;
                else if (*g == ')')
                    stack--;
                if ((stack == 1) && (*g == '>' || *g == '^' || *g == 'v')) {
                    s1 = copy(t->root+2, g);
                    s2 = copy_till_end(g+1);
                    switch (*g) {
                        case '^' :
                            s1 = negate(s1);
                            s2 = negate(s2);
                            insert_two(t, s1, s2);
                            break;
                        case 'v' :
                            s1 = negate(s1);
                            s2 = negate(s2);
                            insert_one(t, s1, s2);
                            break;
                        case '>' :
                            s2 = negate(s2);
                            insert_one(t, s1, s2);
                            break;
                        default : break;
                    }
                    break;
                }
                g++;
            }
        }
    }
    if (t->left != NULL)
        complete(t->left);
    if (t->right != NULL)
        complete(t->right);
}

int compare(char * s, char * ss) {
  if (*s == '-' && *(s+1) == *ss)
    return 1;
  if (*ss == '-' && *(ss+1) == *s)
    return 1;
  return 0;
}

int closed(struct tableau *t) {
  if (t->left != NULL && t->right != NULL) {
    if (closed(t->left) && closed(t->right))
      return 1;
  } else if (t->left != NULL) {
    if (closed(t->left))
      return 1;
  }
  char * g = t->root;
  if (*g == '-')
    g++;
  if (is_letter(*g)) {
    struct tableau * p = t;
    while (p->parent != NULL) {
      p = p->parent;
      if (compare(t->root, p->root))
        return 1;
    }
  }
  return 0;
}

int parseParenthesis(char *g) {
    int height = 0;
    while((!((height == 1)&&((*g == '^')||(*g == 'v')||(*g == '>'))))&&(*g != '\0')) {
        if (*g == '(') {
            height++;
        }
        if (*g == ')') {
            if (height) {
                height--;
            } else {
                return 0;
            }
        }
        g++;
    }
    
    if (*g == '\0') {
        return 0;
    } else {
        middle = g;
    }
    g++;
    while ((*g != '\0')&&(height>0)) {
        if (*g == '(') {
            height++;
        }
        if (*g == ')') {
            if (height >= 0) {
                height--;
            }
            else {
                return 0;
            }
        }
        g++;
    }
    if ((*g == '\0')&&(*(g-1) == ')')) {
        tail = g-1;
        return 1;
    } else {
        return 0;
    }
}

/* returns 0 for non-formulas, 1 for atoms, 2 for negations, 3 for binary connective fmlas, 4 for existential and 5 for universal formulas.*/
int parse(char *g) {
    char *middle_current;
    char *tail_current;
    char temp;
    switch(*g){
        case '-':
            g++;
            if (!parse(g))
                return 0;
            else
                return 2;
            break;
        case '(':
            if (parseParenthesis(g)) {
                middle_current = middle;
                tail_current = tail;
                temp = *middle_current;
                *middle_current = '\0';
                *tail_current = '\0';
                g++;
                if (parse(g) && parse(middle_current+1)) {
                    *middle_current = temp;
                    *tail_current = ')';
                    return 3;
                } else {
                    *middle_current = temp;
                    *tail_current = ')';
                    return 0;
                }
            } else {
                return 0;
            }
            break;
        default:
            if (is_letter(*g) && (*(g+1) == '\0'))
                return 1;
            else
                return 0;
    }
}

int main() { 
  char *name = malloc(Fsize);
  FILE *fp, *fpout;
  /* reads from input.txt, writes to output.txt*/
  if ((fp = fopen("input.txt","r")) == NULL) { printf("Error opening file");exit(1); }
  if ((fpout = fopen("output.txt","w")) == NULL) { printf("Error opening file");exit(1); }
  int j;
  for (j=0; j < cases; j++) {
      fscanf(fp, "%s", name); /*read formula*/
      switch (parse(name)) {
        case(0): fprintf(fpout, "%s is not a formula.  ", name);break;
        case(1): fprintf(fpout, "%s is a proposition.  ", name);break;
        case(2): fprintf(fpout, "%s is a negation.  ", name);break;
        case(3): fprintf(fpout, "%s is a binary.  ", name);break;
        default: fprintf(fpout, "What the f***!  ");
      }
      /*make new tableau with name at root, no children, no parent*/
      struct tableau t = { name, NULL, NULL, NULL };
      /*expand the root, recursively complete the children*/
      if (parse(name)!=0) {
        complete(&t);
        if (closed(&t)) fprintf(fpout, "%s is not satisfiable.\n", name);
        else fprintf(fpout, "%s is satisfiable.\n", name);
      } else fprintf(fpout, "I told you, %s is not a formula.\n", name);
  }
  fclose(fp);
  fclose(fpout);
  free(name);
  return(0);
}