	AREA text, CODE, READONLY
		EXPORT fermat1
fermat1
		
	;MOV		R0, #10		; Assign 100 to register R0, assume it's N.
	CMP		R0, #0
	MOVLE	R0, #0		; f1 = 0 ; for debug purpose used 6 and 7 to see register values changing from zero -> something
	MOVLE	R1, #0		; f2 = 0
	BLE     RETURN_END
	BGT     Odd_Even_Check 

RETURN_END
	BX      LR
	
Odd_Even_Check
	TST		R0, #1		; Even or Odd test, the Z flag will be set if R0 AND is zero, i.e if R1 is even
	BEQ 	N_is_even
	BNE 	N_is_odd
	
N_is_even
	MOV     R1, #2
	UDIV    R1, R0, R1  ;f2
	MOV		R0, #2		; f1 = 2
	BX		LR
	
	
N_is_odd
	VMOV   S0, R0			; S0 -> N
	VMOV.F32   S1, #1		; S1 contains 1.0
	VCVT.F64.F32	S2, S1	;
	VCVT.F32.U32 S0, S0 	; convert N from int to float
	;VCVT.F63.F32 S0, S0		; convert N from single to double
	VSQRT.F32  S2, S0		; compute sqrt of N 
	
	VCVT.U32.F32 S3, S2     ; convert sqrt of N from float to nearest uint
	VCVT.F32.U32 S3, S3     ; convert it back to float uint to float
	
	VCMP.F32 S2, S3         ; comparison between squartroot and its int
	VMRS APSR_nzcv, FPSCR
	VADDGT.F32 S1, S1, S3   ; positive result sets FPSCR flag to GT: 0010 -> weird
	VMOVEQ.F32 S1, S3 	    ; equal comparison sets FPSCR to EQ: 0110
	                        ; register S1 now has the ceiling value 									
;---------------------------------------------------------------------------------

    VMUL.F32			S5, S1, S1	; temp = x^2 -> S5
	VSUB.F32			S5, S5, S0	; y^2 = x^2 - N -> S5 to be y^2
	
	VMOV.F32			S7, #1		; Assign 1 to a 32-bit register reg contains 1
	B 					while_loop

while_loop
	VSQRT.F32			S6, S5		; y = sqrt(y^2), the default rounding is to 0.
	;conversoin needed
	VCVT.U32.F32 		S6, S6
	VCVT.F32.U32 		S6, S6 
	VMUL.F32			S6, S6, S6	; Compute the y^2 again
	VCMP.F32			S5, S6		; Test equivalence of two y^2
	VMRS APSR_nzcv, FPSCR
	
	BEQ					Final
	VADDGT.F32			S1, S1, S7 	; x = x + 1
	VMULGT.F32			S4, S1, S1	; temp = x^2 -> S4
	VSUBGT.F32			S5, S4, S0	; y^2 = x^2 - N
	BGT					while_loop
	
Final
	VSQRT.F32		  S6, S6
	VADD.F32          S2, S1, S6
	VSUB.F32	      S3, S1, S6
	VCVT.U32.F32      S2, S2
	VCVT.U32.F32      S3, S3
	VMOV              R0, R1, S2, S3
	
	BX LR;
	END;
		
	