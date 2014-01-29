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
	
	BEQ		zero 		; if (N == 0), go to brach zero
zero
	MOV		R1, #0		; f1 = 0
	MOV		R2, #0		; f2 = 0
	
	TST		R0, #1		; Even or Odd test, the Z flag will be set if R0 AND is zero, i.e if R1 is even
	BEQ 	N_is_even	; Go to branch N_is_even 
	BNE		N_is_odd	; Go to branch N_is_odd
N_is_even
	MOV		R1, #2		; f1 = 2
	LSR 	R0, #2		; N/2
	MOV 	R2, R0		; f = N/2
	
N_is_odd
	VMOV   				S0, R0		; Assign the value from R0 to the FPU register.
	VCVT.F32.S32 		S1, S0		; Convert N from signed interger to float
	VSQRT.F32 			S2, S1		; x = squrt(N)
	;VCVT{01}.F32.S32	S3, S2		; x = ceil(x), rounding mode 01, means ceiling.	
	VMUL.F32			S4, S2, S2	; temp = x^2
	VSUB.F32			S5, S4, S1	; y^2 = x^2 - N
	VSQRT.F32			S6, S5		; y = sqrt(y^2), the default rounding is to 0.
	VMUL.F32			S7, S6, S6	; Compute the y^2 again
	VCMP				S7, S5		; Test equivalence of two y^2
	BEQ		
	BX LR;
	END;