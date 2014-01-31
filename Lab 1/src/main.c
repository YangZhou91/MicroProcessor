#include <stdio.h>

extern int lcm(int number1, int number2);

int main()
{
	int number1 = 0;
	int number2 = 40;
	int result = lcm(number1, number2);
	printf("The first number is %d\n", number1);
	printf("The second number is %d\n", number2);
	printf("The result is %d\n", result);

	return 0;
}



