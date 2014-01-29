	AREA text, CODE, READONLY
		EXPORT fermat1
fermat1
	
	;GBLA	N			; Initlize the variable N
						; GBLA is an instruction declears a global 
						; arithmetic variable, and initalize its value to 0.
N	EQU		10			; ERROR: Can not assign value to the N.
	LDR 	R0, =0x1234	; Set R0 to 0x1234
	MOV		R0, #1000	; Assign value to register R0, assume it's N.
	TEQ		R0, #0		; Test is n is equal to zero
	BMI		negative			; if (N < 0)
negative	
	MOV		R1, #0		; f1 = 0
	MOV		R2, #0		; f2 = 0
	;return f1 = f2 = 0
	
	BEQ		zero 		; if (N == 0)
zero

	;return f1 = f2 = 0
	
	TST		R0, #1		; Even or Odd test, the Z flag will be set if R0 AND is zero, i.e if R1 is even
	BEQ 	N_is_even
N_is_even
	MOV		R1, #2		; f1 = 2
	LSR 	R0, #2		; N/2
	MOV 	R2, R0		; f = N/2
	BNE		N_is_odd
N_is_odd
	VMOV   				S0, R0	; Assign the value from R0 to the FPU register.
	VCVT.F32.S32 		S1, S0	; Convert signed interger to float
	VSQRT.F32 			S2, S1	; x = squrt(N)
	VCVT{01}.S32.F32	S3, S2	; x = ceil(x), rounding mode 01, means ceiling.	
	
	BX LR;
	END;