// Prerak Parekh
// 2018130035
// SPCC
// Exp 3 - To create user defined library in open source environment and use it for particular functions

#include <stdio.h>
#include <math.h>
#include "sample.h"
// Including all the required librares

// factorial function
long fact(long n) {
    if(n == 0 || n == 1) return 1;
    return n*fact(n-1);
}

// exponential function
double etox(double x) {
    return exp(x);
}

// a raised to function
double atox(double x, double y) {
    return pow(x, y);
}

// Natural logarithm function
double logn(double x) {
    return log10(x);
}

// normal logarithm function
double logan(double a, double n) {
    return log10(a)/log10(n);
}

double ln(double x) {
    return log(x);
}

// Exponential growth function
double exponentialgrowth(double x, double y) {
    return pow((1 + x), y);
}

// Logarithm multiplied with power function
double logmulpow(double a, double x) {
    return log(a)*pow(a, x);
}

// Binomial coefficient calculation function
double binomial(double p, int n, int x) {
    double num = fact(n)*pow(p, x)*pow((1-p), (n-x));
    double den = fact(x)*fact(n-x);

    return num/den;
}

// Poisson coefficient calculation function
double poisson(int u, int x) {

    double num = exp(-1*u)*(pow(u, x));
    double den = fact(x);

    return num/den;
}