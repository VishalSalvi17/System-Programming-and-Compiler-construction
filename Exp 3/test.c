// Prerak Parekh
// 2018130035
// SPCC
// Exp 3 - To create user defined library in open source environment and use it for particular functions

// Inlcuding all the required libraries
#include <stdio.h>
#include "sample.h"
#include <math.h>

// The main function
int main(void) {
    puts("Below I am using a shared library using function sample()...");
    int input = 0;

    // Infinite while loop for executing the functions
    while(input!=-1) {
        // Switch case
        printf("Enter below mentioned number\n");
        printf("1 for factorial\n");
        printf("2 for e to the power x\n");
        printf("3 for a to the power x\n");
        printf("4 for log to base 10\n");
        printf("5 for log a to log b\n");
        printf("6 for natural logarithm\n");
        printf("7 for exponential growth\n");
        printf("8 for log numlitplied with power\n");
        printf("9 for binomial distribution\n");
        printf("10 for poisson distribution\n");
        printf("-1 for exiting\n");
        printf("Enter the input");
        scanf("%d", &input);
        switch(input) {
            // declaring the variables
            long f;
            float val;
            float a;
            float e;
            float n;
            int n1;
            float p;
            int u;
            int x;
            float base;
            float expo;
            float loga;

            case 1:
            printf("Enter the number whose factorial is required");
            scanf("%ld", &f);
            printf("The factorial value is : %ld", fact(f));
            printf("\n");
            break;
            
            case 2:
            printf("Enter the number whose exponential is required");
            scanf("%f", &val);
            printf("The exponential value is : %f", etox(val));
            printf("\n");
            break;
            
            case 3:
            printf("Enter the base");
            scanf("%f", &a);
            printf("Enter the exponent");
            scanf("%f", &e);
            printf("The exponential value is : %f", atox(a, e));
            printf("\n");
            break;
            
            case 4:
            printf("Enter the value whose logarithm is required:");
            scanf("%f", &val);
            printf("The logarithm value is : %f", log(val));
            printf("\n");
            break;
            
            case 5:
            printf("Enter the base value of the logarithm");
            scanf("%f", &n);
            printf("Enter the value whose logarithm is to be found");
            scanf("%f", &a);
            printf("The logarithm value is : %f", logan(a, n));
            printf("\n");
            break;
            
            case 6:
            printf("Enter the value whose natural logarithm is to be found:");
            scanf("%f", &n);
            printf("The natural logarithm value is : %f", ln(n));
            printf("\n");
            break;
            
            case 7:
            printf("Enter the base value:");
            scanf("%f", &base);
            printf("Enter the exponent:");
            scanf("%f", &expo);
            printf("The exponential growth value is : %f", exponentialgrowth(base, expo));
            printf("\n");
            break;
            
            case 8:
            printf("Enter the logarithmic value:");
            scanf("%f", &loga);
            printf("Enter the exponent:");
            scanf("%f", &expo);
            printf("The logarithm multiplied with exponent value is : %f", logmulpow(loga, expo));
            printf("\n");
            break;
            
            case 9:
            printf("Enter the p value:");
            scanf("%f", &p);
            printf("Enter the n value:");
            scanf("%d", &n1);
            printf("Enter the x value:");
            scanf("%d", &x);
            printf("The binomial coefficient value is : %f", binomial(p, n1, x));
            printf("\n");
            break;
            
            case 10:
            printf("u is always greater then x");
            printf("Enter the u value:");
            scanf("%d", &u);
            printf("Enter the x value:");
            scanf("%d", &x);
            printf("The binomial coefficient value is : %f", poisson(u, x));
            printf("\n");
            break;
            default:
            printf("Wrong input");
            printf("\n");
            break;
        }
    }
    return 0;
}