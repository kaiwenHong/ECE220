#include <stdlib.h>
#include <stdio.h>
/* This program takes 2 inputs from the user and prints the semi primes between the 2 numbers inputted

Lab Partners: Luis Aragon (laragon2), Manan Mittal (manansm2)*/


int is_prime(int number);
int print_semiprimes(int a, int b);


int main(){   
   int a, b;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return 1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return 1;
   }

   // TODO: call the print_semiprimes function to print semiprimes in [a,b] (including a and b)
   print_semiprimes(a,b);
   return 0;
}


/*
 * TODO: implement this function to check the number is prime or not.
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
/* This method checks if the number given to it is semi prime */
int is_prime(int number)
{
	int i,c = 0;
	for(i=2;c<2 && i*i<=number;i++)
	{
		while(number % i ==0){
			number = number/i;
			c++;
		}
	}
	return c +(number > 1) == 2;
}


/*
 * TODO: implement this function to print all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
/*This method checks all the numbers in the interval and prints them if its a semi prime */
int print_semiprimes(int a, int b)
{
	int x = 0;
	int y = b;
	for(x = a;x<=y;x++){
		if(is_prime(x)){
			printf("%d", x);
			putchar(' ');
		}
	}
	putchar('\n');
	
	return 0;
	
}



