	AREA text, CODE, READONLY
	EXPORT LCM
	IMPORT GCD
LCM
	MUL	R3, R0, R1	; Calculate the product of R0 and R1

	CMP	R0, #0 ; Compare the R0 with 0
	BEQ	output_zero

	CMP	R1, #0
	BEQ	output_zero

	B	calculate_gcd

calculate_gcd
	MOV     R5, LR         ; Save address of LR
	LDR 	R4, =GCD       ; Branch out to GCD
	BLX     R4             ; --
	MOV     LR, R5         ; Restore the address in LR
	B	    calculate_lcm

calculate_lcm

	SDIV R0, R3, R1 ; The LCM is the quotient, stored in R0
	BX LR

output_zero
	MOV	R0, #0 ; Store 0 into R3, as output.
	BX LR
	END;
	
	