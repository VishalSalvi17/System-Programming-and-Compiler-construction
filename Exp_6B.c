//Vishal Salvi
//2019230069
//BATCH C
//52
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int z = 0,i = 0,j = 0,c = 0;
char a[16], ac[20], stk[15], act[10];

void check()
{
    strcpy(ac,"Reduce to s->");
    for(z =0; z<c; z++)
    {
        if(stk[z] == '2')
        {
            printf("%s2",ac);
            stk[z] = 's';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t",stk,a);
        }
    }
    for(z =0; z<c-2; z++)
    {
        if(stk[z] == 'E' && stk[z+1] == '+' && stk[z+2] == 'E')
        {
            printf("%sE+E",ac);
            stk[z] = 's';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t",stk,a);
            i = i -2;
        }
    }
    for(z =0; z<c-2; z++)
    {
        if(stk[z] == 'E' && stk[z+1] == '*' && stk[z+2] == 'E')
        {
            printf("%sE*E",ac);
            stk[z] = 's';
            stk[z + 1] = '\0';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t",stk,a);
            i = i -2;
        }
    }
    return;
}

int main()
{
    printf("Grammer is -\ns-> T+T/T*T/id \n");
    char name[20];
    scanf("%s", name);
    strcpy(a,name);
    c=strlen(a);
    strcpy(act,"Shift");
    printf("\nstack \t input \t action");
    printf("\n$\t%s$\t",a);
    
    for(i=0; j < c; i++, j++)
    {
        printf("%s",act);
        stk[i] = a[j];
        stk[i+1] = '\0';
        a[j]=' ';
        printf("\n$%s\t%s$\t",stk,a);
        check();
    }
    check();
    if(stk[0] == 's' && stk[1] == '\0')
        printf("Accept\n");
    else
        printf("Reject\n");
        
}