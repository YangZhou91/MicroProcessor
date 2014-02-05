	AREA text, CODE, READONLY
	EXPORT GCD
GCD
	CMP	R0, #0 ; Compare the R0 with 0
	BEQ	output_zero


	CMP	R1, #0
	BEQ	output_zero

	B	calculate_gcd
calculate_gcd
	CMP	R0, R1	; Compare two numbers
	SUBGT	R0, R0, R1	; R0 = R0-R1 if R0 is greater
	SUBLE	R1, R1, R0	; R1 = R1 - R0 if R1 is greater
	CMP		R0, R1
	BNE	calculate_gcd
	MOVEQ	R0, R1	; Store R10 into R0
    BEQ     EndLoop
	
output_zero
	MOV		R0, #0 ; Store 0 into R3, as output.
	BX 		LR
EndLoop
    BX 		LR
	
	END;
	
	
	
	
	