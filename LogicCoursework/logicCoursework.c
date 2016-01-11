#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize = 200;  /*big enough for our formulas*/
char * middleAll = NULL;
char * tailAll = NULL;
char * _middle = NULL;
int layer = 0;
char partOne[50];
int no_edges;
int no_nodes;

int parseXYZ(char *g)
{
    if ((*g == '[') && ((*(g+1) == 'x') || (*(g+1) == 'y') || (*(g+1) == 'z')) && ((*(g+2) == 'x') || (*(g+2) == 'y') || (*(g+2) == 'z')) && (*(g+3) == ']') && (*(g+4) == '\0'))
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
        middleAll = g;
    }
    g++;
    while ((*g != '\0')&&(height>0))
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
        tailAll = g-1;
        return 1;
    } else
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
                middle = middleAll;
                if (layer == 1)
                {
                    _middle = middle;
                }
                tail = tailAll;
                temp = *middle;
                *middle = '\0';
                *tail = '\0';
                g++;
                if(parse(g)&&parse(middle+1))
                {
                    *middle = temp;
                    *tail = ')';
                    middleAll = middle;
                    tailAll = tail;
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
    g++;
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

int interpret(char variable){
    switch (variable) {
        case 'x':
            return 0;
            break;
        case 'y':
            return 1;
            break;
        case 'z':
            return 2;
            break;
        default:
            return -1;
            break;
    }
}

int eval(char *nm, int edges[no_edges][2], int size, int V[3])
/*this method takes a formula, the list of edges of a graph, the number of vertices and a variable assignment.  It then evaluates the formula and returns 1 or 0 as appropriate.  */
{
    int v[3] = {
        V[0], V[1], V[2]
    };
    int flag;
    char *middle = NULL;
    char *tail = NULL;
    char temp = '\0';
    if(middle != NULL)
        temp = *middle;
    int part1, part2;
    switch(parse(nm))
    {
        case 1:
            flag = 0;
            for (int i = 0; i < no_edges; ++i)
            {
                if ((edges[i][0] == v[interpret(*(nm + 2))]) && (edges[i][1] == v[interpret(*(nm + 3))]))
                {
                    flag = 1;
                }
            }
            if (flag)
            {
                return 1;
            }else{
                return 0;
            }
            break;
        case 2:
            return !eval(++nm,edges,size,v);
            break;
        case 3:
            middle = middleAll;
            tail = tailAll;
            temp = *middle;
            *middle = '\0';
            part1 = eval(nm+1,edges,size,v);
            *tail = '\0';
            part2 = eval(middle+1,edges,size,v);
            *middle = temp;
            *tail = ')';
            switch(*middleAll)
        {
            case '^': return (part1 && part2);break;
            case 'v': return (part1 || part2);break;
            case '>': return (!part1 || part2);break;
            default: break;
        }
            break;
        case 4:
            flag = 0;
            switch(*(nm+1)){
                case 'x':
                    for (int i = 0; i < no_nodes; ++i)
                    {
                        v[0] = i;
                        flag |= eval(nm+2,edges,size,v);
                    }
                    break;
                case 'y':
                    for (int i = 0; i < no_nodes; ++i)
                    {
                        v[1] = i;
                        flag |= eval(nm+2,edges,size,v);
                    }
                    break;
                case 'z':
                    for (int i = 0; i < no_nodes; ++i)
                    {
                        v[2] = i;
                        flag |= eval(nm+2,edges,size,v);
                    }
                    break;
                default: break;
            }
            return flag;
            break;
        case 5:
            flag = 1;
            switch(*(nm+1)){
                case 'x':
                    for (int i = 0; i < no_nodes; ++i)
                    {
                        v[0] = i;
                        flag &= eval(nm+2,edges,size,v);
                    }
                    break;
                case 'y':
                    for (int i = 0; i < no_nodes; ++i)
                    {
                        v[1] = i;
                        flag &= eval(nm+2,edges,size,v);
                    }
                    break;
                case 'z':
                    for (int i = 0; i < no_nodes; ++i)
                    {
                        v[2] = i;
                        flag &= eval(nm+2,edges,size,v);
                    }
                    break;
                default: break;
            }
            return flag;
            break;
        default: break;
    }
    return 0;
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
    /*
    if (p==3)
    {
        printf("The first part is %s, the binary connective is %c, the second part is %s\n", partone(name), bin(name), parttwo(name));
    }
     */
    /*Input a graph.  No. of nodes, edges, then input each edge.*/
    if (p == 0) {
        return 0;
    }
    printf("How many nodes in the graph?\n");
    scanf(" %d", &no_nodes);
    printf("The nodes are 0, 1, ..., %d\n", no_nodes-1);
    printf("Now the edges\n");
    printf("How many edges?\n");
    scanf(" %d", &no_edges);
    
    int edges[no_edges][2];  /*Store edges in 2D array*/
    int  i, k, j;
    for(i=0;i<no_edges;i++)
    {
        printf("input a pair of nodes (<%d)", no_nodes);
        scanf(" %d", &j);
        scanf(" %d", &k);
        edges[i][0]=j; edges[i][1]=k;
    }
    /*Assign variables x, y, z to nodes */
    int V[3];
    /*Store variable values in array
     value of x in V[0]
     value of y in V[1]
     value of z in V[2] */
    printf("Assign variables x, y, z\n");
    printf("x is ?(<%d)", no_nodes);scanf(" %d", &V[0]);
    printf("y is ?");scanf(" %d", &V[1]);
    printf("z is ?");scanf(" %d", &V[2]);
    /*Now check if formula is true in the graph with given variable assignment. */
    if (eval(name, edges, no_nodes,  V)==1)
        printf("The formula %s is true\n", name);
    else
        printf("The formula %s is false\n", name);
    free(name);
    return(1);
}