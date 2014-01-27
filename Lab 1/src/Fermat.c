/******************************************
 * Tashreef
 * Yang
 * Compile with : gcc -o test Fermat.c -lm
 * Run: ./test 5959
 * ***************************************/


#include <stdio.h>
#include <math.h>

typedef struct Fermitfactor
{
	int f1;
	int f2;
} Fermitfactors;

Fermitfactors factorization (int);

int main (int argc, char* argv[])
{

   if (argc != 2) return 0;
   
   Fermitfactors Factors_1 = {0, 0};
   int Number = atoi(argv[1]);
   
   Factors_1 = factorization (Number);
   
   printf("f1: %d \t f2: %d\n", Factors_1.f1, Factors_1.f2);   // For Debug only
   
   return 0;

}

Fermitfactors factorization (int N)
{
	double x, y2, Num;
	Fermitfactors Factors_2 = {0, 0};

	if ((N < 0) || (N == 0))
	{
	return Factors_2;
	}
	else if (N%2 == 0)
	{
		Factors_2.f1 = 2;
		Factors_2.f2 = N/2;
		
		return Factors_2;
	}
	else
	{
		Num = (double)N;
		x = ceil(sqrt(Num));
		y2 = x*x - Num;

		while (fmod((sqrt(y2)),1.0) != 0.0)
		{
			x++;
			y2 = x*x-Num;
		}
	}

	printf("x:%f\n", x);  // For Debug only
	printf("y^2:%f\n", y2);  // For Debug only

	Factors_2.f1 = x+(int)sqrt(y2);
	Factors_2.f2 = x-(int)sqrt(y2);

	return Factors_2;

}



