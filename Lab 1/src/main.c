/******************************************
 * Tashreef
 * Yang
 * ***************************************/


#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SIZE 31      // Size of the temporary buffer used in prime factorization 

typedef struct Fermitfactor
{
	uint32_t f1;
	uint32_t f2;
} Fermitfactors;     // typedef struct

extern uint64_t fermat1(uint32_t N);   //Call assembly func Fermat1 from C

//Helper/TestBench Func prototypes
Fermitfactors CallAssembly (int, int);
Fermitfactors factorization (int);
void Primefactorization(int);
extern uint32_t GCD(uint32_t number1, uint32_t number2);
extern uint32_t LCM(uint32_t number1, uint32_t number2);
void CallGCD (int, int);


int main ()
{
	 uint32_t Number = 7868025;
	 uint32_t GCDReturn;
	 uint32_t LCMReturn;
	
	
	 // Call assembly Fermat from C
	 Fermitfactors Factors_1 = {0, 0};
	 CallAssembly(Number, 1);
	 
	 // Call C-Fermat from C
   Factors_1 = factorization (Number);
	 
	 // Call Prime Factorization from C
	 Primefactorization(Number);
   printf("\nC: f1: %d \t C: f2: %d\n", Factors_1.f1, Factors_1.f2);
	 
	 //Call GCD
	 GCDReturn = GCD(13, 17);
	 printf("The result of GCD is %d\n", GCDReturn);
	 
	 //Call LCM
	 LCMReturn = LCM(5, 25);
	 printf("The result of LCM is %d\n", LCMReturn);
   
   return 0;

}

Fermitfactors CallAssembly (int Number, int display_flag)
{
	uint32_t Mask = 0xFFFFFFFF; // 32-bits all 1s
	uint64_t FermatReturn_64;
	FermatReturn_64 = fermat1(Number);  // 64-bits, Most Significant 32bits -> R1; Least Significant 32bits -> R0
	Fermitfactors Factors_arm = {0, 0};
	
	Factors_arm.f1 = Mask & FermatReturn_64;  // Extract the Least Significant 32bits -> R0
	FermatReturn_64 = FermatReturn_64 >> 32;  // Shift the 64-bit >> 32
	Factors_arm.f2 = Mask & FermatReturn_64;  // Extract the Most Significant 32bits -> R1
	
	// display_flag 1,0 -> print both factors
	if (display_flag)
	{
		printf("ARM Assembly x:%d\n", Factors_arm.f1);  
		printf("ARM Assembly x:%d\n", Factors_arm.f2);  
	}
	
	return Factors_arm;
}

void Primefactorization(int Num)
{
	uint32_t PrimeFound = 0;           // Flag 0-> Number not prime factors and 1 ->  Number prime found before looping
	uint32_t NumberToDisplay = Num;    // Flag for displaying TestBench output
	uint32_t index = 1;                // index for the array PrimeFactors[32]
	uint32_t i;                        
	uint32_t PrimeFactors[32] = {0};   // array PrimeFactors[32] contains all prime factors
	uint32_t Buffer[SIZE] = {0};       // Temporary storage for prime factors calculation SIZE=31 => cannot have more than 31 non zero prime factors
	uint32_t Size = 1;                 // number of non zero elements in the temp storage
	uint32_t BufferIndex = 0;          
	uint32_t FirstEmpty = 0;           // First empty spot in the temporary storage array
	Fermitfactors FactorsRet = {0, 0}; // 
	
	// For number <= 0, make first element 0
	if (Num <= 0)
	{
		PrimeFactors[0] = 0;
	}
	else
	{
		PrimeFactors[0] = 1;
		FactorsRet = CallAssembly(Num, 0); //Call assembly without displaying the fermat factors
		
		// if either fermat factors are 1 this means a prime number
    // is found on first try, update flags PrimeFound and write 
    // the prime number to the array PrimeFactors 		
		if ((FactorsRet.f1 == 1) || (FactorsRet.f2 == 1))
		{
			if (FactorsRet.f1 != 1)
			{
				PrimeFactors[index] = FactorsRet.f1;
			}
			else
				PrimeFactors[index] = FactorsRet.f2;
			
			index++;
			PrimeFound=1;
		}
		
		// Replace the first two elements of the buffer
		Buffer[0] = FactorsRet.f1;
		Buffer[1] = FactorsRet.f2;
		Size=2;
		// Now Buffer contains 2 nonzero elements, Size == 0 when no more prime numbers in the temp storage
		while ((PrimeFound != 1) && Size != 0)
		{
			Size=0;
			FactorsRet = CallAssembly(Buffer[BufferIndex], 0);
			
			if ((FactorsRet.f1 == 1) || (FactorsRet.f2 == 1))
			{
				if (FactorsRet.f1 != 1)
				{
					PrimeFactors[index] = FactorsRet.f1;
				}
				else
					PrimeFactors[index] = FactorsRet.f2;
				
				Buffer[BufferIndex]=0;
				index++;
			}
			else
			{
				Buffer[BufferIndex] = FactorsRet.f1;
				// Get the first empty spot in the temp storage buffer
				for (i=0; i < SIZE; i++)
				{
					if (Buffer[i] == 0)
					{
						FirstEmpty = i;
						i=SIZE;
					}
				}
				Buffer[FirstEmpty] = FactorsRet.f2;
			}
			
			//Tenp storage buffer's BufferIndex
			for (i=0; i < SIZE; i++)
			{
				if (Buffer[i] != 0)
				{
					BufferIndex = i;
					i=SIZE;
				}
			}
			
			// Number od nonzero elements indicates number of non-prime numbers
			for (i=0; i < SIZE; i++)
			{
				if (Buffer[i] != 0)
				{
					Size++;
					
				}
			}		
		}
}
	
/*********************************
*  PrimeFactorization ends Here **
*  array PrimeFactors contains  **
*  all the prime factors.       **      
*********************************/

/*  STARTS: Displaying all prime numbers and there product   */

	int j=0, flag=1;
	uint32_t MultFactor = 1;

	if (PrimeFactors[0] == 0)
	{
		printf("No Prime factors\n");
	}
	else
	{
		while (PrimeFactors[j] != 0)
		{
			if (flag)
			{
				printf("Prime factors of %d are: ",NumberToDisplay);
				flag--;
			}
			
			if (PrimeFactors[0] != 0)
			{
				MultFactor = MultFactor * PrimeFactors[j];
				printf("%d ",PrimeFactors[j]);
			}
			else
			{
				printf("%d \n",0);
			}
			j++;
		}
		
		if (PrimeFactors[0] != 0)
		{
			printf("\nProduct of all factors gives: %d ",MultFactor);
		}
	
	}
	
	/*  ENDS: Displaying all prime numbers and there product   */
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


	Factors_2.f1 = x+(int)sqrt(y2);
	Factors_2.f2 = x-(int)sqrt(y2);

	return Factors_2;

}


