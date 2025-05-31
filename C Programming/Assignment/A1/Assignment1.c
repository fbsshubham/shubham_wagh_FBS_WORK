//Finding C from F(temp)(using function without returntype without parameters).
#include<stdio.h>
void temp();			//fn declaration without returntype and without parameters
void main()
{
	printf("Start of program:\n");
	temp();				//fn call
	printf("End the program...");
}
void temp()				//fn Body
{
	float c,f;
	printf("Start of function:\n");
	printf("Enter temprature in celcius :");
	scanf("%f",&c);
	f=c*5/9+32;
	printf("Temprature in fahrenheit is %f\n",f);
	printf("End of function...\n");
}
 
