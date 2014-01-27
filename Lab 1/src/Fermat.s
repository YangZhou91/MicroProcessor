	AREA text, CODE, READONLY
		EXPORT fermat1
fermat1
	MOV		R0, #10		; Assign 100 to register R0, assume it's N.
	TEQ		R0, #0		; Test is n is equal to zero
	BMI		neg			; if (N < 0)
neg	
	;return f1 = f2 = 0
	BEQ		zero 		; if (N == 0)
zero
	;return f1 = f2 = 0
	
	BX LR;
	END;