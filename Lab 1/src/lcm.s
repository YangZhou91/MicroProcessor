	AREA text, CODE, READONLY
		EXPORT lcm
lcm
;	MOV 	R1, #32		; Initlize the first number
;	MOV 	R2, #45		; Initlize the second number
	MUL		R3, R0, R1	; Calculate the product of R0 and R1

	CMP		R0, #0	; Compare the R0 with 0			
	BEQ		output_zero

	CMP		R1, #0
	BEQ		output_zero

	B	calculate_gcd
	
calculate_gcd
	CMP		R0, R1		; Compare two numbers
	SUBGT	R0, R0, R1	; R0 = R0-R1 if R0 is greater
	SUBLE	R1, R1, R0	; R1 = R1 - R0 if R1 is greater
	CMP		R0, R1
	BNE		calculate_gcd
	BEQ		calculate_lcm
	
calculate_lcm
	
	SDIV 	R0, R3, R1  ; The LCM is the quotient, stored in R0
	BX LR
	
output_zero
	MOV	R0, #0	; Store 0 into R3, as output.
	BX LR
	END;
