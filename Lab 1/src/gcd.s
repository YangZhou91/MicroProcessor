	AREA text, CODE, READONLY
		EXPORT gcd
gcd
	
	MOV 	R1, #69	; Initlize the first number in R0 
	MOV		R2, #0	; Initlize the second number in R1
	CMP		R1, #0	; Compare the R0 with 0			
	BEQ		output_zero

	
	CMP		R2, #0
	BEQ		output_zero
	
	B	calculate_gcd
calculate_gcd
	CMP		R1, R2		; Compare two numbers
	SUBGT	R1, R1, R2	; R0 = R0-R1 if R0 is greater
	SUBLE	R2, R2, R1	; R1 = R1 - R0 if R1 is greater
	BNE		calculate_gcd
	MOVEQ	R0, R1		; Store R10 into R0
	
output_zero
	MOV	R0, #0	; Store 0 into R3, as output.
	BX LR
	END;