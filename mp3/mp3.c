#include <stdio.h>
#include <stdlib.h>

// This program takes an input from a user and outputs the row of the pascals 		triangle that corresponds to the input.

//Lab Parters : Manan Mittal (manansm2), Luis Aragon (laragon2)
long printRow(int row);
int main()
{
  int row;

  printf("Enter a row index: ");
  scanf("%d",&row);

  // Write your code here
  	printRow(row);
	return 0;
  }
  
long printRow(int row)
{	// initializing variables
	long temp, k, i;
	for(k=0;k<=row;k++)
	{
		temp = 1;
		for(i=1;i<=k;i++)
		{
			temp=temp*(row+1-i)/i;
		}
		// print temp's value to string that corresponds to the row
		printf("%li ", temp);
	}
	printf("\n");
	return 0;
	
}
  
 
